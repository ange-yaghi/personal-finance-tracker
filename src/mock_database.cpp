#include "../include/mock_database.h"

pft::MockDatabase::MockDatabase() {
    /* void */
}

pft::MockDatabase::~MockDatabase() {
    /* void */
}

int pft::MockDatabase::GetAccountBalance(int account, int typeId, const char *date) {
    return 0;
}

int pft::MockDatabase::GetTotalAmountMonth(int transactionClass, int type, const char *month) {
    return 0;
}

int pft::MockDatabase::GetTotalBudgetMonth(int transactionClass, int type, const char *month) {
    return 0;
}

void pft::MockDatabase::CalculateTotalBreakdown(TotalBreakdown *target, int transactionClass, int mainType, int budgetType, const char *month) {
    /* void */
}

bool pft::MockDatabase::GetActiveBudget(int budgetClass, int transactionType, const char *month, Transaction *budget) {
    return false;
}

void pft::MockDatabase::CalculateMonthlyBreakdown(TotalBreakdown * target, const std::vector<std::string>& months, int transactionClass, int transactionType, int budgetType) {
    /* void */
}

void pft::MockDatabase::InsertTransaction(Transaction *transaction) {
}

void pft::MockDatabase::UpdateTransaction(Transaction *transaction) {
}

void pft::MockDatabase::InsertAccount(Account *account) {
}

void pft::MockDatabase::UpdateAccount(Account *account) {
}

void pft::MockDatabase::InsertTransactionClass(TransactionClass *tClass) {
}

void pft::MockDatabase::UpdateTransactionClass(TransactionClass *tClass) {
}

void pft::MockDatabase::InsertTransactionType(TransactionType *type) {
}

void pft::MockDatabase::UpdateTransactionType(TransactionType *type) {
}

bool pft::MockDatabase::GetDatabaseObject(const char *query, DatabaseObject *target) {
    return false;
}

bool pft::MockDatabase::GetDatabaseObject(int id, const char *table, DatabaseObject *target) {
    return false;
}

bool pft::MockDatabase::GetTransaction(int id, Transaction *target) {
    return false;
}

void pft::MockDatabase::GetAllAccountSuggestions(const char *reference, FieldInput *targetVector) {
}

bool pft::MockDatabase::GetAccount(int id, Account *target) {
    return false;
}

void pft::MockDatabase::GetAllClassSuggestions(const char *reference, FieldInput *targetVector) {
}

bool pft::MockDatabase::GetClass(int id, TransactionClass *target, bool deepFetch) {
    return false;
}

void pft::MockDatabase::GetAllTypeSuggestions(const char *reference, FieldInput *targetVector) {
}

void pft::MockDatabase::GetAllTypes(std::vector<int> &target) {
}

bool pft::MockDatabase::GetType(int id, TransactionType *target) {
    return false;
}
