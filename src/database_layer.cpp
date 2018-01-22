#include <database_layer.h>

#include <sstream>
#include <string>

#include <stdio.h>
#include <string.h>

#include <transaction.h>

#include <field_input.h>

DatabaseLayer::DatabaseLayer()
{

	m_database = NULL;

}

DatabaseLayer::~DatabaseLayer()
{
}

void DatabaseLayer::OpenDatabase()
{

	int result = sqlite3_open("FinanceDatabase.db", &m_database);

	if (result != SQLITE_OK)
	{

		// TODO: better error reporting
		printf("Could not open database.\n");

	}

	InitializeDatabase();

}

bool DatabaseLayer::DoesTableExist(const char *tableName)
{

	sqlite3_stmt *statement;
	char buffer[256];
	int result;
	bool found = true;

	sprintf(buffer, "SELECT name FROM sqlite_master WHERE type='table' AND name='%s'", tableName);

	result = sqlite3_prepare_v2(m_database, buffer, -1, &statement, NULL);

	result = sqlite3_step(statement);

	if (result != SQLITE_ROW)
	{

		found = false;

	}

	// Free the statement
	sqlite3_finalize(statement);

	return found;

}

void DatabaseLayer::RenameTable(const char *name, const char *newName)
{

	sqlite3_stmt *statement;
	char buffer[256];
	int result;
	bool found = true;

	sprintf(buffer, "ALTER TABLE %s RENAME TO %s", name, newName);

	result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

	if (result != SQLITE_OK &&
		result != SQLITE_ROW &&
		result != SQLITE_DONE)
	{

		// TODO: error could not create table

	}

}

void DatabaseLayer::CreateTable(const char *tableName, const char *columns)
{

	char buffer[1024];

	sprintf(buffer, "CREATE TABLE %s (%s);", tableName, columns);

	int result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

	if (result != SQLITE_OK &&
		result != SQLITE_ROW &&
		result != SQLITE_DONE)
	{

		// TODO: error could not create table

	}

}

void DatabaseLayer::Insert(const char *tableName, const char *data)
{

	char buffer[1024];

	sprintf(buffer, "INSERT INTO %s VALUES (%s);", tableName, data);

	int result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

	if (result != SQLITE_OK &&
		result != SQLITE_ROW &&
		result != SQLITE_DONE)
	{

		// TODO: error could not insert into table

		const char *err = sqlite3_errmsg(m_database);
		int a = 0;

	}

}

void DatabaseLayer::SimpleUpdate(const char *table, const char *idColumn, const char *id, const char *values)
{

	char buffer[1024];

	sprintf(buffer, "UPDATE %s SET %s WHERE %s=%s;", table, values, idColumn, id);

	int result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

	if (result != SQLITE_OK &&
		result != SQLITE_ROW &&
		result != SQLITE_DONE)
	{

		// TODO: error could not update table

	}

}

void DatabaseLayer::InitializeDatabase()
{

}

void DatabaseLayer::PortDatabase(DATABASE_VERSION newVersion)
{

	// To make life easier, porting only works in steps of 1
	while ((int)m_version != (int)newVersion - 1)
	{

		PortDatabase((DATABASE_VERSION)((int)m_version + 1));

	}

	if (newVersion == VERSION_1_0 /* Replace with VERSION_1_1 */ && m_version == VERSION_1_0)
	{

		// Do stuff

	}

}

void DatabaseLayer::CreateTableName(char *name)
{

	int i = 0;
	while (true)
	{

		if (name[i] == '\0') return;

		if (name[i] == ' ')
		{

			name[i] = '_';

		}

		i++;

	}
}

int DatabaseLayer::GetBankSum(const char *date)
{
	// Execute the query

	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT sum(AMOUNT) FROM `TRANSACTIONS` WHERE DATE <= '%s' "
		"AND TYPE_ID=1 "
		"AND ACCOUNT_ID=1"
		, date);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	double amount = sqlite3_column_double(statement, 0);

	result = sqlite3_step(statement);
	sqlite3_finalize(statement);

	return (int)(amount * 100 + 0.5);
}

