#include <database_layer.h>

#include <sstream>
#include <string>
#include <iomanip>

#include <stdio.h>
#include <string.h>

#include <transaction.h>
#include <counterparty.h>
#include <account.h>
#include <transaction_class.h>
#include <transaction_type.h>

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

	const char *rows = "(ID, NAME, TYPE_ID, CLASS_ID, PARENT_ENTITY_ID, ACCOUNT_ID, AMOUNT, DATE, COUNTERPARTY_ID, NOTES)";

	std::stringstream ss;

	ss << std::fixed;
	ss << std::setprecision(2);

	ss << "(";
	ss << "NULL,";
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
	query += " VALUES ";
	query += ss.str();
	query += ";";

	result = sqlite3_exec(m_database, query.c_str(), NULL, NULL, NULL);
}

void DatabaseLayer::UpdateTransaction(Transaction *transaction)
{
	// Execute the query

	int result;
	sqlite3_stmt *statement;
	const char *selectQuery = "SELECT * FROM `TRANSACTIONS`;";
	result = sqlite3_prepare(m_database, selectQuery, -1, &statement, NULL);
	int columnCount = sqlite3_column_count(statement);

	sqlite3_step(statement);

	std::stringstream ss;

	ss << std::fixed;
	ss << std::setprecision(2);

	ss << "UPDATE TRANSACTIONS SET ";

	for (int i = 0; i < columnCount; i++)
	{
		const char *columnName = sqlite3_column_name(statement, i);
		int columnType = sqlite3_column_type(statement, i);

		ss << columnName << " = ";

		if (columnType == SQLITE_INTEGER)
			ss << transaction->GetIntAttribute(std::string(columnName));
		else if (columnType == SQLITE_TEXT)
			ss << "'" << transaction->GetStringAttribute(std::string(columnName)) << "'";
		else if (columnType == SQLITE_FLOAT)
			ss << transaction->GetIntAttribute(std::string(columnName)) / 100.0;
		else if (columnType == SQLITE_NULL)
			ss << "''";

		if (i != columnCount - 1)
			ss << ", ";
	}

	ss << " WHERE ID = " << transaction->m_id;
	std::string updateQuery = ss.str();

	sqlite3_finalize(statement);

	// Execute the generated query

	result = sqlite3_exec(m_database, updateQuery.c_str(), NULL, NULL, NULL);

	if (result != SQLITE_OK &&
		result != SQLITE_ROW &&
		result != SQLITE_DONE)
	{

		// TODO: error could not update table

	}
}

bool DatabaseLayer::GetTransaction(int id, Transaction *target)
{
	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT * FROM `TRANSACTIONS` WHERE ID = %d;",
		id);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	int columnCount = sqlite3_column_count(statement);
	int rowCount = 0;

	while (result == SQLITE_ROW)
	{
		rowCount++;
		for (int i = 0; i < columnCount; i++)
		{
			const char *columnName = sqlite3_column_name(statement, i);
			int columnType = sqlite3_column_type(statement, i);
			
			if (columnType == SQLITE_INTEGER)
				target->SetIntAttribute(std::string(columnName), sqlite3_column_int(statement, i));
			else if (columnType == SQLITE_TEXT)
				target->SetStringAttribute(std::string(columnName), std::string((char *)sqlite3_column_text(statement, i)));
			else if (columnType == SQLITE_FLOAT)
				target->SetIntAttribute(std::string(columnName), (int)(sqlite3_column_double(statement, i)*100));
		}
		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);

	if (rowCount == 0) return false;
	else return true;
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

