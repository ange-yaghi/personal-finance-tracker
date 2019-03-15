#include <database_layer.h>

#include <sstream>
#include <string>
#include <iomanip>

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <transaction.h>
#include <account.h>
#include <transaction_class.h>
#include <transaction_type.h>

#include <total_breakdown.h>

#include <field_input.h>

namespace pft {

    DatabaseLayer::DatabaseLayer() {
        m_database = nullptr;
    }

    DatabaseLayer::~DatabaseLayer() {
		assert(m_database == nullptr);
	}

	void DatabaseLayer::Initialize() {

	}

    void DatabaseLayer::OpenDatabase(const char *fileName, bool testMode) {
        int result = sqlite3_open(fileName, &m_database);

        if (result != SQLITE_OK) {
            // TODO: better error reporting
            printf("Could not open database.\n");
        }

		if (!testMode) {
			Initialize();
			InitializeDatabase();
			LoadQueries();
		}
    }

    bool DatabaseLayer::DoesTableExist(const char *tableName) {
        sqlite3_stmt *statement;
        char buffer[256];
        int result;
        bool found = true;

        sprintf_s(buffer, "SELECT name FROM sqlite_master WHERE type='table' AND name='%s'", tableName);

        result = sqlite3_prepare_v2(m_database, buffer, -1, &statement, NULL);

        result = sqlite3_step(statement);

        if (result != SQLITE_ROW) {
            found = false;
        }

        // Free the statement
        sqlite3_finalize(statement);

        return found;
    }

    void DatabaseLayer::RenameTable(const char *name, const char *newName) {
        sqlite3_stmt *statement;
        char buffer[256];
        int result;
        bool found = true;

        sprintf_s(buffer, "ALTER TABLE %s RENAME TO %s", name, newName);

        result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

        if (result != SQLITE_OK &&
            result != SQLITE_ROW &&
            result != SQLITE_DONE) {
            // TODO: error could not create table
        }
    }

    void DatabaseLayer::CreateTable(const char *tableName, const char *columns) {
        char buffer[1024];

        sprintf_s(buffer, "CREATE TABLE %s (%s);", tableName, columns);

        int result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

        if (result != SQLITE_OK &&
            result != SQLITE_ROW &&
            result != SQLITE_DONE) {
            // TODO: error could not create table
        }

    }

    void DatabaseLayer::Insert(const char *tableName, const char *data) {
        char buffer[1024];

        sprintf_s(buffer, "INSERT INTO %s VALUES (%s);", tableName, data);

        int result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

        if (result != SQLITE_OK &&
            result != SQLITE_ROW &&
            result != SQLITE_DONE) {
            // TODO: error could not insert into table
            const char *err = sqlite3_errmsg(m_database);
        }
    }

    void DatabaseLayer::SimpleUpdate(const char *table, const char *idColumn, const char *id, const char *values) {
        char buffer[1024];

        sprintf_s(buffer, "UPDATE %s SET %s WHERE %s=%s;", table, values, idColumn, id);

        int result = sqlite3_exec(m_database, buffer, NULL, NULL, NULL);

        if (result != SQLITE_OK &&
            result != SQLITE_ROW &&
            result != SQLITE_DONE) {
            // TODO: error could not update table
        }
    }

    void DatabaseLayer::InitializeDatabase() {
		m_initializeDatabaseQuery.SetDatabase(m_database);
		m_initializeDatabaseQuery.LoadFile((std::string(m_homePath) + "/assets/sql/generate_db_v1_0.sql").c_str());
		m_initializeDatabaseQuery.Reset();
		m_initializeDatabaseQuery.ExecuteAll();
		m_initializeDatabaseQuery.Free();
    }

    void DatabaseLayer::PortDatabase(DATABASE_VERSION newVersion) {
        // To make life easier, porting only works in steps of 1
        while ((int)m_version != (int)newVersion - 1) {
            PortDatabase((DATABASE_VERSION)((int)m_version + 1));
        }

        if (newVersion == VERSION_1_0 /* Replace with VERSION_1_1 */ && m_version == VERSION_1_0) {
            // Do stuff
        }
    }

    void DatabaseLayer::CreateTableName(char *name) {
        int i = 0;
        while (true) {
            if (name[i] == '\0') return;

            if (name[i] == ' ') {
                name[i] = '_';
            }

            i++;
        }
    }