void DatabaseLayer::InsertTransaction(Transaction *transaction)
{
	// Execute the query

	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	const char *rows = "(ID, NAME, TYPE, CLASS_ID, PARENT_ENTITY_ID, ACCOUNT_ID, AMOUNT, DATE, COUNTERPARTY_ID, NOTES)";

	std::stringstream ss;

	ss << "(";
	ss << "NULL";
	ss << "'" << transaction->GetStringAttribute(std::string("NAME")) << "'" << ",";
	ss << transaction->GetIntAttribute(std::string("TYPE_ID")) << ",";
	ss << transaction->GetIntAttribute(std::string("CLASS_ID")) << ",";
	ss << transaction->GetIntAttribute(std::string("PARENT_ENTITY_ID")) << ",";
	ss << transaction->GetIntAttribute(std::string("ACCOUNT_ID")) << ",";
	ss << ((double)transaction->GetIntAttribute(std::string("AMOUNT")))/100.00 << ",";
	ss << "'" << transaction->GetStringAttribute(std::string("DATE")) << "'" << ",";
	ss << transaction->GetIntAttribute(std::string("COUNTERPARTY_ID")) << ",";
	ss << "'" << transaction->GetStringAttribute(std::string("NOTES")) << "'";
	ss << ")";

	//INSERT INTO COMPANY(ID, NAME, AGE, ADDRESS, SALARY)
	//	VALUES(1, 'Paul', 32, 'California', 20000.00);

	std::string query;
	query += "INSERT INTO TRANSACTIONS";
	query += rows;
	query += " ";
	query += ss.str();
	query += ";";

	result = sqlite3_prepare(m_database, query.c_str(), -1, &statement, NULL);
	result = sqlite3_step(statement);

	double amount = sqlite3_column_double(statement, 0);

	result = sqlite3_step(statement);
	sqlite3_finalize(statement);

	//return (int)(amount * 100 + 0.5);
}

void DatabaseLayer::GetAllCounterpartySuggestions(const char *reference, FieldInput *targetVector)
{
	// Clear suggestions first
	targetVector->ClearSuggestions();

	// Execute the query

	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT ID, NAME FROM `COUNTERPARTIES` WHERE NAME LIKE '%s%%';",
		reference);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	while (result == SQLITE_ROW)
	{
		int ID = sqlite3_column_int(statement, 0);
		std::string name = (char *)sqlite3_column_text(statement, 1);

		targetVector->AddSuggestion(ID, name);

		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);
}

void DatabaseLayer::GetAllAccountSuggestions(const char *reference, FieldInput *targetVector)
{
	// Clear suggestions first
	targetVector->ClearSuggestions();

	// Execute the query

	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT ID, NAME FROM `ACCOUNTS` WHERE NAME LIKE '%s%%';",
		reference);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	while (result == SQLITE_ROW)
	{
		int ID = sqlite3_column_int(statement, 0);
		std::string name = (char *)sqlite3_column_text(statement, 1);

		targetVector->AddSuggestion(ID, name);

		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);
}

void DatabaseLayer::GetAllClassSuggestions(const char *reference, FieldInput *targetVector)
{
	// Clear suggestions first
	targetVector->ClearSuggestions();

	// Execute the query

	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT ID, NAME FROM `CLASSES` WHERE NAME LIKE '%s%%';",
		reference);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	while (result == SQLITE_ROW)
	{
		int ID = sqlite3_column_int(statement, 0);
		std::string name = (char *)sqlite3_column_text(statement, 1);

		targetVector->AddSuggestion(ID, name);

		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);
}

void DatabaseLayer::GetAllTypeSuggestions(const char *reference, FieldInput *targetVector)
{
	// Clear suggestions first
	targetVector->ClearSuggestions();

	// Execute the query

	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT ID, NAME FROM `TYPES` WHERE NAME LIKE '%s%%';",
		reference);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	while (result == SQLITE_ROW)
	{
		int ID = sqlite3_column_int(statement, 0);
		std::string name = (char *)sqlite3_column_text(statement, 1);

		targetVector->AddSuggestion(ID, name);

		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);
}
