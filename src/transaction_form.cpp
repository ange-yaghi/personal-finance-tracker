#include "transaction_form.h"

#include <transaction.h>
#include <transaction_class.h>
#include <account.h>
#include <transaction_type.h>

#include <database_layer.h>

pft::TransactionForm::TransactionForm() {

}

pft::TransactionForm::~TransactionForm() {

}

void pft::TransactionForm::Initialize() {
    Form::Initialize();

    m_nameField.SetFieldName(std::string("NAME"));
    m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

    m_amountField.SetFieldName(std::string("AMOUNT"));
    m_amountField.SetInputType(FieldInput::INPUT_SHORT_STRING);

    m_counterpartyField.SetFieldName(std::string("TARGET ACCOUNT"));
    m_counterpartyField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_classField.SetFieldName(std::string("CLASS"));
    m_classField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_accountField.SetFieldName(std::string("SOURCE ACCOUNT"));
    m_accountField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_typeField.SetFieldName(std::string("TYPE"));
    m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_parentIdField.SetFieldName(std::string("PARENT ENTITY ID"));
    m_parentIdField.SetInputType(FieldInput::INPUT_INT);

    m_dateField.SetFieldName(std::string("DATE"));
    m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);

    /* Register all fields */
    RegisterField(&m_nameField);
    RegisterField(&m_dateField);
    RegisterField(&m_typeField);
    RegisterField(&m_classField);
    RegisterField(&m_counterpartyField);
    RegisterField(&m_parentIdField);
    RegisterField(&m_accountField);
    RegisterField(&m_amountField);
}

void pft::TransactionForm::Copy(Form *target) {
    // UNIMPLEMENTED
}

void pft::TransactionForm::PopulateFields(Transaction *transaction) {
    TransactionClass transactionClass;
    Account sourceAccount;
    Account targetAccount;
    TransactionType type;

    transactionClass.Initialize();
    sourceAccount.Initialize();
    targetAccount.Initialize();
    type.Initialize();

    // Fetch related objects from the database
    m_databaseLayer->GetAccount(transaction->GetIntAttribute(std::string("SOURCE_ACCOUNT_ID")), &sourceAccount);
    m_databaseLayer->GetAccount(transaction->GetIntAttribute(std::string("TARGET_ACCOUNT_ID")), &targetAccount);
    m_databaseLayer->GetClass(transaction->GetIntAttribute(std::string("CLASS_ID")), &transactionClass);
    m_databaseLayer->GetType(transaction->GetIntAttribute(std::string("TYPE_ID")), &type);

    // Populate fields
    m_nameField.SetCurrentValue(transaction->GetStringAttribute(std::string("NAME")));
    m_amountField.SetCurrentValue(transaction->GetCurrencyAttribute(std::string("AMOUNT")));
    m_counterpartyField.SetCurrentValue(FieldInput::Suggestion(targetAccount.GetStringAttribute(std::string("NAME")), targetAccount.GetIntAttribute(std::string("ID"))));
    m_classField.SetCurrentValue(FieldInput::Suggestion(transactionClass.GetStringAttribute(std::string("NAME")), transactionClass.GetIntAttribute(std::string("ID"))));
    m_accountField.SetCurrentValue(FieldInput::Suggestion(sourceAccount.GetStringAttribute(std::string("NAME")), sourceAccount.GetIntAttribute(std::string("ID"))));
    m_typeField.SetCurrentValue(FieldInput::Suggestion(type.GetStringAttribute(std::string("NAME")), type.GetIntAttribute(std::string("ID"))));
    m_parentIdField.SetCurrentValue(transaction->GetIntAttribute(std::string("PARENT_ENTITY_ID")));
    m_dateField.SetCurrentValue(transaction->GetStringAttribute(std::string("DATE")));
}

void pft::TransactionForm::PopulateTransaction(Transaction *target) {
    target->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue());
    target->SetCurrencyAttribute(std::string("AMOUNT"), m_amountField.GetDoubleValue());
    target->SetIntAttribute(std::string("TARGET_ACCOUNT_ID"), m_counterpartyField.GetCurrentSuggestion()->Id);
    target->SetIntAttribute(std::string("CLASS_ID"), m_classField.GetCurrentSuggestion()->Id);
    target->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
    target->SetIntAttribute(std::string("SOURCE_ACCOUNT_ID"), m_accountField.GetCurrentSuggestion()->Id);
    target->SetIntAttribute(std::string("PARENT_ENTITY_ID"), m_parentIdField.GetIntValue());
    target->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());
}