    int DatabaseLayer::GetAccountBalance(int account, const char *date) {
        // Execute the query

        int result;
        char buffer[1024];
        sqlite3_stmt *statement;

		// First query is for outgoing payments
        sprintf_s(buffer,
            "SELECT sum(AMOUNT) FROM `TRANSACTIONS` WHERE DATE <= '%s' "
            "AND TYPE_ID=1 "
            "AND SOURCE_ACCOUNT_ID=%d",
            date, account);

        result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
        result = sqlite3_step(statement);

        int amount = -sqlite3_column_int(statement, 0);

        result = sqlite3_step(statement);
        sqlite3_finalize(statement);

		// Second query is for incoming payments
		sprintf_s(buffer,
			"SELECT sum(AMOUNT) FROM `TRANSACTIONS` WHERE DATE <= '%s' "
			"AND TYPE_ID=1 "
			"AND TARGET_ACCOUNT_ID=%d",
			date, account);

		result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
		result = sqlite3_step(statement);

		amount += sqlite3_column_int(statement, 0);

		result = sqlite3_step(statement);
		sqlite3_finalize(statement);

		return amount;
    }

    // Get total amount by month
    int DatabaseLayer::GetTotalAmountMonth(int transactionClass, int type, const char *month) {
        TransactionClass tClass;
        tClass.Initialize();
        GetClass(transactionClass, &tClass);

        int childAmount = 0;
        int childCount = tClass.GetChildCount();
        for (int i = 0; i < childCount; i++) {
            childAmount += GetTotalAmountMonth(tClass.GetChild(i)->GetIntAttribute(std::string("ID")), type, month);
        }

        // Execute the query

        int result;
        char buffer[1024];
        sqlite3_stmt *statement;

        sprintf_s(buffer,
            "SELECT sum(AMOUNT) FROM `TRANSACTIONS` WHERE DATE LIKE '%%%s%%' "
            "AND TYPE_ID=%d "
            "AND CLASS_ID=%d",
            month, type, transactionClass);

        result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
        result = sqlite3_step(statement);

        double amount = sqlite3_column_double(statement, 0);

        result = sqlite3_step(statement);
        sqlite3_finalize(statement);

        int roundedAmount = 0;

        if (amount < 0) return childAmount + (int)(amount * 100 - 0.5);
        else return childAmount + (int)(amount * 100 + 0.5);
    }

    // Get total budget by month
    int DatabaseLayer::GetTotalBudgetMonth(int transactionClass, int type, const char *month) {
        Transaction budgetTransaction;
        budgetTransaction.Initialize();

        GetActiveBudget(transactionClass, type, month, &budgetTransaction);

        float amount = budgetTransaction.GetCurrencyAttribute(std::string("AMOUNT"));

        if (amount < 0) return (int)(amount * 100 - 0.5);
        else return (int)(amount * 100 + 0.5);
    }

    void DatabaseLayer::CalculateTotalBreakdown(TotalBreakdown *target, int transactionClass, int mainType, int budgetType, const char *month) {
        TransactionClass tClass;
        tClass.Initialize();
        GetClass(transactionClass, &tClass);

        int nChildren = tClass.GetChildCount();

        target->SetClass(tClass.GetIntAttribute(std::string("ID")));
        target->InitializeAmounts(2);
        target->InitializeChildren(nChildren);

        target->SetAmount(GetTotalAmountMonth(transactionClass, mainType, month), 0);

        Transaction budgetData;
        budgetData.Initialize();
        GetActiveBudget(transactionClass, budgetType, month, &budgetData);

        double amount = budgetData.GetCurrencyAttribute(std::string("AMOUNT"));
        int roundedBudget = 0;

        if (amount < 0) roundedBudget = (int)(amount * 100 - 0.5);
        else roundedBudget = (int)(amount * 100 + 0.5);

        target->SetAmount(roundedBudget, 1);

        for (int i = 0; i < nChildren; i++) {
            CalculateTotalBreakdown(target->GetChild(i), tClass.GetChild(i)->GetIntAttribute(std::string("ID")), mainType, budgetType, month);
        }
    }

