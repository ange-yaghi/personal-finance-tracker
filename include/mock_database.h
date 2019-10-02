#ifndef PFT_MOCK_DATABASE_H
#define PFT_MOCK_DATABASE_H

#include "database_layer.h"

namespace pft {

    class MockDatabase : public DatabaseLayer {
    public:
        MockDatabase();
        ~MockDatabase();

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
        virtual bool GetClass(int id, TransactionClass *target, bool deepFetch = true);

        // Get suggestions from types
        virtual void GetAllTypeSuggestions(const char *reference, FieldInput *targetVector);

        // Get all types
        virtual void GetAllTypes(std::vector<int> &target);

        // Find a type based on id
        virtual bool GetType(int id, TransactionType *target);
    };

} /* namespace pft */

#endif /* PFT_MOCK_DATABASE_H */