bool DatabaseLayer::GetCounterparty(int id, Counterparty *target)
{
	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT * FROM `COUNTERPARTIES` WHERE ID = %d;",
		id);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	int columnCount = sqlite3_column_count(statement);
	int rowCount = 0;

	while (result == SQLITE_ROW)
	{
		rowCount++;
		for (int i = 0; i < columnCount; i++)
		{
			const char *columnName = sqlite3_column_name(statement, i);
			int columnType = sqlite3_column_type(statement, i);

			if (columnType == SQLITE_INTEGER)
				target->SetIntAttribute(std::string(columnName), sqlite3_column_int(statement, i));
			else if (columnType == SQLITE_TEXT)
				target->SetStringAttribute(std::string(columnName), std::string((char *)sqlite3_column_text(statement, i)));
			else if (columnType == SQLITE_FLOAT)
				target->SetIntAttribute(std::string(columnName), (int)(sqlite3_column_double(statement, i) * 100));
		}
		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);

	if (rowCount == 0) return false;
	else return true;
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

bool DatabaseLayer::GetAccount(int id, Account *target)
{
	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT * FROM `ACCOUNTS` WHERE ID = %d;",
		id);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	int columnCount = sqlite3_column_count(statement);
	int rowCount = 0;

	while (result == SQLITE_ROW)
	{
		rowCount++;
		for (int i = 0; i < columnCount; i++)
		{
			const char *columnName = sqlite3_column_name(statement, i);
			int columnType = sqlite3_column_type(statement, i);

			if (columnType == SQLITE_INTEGER)
				target->SetIntAttribute(std::string(columnName), sqlite3_column_int(statement, i));
			else if (columnType == SQLITE_TEXT)
				target->SetStringAttribute(std::string(columnName), std::string((char *)sqlite3_column_text(statement, i)));
			else if (columnType == SQLITE_FLOAT)
				target->SetIntAttribute(std::string(columnName), (int)(sqlite3_column_double(statement, i) * 100));

		}
		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);

	if (rowCount == 0) return false;
	else return true;
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

bool DatabaseLayer::GetClass(int id, TransactionClass *target)
{
	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT * FROM `CLASSES` WHERE ID = %d;",
		id);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	int columnCount = sqlite3_column_count(statement);
	int rowCount = 0;

	while (result == SQLITE_ROW)
	{
		rowCount++;
		for (int i = 0; i < columnCount; i++)
		{
			const char *columnName = sqlite3_column_name(statement, i);
			int columnType = sqlite3_column_type(statement, i);

			if (columnType == SQLITE_INTEGER)
				target->SetIntAttribute(std::string(columnName), sqlite3_column_int(statement, i));
			else if (columnType == SQLITE_TEXT)
				target->SetStringAttribute(std::string(columnName), std::string((char *)sqlite3_column_text(statement, i)));
			else if (columnType == SQLITE_FLOAT)
				target->SetIntAttribute(std::string(columnName), (int)(sqlite3_column_double(statement, i) * 100));
		}
		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);

	if (rowCount == 0) return false;
	else return true;
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

bool DatabaseLayer::GetType(int id, TransactionType *target)
{
	int result;
	char buffer[1024];
	sqlite3_stmt *statement;

	sprintf(buffer,
		"SELECT * FROM `TYPES` WHERE ID = %d;",
		id);

	result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
	result = sqlite3_step(statement);

	int columnCount = sqlite3_column_count(statement);
	int rowCount = 0;

	while (result == SQLITE_ROW)
	{
		rowCount++;
		for (int i = 0; i < columnCount; i++)
		{
			const char *columnName = sqlite3_column_name(statement, i);
			int columnType = sqlite3_column_type(statement, i);

			if (columnType == SQLITE_INTEGER)
				target->SetIntAttribute(std::string(columnName), sqlite3_column_int(statement, i));
			else if (columnType == SQLITE_TEXT)
				target->SetStringAttribute(std::string(columnName), std::string((char *)sqlite3_column_text(statement, i)));
			else if (columnType == SQLITE_FLOAT)
				target->SetIntAttribute(std::string(columnName), (int)(sqlite3_column_double(statement, i) * 100));
		}
		result = sqlite3_step(statement);
	}

	sqlite3_finalize(statement);

	if (rowCount == 0) return false;
	else return true;
}