    bool DatabaseLayer::GetActiveBudget(int budgetClass, int transactionType, const char *month, Transaction *budget) {
        char buffer[1024];

        sprintf_s(buffer,
            "SELECT MAX(DATE) AS DATE, * FROM `%s` WHERE DATE <= \'%s-01\' AND CLASS_ID = %d AND TYPE_ID = %d;",
            "TRANSACTIONS", month, budgetClass, transactionType);

        return GetDatabaseObject(buffer, budget);
    }

    void DatabaseLayer::CalculateMonthlyBreakdown(TotalBreakdown *target, const std::vector<std::string> &months, int transactionClass, int transactionType, int budgetType) {
        TransactionClass tClass;
        tClass.Initialize();
        GetClass(transactionClass, &tClass);

        int nMonths = months.size(); // Add one to include the start/end month
        int nChildren = tClass.GetChildCount();

        target->SetClass(tClass.GetIntAttribute(std::string("ID")));
        target->InitializeAmounts(nMonths);
        target->InitializeChildren(nChildren);

        for (int i = 0; i < nMonths; i++) {
            std::string month = months[i];
            target->SetAmount(GetTotalAmountMonth(transactionClass, transactionType, month.c_str()), i);
            target->SetBudget(GetTotalBudgetMonth(transactionClass, budgetType, month.c_str()), i);
        }

        for (int i = 0; i < nChildren; i++) {
            CalculateMonthlyBreakdown(target->GetChild(i), months, tClass.GetChild(i)->GetIntAttribute(std::string("ID")), transactionType, budgetType);
        }
    }

    void DatabaseLayer::InsertTransaction(Transaction *transaction) {
		m_insertTransactionQuery.Reset();
		m_insertTransactionQuery.BindString("NAME", transaction->GetStringAttribute("NAME").c_str());
		m_insertTransactionQuery.BindString("DATE", transaction->GetStringAttribute("DATE").c_str());
		m_insertTransactionQuery.BindString("NOTES", transaction->GetStringAttribute("NOTES").c_str());
		m_insertTransactionQuery.BindInt("TYPE_ID", transaction->GetIntAttribute("TYPE_ID"));
		m_insertTransactionQuery.BindInt("CLASS_ID", transaction->GetIntAttribute("CLASS_ID"));
		m_insertTransactionQuery.BindInt("PARENT_ENTITY_ID", transaction->GetIntAttribute("PARENT_ENTITY_ID"));
		m_insertTransactionQuery.BindInt("SOURCE_ACCOUNT_ID", transaction->GetIntAttribute("SOURCE_ACCOUNT_ID"));
		m_insertTransactionQuery.BindInt("AMOUNT", transaction->GetIntAttribute("AMOUNT"));
		m_insertTransactionQuery.BindInt("TARGET_ACCOUNT_ID", transaction->GetIntAttribute("TARGET_ACCOUNT_ID"));
		m_insertTransactionQuery.Step();

		transaction->SetIntAttribute("ID", sqlite3_last_insert_rowid(m_database));
    }

    void DatabaseLayer::UpdateTransaction(Transaction *transaction) {
		m_updateTransactionQuery.Reset();
		m_updateTransactionQuery.BindString("NAME", transaction->GetStringAttribute("NAME").c_str());
		m_updateTransactionQuery.BindString("DATE", transaction->GetStringAttribute("DATE").c_str());
		m_updateTransactionQuery.BindString("NOTES", transaction->GetStringAttribute("NOTES").c_str());
		m_updateTransactionQuery.BindInt("TYPE_ID", transaction->GetIntAttribute("TYPE_ID"));
		m_updateTransactionQuery.BindInt("CLASS_ID", transaction->GetIntAttribute("CLASS_ID"));
		m_updateTransactionQuery.BindInt("PARENT_ENTITY_ID", transaction->GetIntAttribute("PARENT_ENTITY_ID"));
		m_updateTransactionQuery.BindInt("SOURCE_ACCOUNT_ID", transaction->GetIntAttribute("SOURCE_ACCOUNT_ID"));
		m_updateTransactionQuery.BindInt("AMOUNT", transaction->GetIntAttribute("AMOUNT"));
		m_updateTransactionQuery.BindInt("TARGET_ACCOUNT_ID", transaction->GetIntAttribute("TARGET_ACCOUNT_ID"));
		m_updateTransactionQuery.BindInt("ID", transaction->GetIntAttribute("ID"));
		m_insertTransactionQuery.Step();
    }

