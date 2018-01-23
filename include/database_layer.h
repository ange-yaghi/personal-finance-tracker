#ifndef DATABASE_LAYER_H
#define DATABASE_LAYER_H

#include <sqlite3.h>

class Transaction;
class TransactionClass;
class TransactionType;
class Counterparty;
class Account;
class FieldInput;
class DatabaseLayer
{

public:

	enum DATABASE_VERSION
	{

		VERSION_1_0,

	};

	static const DATABASE_VERSION CurrentVersion = VERSION_1_0;

	enum TABLE_TYPE
	{

		TABLE_APPLICATION,
		TABLE_SONG_INFORMATION,
		TABLE_PERFORMANCE,

	};

	struct Toccata_Settings
	{

		int PerformanceID;
		DATABASE_VERSION FileVersion;

	};

	static const char *ReportColumns_v1_0;

public:

	DatabaseLayer();
	~DatabaseLayer();

	void OpenDatabase();
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
	int GetBankSum(const char *date);

	// Add a transaction to the database
	void InsertTransaction(Transaction *transaction);

	// Update a transaction to the database
	void UpdateTransaction(Transaction *transaction);

	// Find a transaction based on id
	bool GetTransaction(int id, Transaction *target);

	// Get suggestions from counterparties
	void GetAllCounterpartySuggestions(const char *reference, FieldInput *targetVector);

	// Find a counterparty based on id
	bool GetCounterparty(int id, Counterparty *target);

	// Get suggestions from accounts
	void GetAllAccountSuggestions(const char *reference, FieldInput *targetVector);

	// Find an account based on id
	bool GetAccount(int id, Account *target);

	// Get suggestions from accounts
	void GetAllClassSuggestions(const char *reference, FieldInput *targetVector);

	// Find a class based on id
	bool GetClass(int id, TransactionClass *target);

	// Get suggestions from types
	void GetAllTypeSuggestions(const char *reference, FieldInput *targetVector);

	// Find a type based on id
	bool GetType(int id, TransactionType *target);

	Toccata_Settings Settings;

protected:

	DATABASE_VERSION m_version;
	sqlite3 *m_database;

};

#endif /* DATABASE_LAYER_H */