#ifndef PFT_DATABASE_LAYER_H
#define PFT_DATABASE_LAYER_H

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

    class DatabaseLayer {
    public:
        DatabaseLayer();
        ~DatabaseLayer();

        // Get bank sum
        virtual int GetAccountBalance(int account, int typeId, const char *date) = 0;

        // Get total amount by month
        virtual int GetTotalAmountMonth(int transactionClass, int type, const char *month) = 0;

        // Get total budget by month
        virtual int GetTotalBudgetMonth(int transactionClass, int type, const char *month) = 0;

        // Get total amount by month
        virtual void CalculateTotalBreakdown(TotalBreakdown *target, int transactionClass, int mainType, int budgetType, const char *month) = 0;

        // Get the current budget
        virtual bool GetActiveBudget(int budgetClass, int transactionType, const char *month, Transaction *budget) = 0;

        // Get total amount by month
        virtual void CalculateMonthlyBreakdown(TotalBreakdown *target, const std::vector<std::string> &months, int transactionClass, int transactionType, int budgetType) = 0;

        // Add a transaction to the database
        virtual void InsertTransaction(Transaction *transaction) = 0;

        // Update a transaction to the database
        virtual void UpdateTransaction(Transaction *transaction) = 0;

        // Add an account to the database
        virtual void InsertAccount(Account *account) = 0;

        // Update account information
        virtual void UpdateAccount(Account *account) = 0;

        // Add a transaction class to the database
        virtual void InsertTransactionClass(TransactionClass *tClass) = 0;

        // Update a transaction class
        virtual void UpdateTransactionClass(TransactionClass *tClass) = 0;

        // Add a transaction type to the database
        virtual void InsertTransactionType(TransactionType *type) = 0;

        // Update a transaction type
        virtual void UpdateTransactionType(TransactionType *type) = 0;

        // Find an object using a custom query
        virtual bool GetDatabaseObject(const char *query, DatabaseObject *target) = 0;

        // Find a transaction based on id
        virtual bool GetDatabaseObject(int id, const char *table, DatabaseObject *target) = 0;

        // Find a transaction based on id
        virtual bool GetTransaction(int id, Transaction *target) = 0;

        // Get suggestions from accounts
        virtual void GetAllAccountSuggestions(const char *reference, FieldInput *targetVector) = 0;

        // Find an account based on id
        virtual bool GetAccount(int id, Account *target) = 0;

        // Get suggestions from accounts
        virtual void GetAllClassSuggestions(const char *reference, FieldInput *targetVector) = 0;

        // Find a class based on id
        virtual bool GetClass(int id, TransactionClass *target, bool deepFetch = true) = 0;

        // Get suggestions from types
        virtual void GetAllTypeSuggestions(const char *reference, FieldInput *targetVector) = 0;

        // Get all types
        virtual void GetAllTypes(std::vector<int> &target) = 0;

        // Find a type based on id
        virtual bool GetType(int id, TransactionType *target) = 0;

        static int StringToInt(const std::string &s);
        static std::string IntToString(int value);
        static void ParseMonth(const std::string &s, int *year, int *month);

    protected:
        std::vector<Account *> m_accounts;
        std::vector<TransactionClass *> m_classes;
        std::vector<Transaction *> m_transactions;
        std::vector<TransactionType *> m_types;
    };

} /* namespace pft */

#endif /* PFT_DATABASE_LAYER_H */