	void DatabaseLayer::InsertAccount(Account *account) {
		m_insertAccountQuery.Reset();
		m_insertAccountQuery.BindString("NAME", account->GetStringAttribute("NAME").c_str());
		m_insertAccountQuery.BindString("LOCATION", account->GetStringAttribute("LOCATION").c_str());
		m_insertAccountQuery.BindString("NOTES", account->GetStringAttribute("NOTES").c_str());
		m_insertAccountQuery.BindInt("PARENT_ID", account->GetIntAttribute("PARENT_ID"));
		m_insertAccountQuery.Step();

		account->SetIntAttribute("ID", sqlite3_last_insert_rowid(m_database));
	}

	void DatabaseLayer::UpdateAccount(Account *account) {
		m_updateAccountQuery.Reset();
		m_updateAccountQuery.BindInt("ID", account->GetIntAttribute("ID"));
		m_updateAccountQuery.BindString("NAME", account->GetStringAttribute("NAME").c_str());
		m_updateAccountQuery.BindString("LOCATION", account->GetStringAttribute("LOCATION").c_str());
		m_updateAccountQuery.BindString("NOTES", account->GetStringAttribute("NOTES").c_str());
		m_updateAccountQuery.BindInt("PARENT_ID", account->GetIntAttribute("PARENT_ID"));
		m_updateAccountQuery.Step();
	}

	void DatabaseLayer::InsertTransactionClass(TransactionClass *tClass) {
		m_insertTransactionClassQuery.Reset();
		m_insertTransactionClassQuery.BindString("NAME", tClass->GetStringAttribute("NAME").c_str());
		m_insertTransactionClassQuery.BindString("DESCRIPTION", tClass->GetStringAttribute("DESCRIPTION").c_str());
		m_insertTransactionClassQuery.BindInt("PARENT_ID", tClass->GetIntAttribute("PARENT_ID"));
		m_insertTransactionClassQuery.Step();

		tClass->SetIntAttribute("ID", sqlite3_last_insert_rowid(m_database));
	}

	void DatabaseLayer::UpdateTransactionClass(TransactionClass *tClass) {
		m_updateTransactionClassQuery.Reset();
		m_updateTransactionClassQuery.BindInt("ID", tClass->GetIntAttribute("ID"));
		m_updateTransactionClassQuery.BindString("NAME", tClass->GetStringAttribute("NAME").c_str());
		m_updateTransactionClassQuery.BindString("DESCRIPTION", tClass->GetStringAttribute("DESCRIPTION").c_str());
		m_updateTransactionClassQuery.BindInt("PARENT_ID", tClass->GetIntAttribute("PARENT_ID"));
		m_updateTransactionClassQuery.Step();
	}

    bool DatabaseLayer::GetDatabaseObject(const char *query, DatabaseObject *target) {
        int result;
        sqlite3_stmt *statement;

        result = sqlite3_prepare(m_database, query, -1, &statement, NULL);
        result = sqlite3_step(statement);

        int columnCount = sqlite3_column_count(statement);
        int rowCount = 0;

        while (result == SQLITE_ROW) {
            rowCount++;
            for (int i = 0; i < columnCount; i++) {
                const char *columnName = sqlite3_column_name(statement, i);
                DataAttribute::ATTRIBUTE_TYPE columnType = target->GetAttributeType(std::string(columnName));
                int tableFormat = sqlite3_column_type(statement, i);

                if (columnType == DataAttribute::TYPE_INT)
                {
                    target->SetIntAttribute(std::string(columnName), sqlite3_column_int(statement, i));
                } else if (columnType == DataAttribute::TYPE_STRING) {
                    if (tableFormat == SQLITE_NULL) {
                        target->SetStringAttribute(std::string(columnName), std::string(""));
                    } else if (tableFormat == SQLITE_FLOAT) {
                        std::stringstream ss;
                        ss << sqlite3_column_double(statement, i);
                        std::string s = ss.str();
                        target->SetStringAttribute(std::string(columnName), s);

                    } else if (tableFormat == SQLITE_INTEGER) {
                        std::stringstream ss;
                        ss << sqlite3_column_double(statement, i);
                        std::string s = ss.str();
                        target->SetStringAttribute(std::string(columnName), s);
                    } else if (tableFormat == SQLITE_TEXT) {
                        const char *cData = (const char *)sqlite3_column_text(statement, i);
                        std::string data = std::string(cData);
                        target->SetStringAttribute(std::string(columnName), data);
                    }
                } else if (columnType == DataAttribute::TYPE_CURRENCY) {
                    if (tableFormat == SQLITE_INTEGER) target->SetCurrencyAttribute(std::string(columnName), sqlite3_column_int(statement, i));
                    else if (tableFormat == SQLITE_FLOAT) target->SetCurrencyAttribute(std::string(columnName), sqlite3_column_double(statement, i));
                }
            }
            result = sqlite3_step(statement);
        }

        sqlite3_finalize(statement);

        if (rowCount == 0) return false;
        else return true;
    }

