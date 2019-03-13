#include "gtest/gtest.h"

#include <config.h>

#include <database_layer.h>
#include <transaction.h>
using namespace pft;

void DestroyIntegrationTestDB(DatabaseLayer *db=nullptr) {
	if (db != nullptr && db->IsOpen()) db->Close();

	int result = remove("integration_test.db");
}

TEST(DatabaseLayerTests, DatabaseLayerSanityCheck) {
	DestroyIntegrationTestDB();

	DatabaseLayer db;
	db.SetHomePath(HOME_PATH);
	db.OpenDatabase("integration_test.db");

	EXPECT_TRUE(db.DoesTableExist("ACCOUNTS"));
	EXPECT_TRUE(db.DoesTableExist("CLASSES"));
	EXPECT_TRUE(db.DoesTableExist("TRANSACTIONS"));
	EXPECT_TRUE(db.DoesTableExist("TYPES"));

	DestroyIntegrationTestDB(&db);
}

 TEST(DatabaseLayerTests, DatabaseLayerTxnInsertion) {
	DestroyIntegrationTestDB();

	DatabaseLayer db;
	db.SetHomePath(HOME_PATH);
	db.OpenDatabase("integration_test.db");

	Transaction transaction;
	transaction.RegisterAttributes();
	transaction.m_amount = 100;
	transaction.m_classId = 0xCC;
	transaction.m_date = "2019-03-13";
	transaction.m_name = "TEST";
	transaction.m_notes = "NOTES";
	transaction.m_parentEntityId = -1;
	transaction.m_sourceAccountId = 0x55;
	transaction.m_targetAccountId = 0x66;
	transaction.m_typeId = 0x77;
	db.InsertTransaction(&transaction);

	EXPECT_EQ(transaction.m_id, 1);

	// Retrieve the transaction
	Transaction target;
	target.RegisterAttributes();
	db.GetTransaction(transaction.m_id, &target);

	EXPECT_EQ(transaction.m_amount, target.m_amount);
	EXPECT_EQ(transaction.m_classId, target.m_classId);
	EXPECT_EQ(transaction.m_date, target.m_date);
	EXPECT_EQ(transaction.m_name, target.m_name);
	EXPECT_EQ(transaction.m_notes, target.m_notes);
	EXPECT_EQ(transaction.m_parentEntityId, target.m_parentEntityId);
	EXPECT_EQ(transaction.m_sourceAccountId, target.m_sourceAccountId);
	EXPECT_EQ(transaction.m_targetAccountId, target.m_targetAccountId);
	EXPECT_EQ(transaction.m_typeId, target.m_typeId);
	EXPECT_EQ(transaction.m_id, target.m_id);

	DestroyIntegrationTestDB(&db);
}
