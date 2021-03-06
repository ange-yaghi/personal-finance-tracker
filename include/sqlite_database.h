#ifndef PFT_SQLITE_DATABASE_H
#define PFT_SQLITE_DATABASE_H

#include "database_layer.h"

#include "database_query.h"
#include "sqlite_forward_decl.h"

#include <vector>

namespace pft {

    /* Forward Declarations */
    class Transaction;
    class TransactionClass;
    class TransactionType;
    class Counterparty;
    class Account;
    class FieldInput;
    class DatabaseObject;
    class TotalBreakdown;

    class SqliteDatabase : public DatabaseLayer {
    public:
        enum DATABASE_VERSION {
            VERSION_1_0,
        };

        static const DATABASE_VERSION CurrentVersion = VERSION_1_0;

        enum TABLE_TYPE {
            TABLE_APPLICATION,
            TABLE_SONG_INFORMATION,
            TABLE_PERFORMANCE,
        };

        struct DatabaseSettings {
            int PerformanceID;
            DATABASE_VERSION FileVersion;
        };

        static const char *ReportColumns_v1_0;

    public:

        SqliteDatabase();
        ~SqliteDatabase();

		void Initialize();
        void OpenDatabase(const char *fileName, bool testMode=false);
        void InitializeDatabase();
        void PortDatabase(DATABASE_VERSION newVersion);

        /* General purpose SQLite Wrappers */

        // Check whether a table exists
        bool DoesTableExist(const char *name);

        // Rename a table
        void RenameTable(const char *name, const char *newName);

        // Create a new table
        void CreateTable(const char *name, const char *columns);

        // Insert a new row in a table
        void Insert(const char *table, const char *data);

        // Update an entry in the table using a simple lookup scheme
        void SimpleUpdate(const char *table, const char *idColumn, const char *id, const char *values);

        // Create a table name
        void CreateTableName(char *string);

        // Get bank sum
        virtual int GetAccountBalance(int account, int typeId, const char *date);

        // Get total amount by month
        virtual int GetTotalAmountMonth(int transactionClass, int type, const char *month);

        // Get total budget by month
        virtual int GetTotalBudgetMonth(int transactionClass, int type, const char *month);

        // Get total amount by month
        virtual void CalculateTotalBreakdown(TotalBreakdown *target, int transactionClass, int mainType, int budgetType, const char *month);

        // Get the current budget
        virtual bool GetActiveBudget(int budgetClass, int transactionType, const char *month, Transaction *budget);

        // Get total amount by month
        virtual void CalculateMonthlyBreakdown(TotalBreakdown *target, const std::vector<std::string> &months, int transactionClass, int transactionType, int budgetType);

        // Add a transaction to the database
        virtual void InsertTransaction(Transaction *transaction);

        // Update a transaction to the database
        virtual void UpdateTransaction(Transaction *transaction);

		// Add an account to the database
        virtual void InsertAccount(Account *account);

		// Update account information
        virtual void UpdateAccount(Account *account);

		// Add a transaction class to the database
        virtual void InsertTransactionClass(TransactionClass *tClass);

		// Update a transaction class
        virtual void UpdateTransactionClass(TransactionClass *tClass);

		// Add a transaction type to the database
        virtual void InsertTransactionType(TransactionType *type);

		// Update a transaction type
        virtual void UpdateTransactionType(TransactionType *type);

        // Find an object using a custom query
        virtual bool GetDatabaseObject(const char *query, DatabaseObject *target);

        // Find a transaction based on id
        virtual bool GetDatabaseObject(int id, const char *table, DatabaseObject *target);

        // Find a transaction based on id
        virtual bool GetTransaction(int id, Transaction *target);

        // Get suggestions from accounts
        virtual void GetAllAccountSuggestions(const char *reference, FieldInput *targetVector);

        // Find an account based on id
        virtual bool GetAccount(int id, Account *target);

        // Get suggestions from accounts
        virtual void GetAllClassSuggestions(const char *reference, FieldInput *targetVector);

        // Find a class based on id
        virtual bool GetClass(int id, TransactionClass *target, bool deepFetch=true);

        // Get suggestions from types
        virtual void GetAllTypeSuggestions(const char *reference, FieldInput *targetVector);

        // Get all types
        virtual void GetAllTypes(std::vector<int> &target);

        // Find a type based on id
        virtual bool GetType(int id, TransactionType *target);

        DatabaseSettings Settings;

		bool IsOpen() const { return m_database != nullptr; }

		void Close();

		void SetHomePath(const char *homePath) { m_homePath = homePath; }
		const char *GetHomePath() const { return m_homePath; }

		void LoadQueries();
		void FreeQueries();

		// SQLite specific
		sqlite3 *GetDatabase() const { return m_database; }

    protected:
        DATABASE_VERSION m_version;
        sqlite3 *m_database;

		const char *m_homePath;

	protected:
		DatabaseQuery m_initializeDatabaseQuery;
		DatabaseQuery m_insertTransactionQuery;
		DatabaseQuery m_updateTransactionQuery;
		DatabaseQuery m_insertAccountQuery;
		DatabaseQuery m_updateAccountQuery;
		DatabaseQuery m_insertTransactionClassQuery;
		DatabaseQuery m_updateTransactionClassQuery;
		DatabaseQuery m_searchClassesQuery;
		DatabaseQuery m_searchAccountsQuery;
		DatabaseQuery m_insertTransactionTypeQuery;
		DatabaseQuery m_updateTransactionTypeQuery;
    };

} /* namespace pft */

#endif /* PFT_SQLITE_DATABASE_H */