    bool DatabaseLayer::GetDatabaseObject(int id, const char *table, DatabaseObject *target) {
        int result;
        char buffer[1024];
        sqlite3_stmt *statement;

        sprintf_s(buffer,
            "SELECT * FROM `%s` WHERE ID = %d;",
            table, id);

        return GetDatabaseObject(buffer, target);
    }

    bool DatabaseLayer::GetTransaction(int id, Transaction *target) {
        return GetDatabaseObject(id, "TRANSACTIONS", target);
    }

    void DatabaseLayer::GetAllAccountSuggestions(const char *reference, FieldInput *targetVector) {
        // Clear suggestions first
        targetVector->ClearSuggestions();

		std::string search = "%%";
		search += reference;
		search += "%%";

		m_searchAccountsQuery.Reset();
		m_searchAccountsQuery.BindString("SEARCH", search.c_str());

		while (m_searchAccountsQuery.Step()) {
			int ID = m_searchAccountsQuery.GetInt(0);

			Account account;
			account.Initialize();
			GetAccount(ID, &account);

			targetVector->AddSuggestion(ID, account.m_name);
		}
    }

    bool DatabaseLayer::GetAccount(int id, Account *target) {
        return GetDatabaseObject(id, "ACCOUNTS", target);
    }

    void DatabaseLayer::GetAllClassSuggestions(const char *reference, FieldInput *targetVector) {
        // Clear suggestions first
        targetVector->ClearSuggestions();

		std::string search = "%%";
		search += reference;
		search += "%%";

		m_searchClassesQuery.Reset();
		m_searchClassesQuery.BindString("SEARCH", search.c_str());
		
		while (m_searchClassesQuery.Step()) {
			int ID = m_searchClassesQuery.GetInt(0);

			TransactionClass tClass;
			tClass.Initialize();
			GetClass(ID, &tClass, false);

			targetVector->AddSuggestion(ID, tClass.m_fullName);
		}
    }

    bool DatabaseLayer::GetClass(int id, TransactionClass *target, bool deepFetch) {
        bool initialResult = GetDatabaseObject(id, "CLASSES", target);
        if (!initialResult) return false;

		if (deepFetch) {
			// Find all children
			int result;
			char buffer[1024];
			sqlite3_stmt *statement;

			sprintf_s(buffer,
				"SELECT ID FROM `CLASSES` WHERE PARENT_ID = %d;",
				target->m_id);

			result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
			result = sqlite3_step(statement);

			while (result == SQLITE_ROW) {
				int ID = sqlite3_column_int(statement, 0);

				TransactionClass *newClass = target->NewChild();
				newClass->SetIntAttribute("ID", ID);

				result = sqlite3_step(statement);
			}

			sqlite3_finalize(statement);

			int nChildren = target->GetChildCount();

			for (int i = 0; i < nChildren; i++) {
				if (!GetClass(target->GetChild(i)->GetIntAttribute("ID"), target->GetChild(i))) {
					return false;
				}
			}
		}

		// Determine full name
		TransactionClass parent;
		parent.Initialize();
		bool foundParent = GetClass(target->m_parentId, &parent, false);

		std::string fullName = target->GetStringAttribute("NAME");

		if (foundParent) {
			fullName = parent.m_fullName + "." + fullName;
		}

		target->m_fullName = fullName;

        return true;
    }

