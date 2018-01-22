#ifndef DATABASE_LAYER_H
#define DATABASE_LAYER_H

#include <sqlite3.h>

class Transaction;
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

	// Get suggestions from counterparties
	void GetAllCounterpartySuggestions(const char *reference, FieldInput *targetVector);

	// Get suggestions from accounts
	void GetAllAccountSuggestions(const char *reference, FieldInput *targetVector);

	// Get suggestions from accounts
	void GetAllClassSuggestions(const char *reference, FieldInput *targetVector);

	// Get suggestions from types
	void GetAllTypeSuggestions(const char *reference, FieldInput *targetVector);

	Toccata_Settings Settings;

protected:

	DATABASE_VERSION m_version;
	sqlite3 *m_database;

};

#endif /* DATABASE_LAYER_H */