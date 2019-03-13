#include "gtest/gtest.h"

#include <config.h>

#include <database_query.h>
#include <database_layer.h>
using namespace pft;

#include <stdio.h>

void DestroyTestDB(DatabaseLayer &db) {
	if (db.IsOpen()) db.Close();
	
	int result = remove("test.db");
}

bool GenerateTestDB(DatabaseLayer &db) {
	DestroyTestDB(db);
	db.OpenDatabase("test.db", true);

	DatabaseQuery generationQuery;
	generationQuery.SetDatabase(db.GetDatabase());
	generationQuery.LoadFile(SQL_DIR "test_db_generation.sql");
	generationQuery.ExecuteAll();

	generationQuery.Free();

	return true;
}

TEST(SanityCheck, SanityCheck) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(QueryTests, QuerySanityCheck) {
	DatabaseLayer db;
	bool result = GenerateTestDB(db);

	EXPECT_TRUE(result);

	DestroyTestDB(db);
}

TEST(QueryTests, QueryInsertion) {
	DatabaseLayer db;
	GenerateTestDB(db);

	DatabaseQuery insertionQuery;
	insertionQuery.SetDatabase(db.GetDatabase());
	insertionQuery.Compile(
		"INSERT INTO TYPES (NAME, DESCRIPTION) VALUES (\"Test\", \"Desc\");");
	bool result = insertionQuery.Step();

	EXPECT_FALSE(result);

	DatabaseQuery query;
	query.SetDatabase(db.GetDatabase());
	query.Compile("SELECT * FROM TYPES;");
	result = query.Step();

	EXPECT_TRUE(result);

	EXPECT_EQ(query.GetInt(0), 1);
	EXPECT_EQ(query.GetString(1), "Test");
	EXPECT_EQ(query.GetString(2), "Desc");

	result = query.Step();
	EXPECT_FALSE(result);

	insertionQuery.Free();
	query.Free();

	DestroyTestDB(db);
}

TEST(QueryTests, QueryInsertionReset) {
	DatabaseLayer db;
	GenerateTestDB(db);

	DatabaseQuery insertionQuery;
	insertionQuery.SetDatabase(db.GetDatabase());
	insertionQuery.Compile(
		"INSERT INTO TYPES (NAME, DESCRIPTION) VALUES (\"Test\", \"Desc\");");
	bool result = insertionQuery.Step();

	EXPECT_FALSE(result);

	DatabaseQuery query;
	query.SetDatabase(db.GetDatabase());
	query.Compile("SELECT * FROM TYPES;");

	for (int i = 0; i < 2; i++) {
		result = query.Step();

		EXPECT_TRUE(result);

		EXPECT_EQ(query.GetInt(0), 1);
		EXPECT_EQ(query.GetString(1), "Test");
		EXPECT_EQ(query.GetString(2), "Desc");

		result = query.Step();
		EXPECT_FALSE(result);

		query.Reset();
	}

	insertionQuery.Free();
	query.Free();

	DestroyTestDB(db);
}

TEST(QueryTests, QueryInsertionOtherTable) {
	DatabaseLayer db;
	GenerateTestDB(db);

	DatabaseQuery insertionQuery;
	insertionQuery.SetDatabase(db.GetDatabase());
	insertionQuery.Compile(
		"INSERT INTO CLASSES (NAME, PARENT_ID) VALUES (\"Test\", 0);");
	bool result = insertionQuery.Step();

	EXPECT_FALSE(result);

	DatabaseQuery query;
	query.SetDatabase(db.GetDatabase());
	query.Compile("SELECT * FROM CLASSES;");
	result = query.Step();

	EXPECT_TRUE(result);

	EXPECT_EQ(query.GetInt(0), 1);
	EXPECT_EQ(query.GetString(1), "Test");
	EXPECT_EQ(query.GetInt(2), 0);

	result = query.Step();
	EXPECT_FALSE(result);

	insertionQuery.Free();
	query.Free();

	DestroyTestDB(db);
}

TEST(QueryTests, QueryParameterTest) {
	DatabaseLayer db;
	GenerateTestDB(db);

	DatabaseQuery insertionQuery;
	insertionQuery.SetDatabase(db.GetDatabase());
	insertionQuery.Compile(
		"INSERT INTO CLASSES (NAME, PARENT_ID) VALUES ($NAME, $PARENT_ID);");
	insertionQuery.BindString("NAME", "Test");
	insertionQuery.BindInt("PARENT_ID", 0);
	bool result = insertionQuery.Step();

	const char *t = sqlite3_errmsg(db.GetDatabase());

	EXPECT_FALSE(result);

	DatabaseQuery query;
	query.SetDatabase(db.GetDatabase());
	query.Compile("SELECT * FROM CLASSES;");

	// Bind parameters
	result = query.Step();
	EXPECT_TRUE(result);

	EXPECT_EQ(query.GetInt(0), 1);
	EXPECT_EQ(query.GetString(1), "Test");
	EXPECT_EQ(query.GetInt(2), 0);

	result = query.Step();
	EXPECT_FALSE(result);

	insertionQuery.Free();
	query.Free();

	DestroyTestDB(db);
}