    void DatabaseLayer::GetAllTypeSuggestions(const char *reference, FieldInput *targetVector) {
        // Clear suggestions first
        targetVector->ClearSuggestions();

        // Execute the query

        int result;
        char buffer[1024];
        sqlite3_stmt *statement;

        sprintf_s(buffer,
            "SELECT ID, NAME FROM `TYPES` WHERE NAME LIKE '%%%s%%';",
            reference);

        result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
        result = sqlite3_step(statement);

        while (result == SQLITE_ROW) {
            int ID = sqlite3_column_int(statement, 0);
            std::string name = (char *)sqlite3_column_text(statement, 1);

            targetVector->AddSuggestion(ID, name);

            result = sqlite3_step(statement);
        }

        sqlite3_finalize(statement);
    }

    void DatabaseLayer::GetAllTypes(std::vector<int> &target) {
        // Clear suggestions first
        target.clear();

        // Execute the query

        int result;
        char buffer[1024];
        sqlite3_stmt *statement;

        sprintf_s(buffer,
            "SELECT ID FROM `TYPES`;");

        result = sqlite3_prepare(m_database, buffer, -1, &statement, NULL);
        result = sqlite3_step(statement);

        while (result == SQLITE_ROW) {
            int ID = sqlite3_column_int(statement, 0);

            target.push_back(ID);

            result = sqlite3_step(statement);
        }

        sqlite3_finalize(statement);
    }

    bool DatabaseLayer::GetType(int id, TransactionType *target) {
        return GetDatabaseObject(id, "TYPES", target);
    }

    int DatabaseLayer::StringToInt(const std::string &s) {
        std::stringstream ss(s);
        int result;

        ss >> result;
        return result;
    }

    std::string DatabaseLayer::IntToString(int value) {
        std::stringstream ss;
        ss.fill('0');
        ss << std::setw(2) << value;
        return ss.str();
    }

    void DatabaseLayer::ParseMonth(const std::string &s, int *year, int *month) {
        std::stringstream ss(s);

        std::string yearBuffer, monthBuffer;

        std::getline(ss, yearBuffer, '-');
        std::getline(ss, monthBuffer, '-');

        *year = StringToInt(yearBuffer);
        *month = StringToInt(monthBuffer);
    }

	void DatabaseLayer::Close() {
		// Queries must be freed first or else the 
		// database object cannot be freed
		FreeQueries();

		sqlite3_close(m_database);
		m_database = nullptr;
	}

	void DatabaseLayer::LoadQueries() {
		std::string homePath = m_homePath;

		m_insertTransactionQuery.SetDatabase(m_database);
		m_insertTransactionQuery.LoadFile((homePath + "/assets/sql/new_transaction.sql").c_str());

		m_insertAccountQuery.SetDatabase(m_database);
		m_insertAccountQuery.LoadFile((homePath + "/assets/sql/new_account.sql").c_str());

		m_updateAccountQuery.SetDatabase(m_database);
		m_updateAccountQuery.LoadFile((homePath + "/assets/sql/update_account.sql").c_str());

		m_insertTransactionClassQuery.SetDatabase(m_database);
		m_insertTransactionClassQuery.LoadFile((homePath + "/assets/sql/new_class.sql").c_str());

		m_updateTransactionClassQuery.SetDatabase(m_database);
		m_updateTransactionClassQuery.LoadFile((homePath + "/assets/sql/update_class.sql").c_str());

		m_updateTransactionQuery.SetDatabase(m_database);
		m_updateTransactionQuery.LoadFile((homePath + "/assets/sql/update_transaction.sql").c_str());

		m_searchClassesQuery.SetDatabase(m_database);
		m_searchClassesQuery.LoadFile((homePath + "/assets/sql/search_classes.sql").c_str());

		m_searchAccountsQuery.SetDatabase(m_database);
		m_searchAccountsQuery.LoadFile((homePath + "/assets/sql/search_accounts.sql").c_str());
	}

	void DatabaseLayer::FreeQueries() {
		m_insertTransactionQuery.Free();
		m_insertAccountQuery.Free();
		m_updateAccountQuery.Free();
		m_updateTransactionQuery.Free();
		m_insertTransactionClassQuery.Free();
		m_updateTransactionClassQuery.Free();
		m_searchClassesQuery.Free();
		m_searchAccountsQuery.Free();
	}

} /* namespace pft */
