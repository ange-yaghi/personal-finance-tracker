#include "transaction_form.h"

#include <transaction.h>
#include <transaction_class.h>
#include <account.h>
#include <counterparty.h>
#include <transaction_type.h>

#include <database_layer.h>

TransactionForm::TransactionForm()
{

}

TransactionForm::~TransactionForm()
{

}

void TransactionForm::Initialize()
{
	Form::Initialize();

	m_nameField.SetFieldName(std::string("NAME"));
	m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_amountField.SetFieldName(std::string("AMOUNT"));
	m_amountField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_counterpartyField.SetFieldName(std::string("COUNTERPARTY"));
	m_counterpartyField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_classField.SetFieldName(std::string("CLASS"));
	m_classField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_accountField.SetFieldName(std::string("ACCOUNT"));
	m_accountField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_typeField.SetFieldName(std::string("TYPE"));
	m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_parentIdField.SetFieldName(std::string("PARENT ENTITY ID"));
	m_parentIdField.SetInputType(FieldInput::INPUT_INT);

	m_dateField.SetFieldName(std::string("DATE"));
	m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	RegisterField(&m_nameField);
	RegisterField(&m_dateField);
	RegisterField(&m_typeField);
	RegisterField(&m_classField);
	RegisterField(&m_counterpartyField);
	RegisterField(&m_parentIdField);
	RegisterField(&m_accountField);
	RegisterField(&m_amountField);
}

void TransactionForm::Copy(Form *target)
{

}

void TransactionForm::Populate(Transaction *transaction)
{
	TransactionClass transactionClass;
	Account account;
	Counterparty counterparty;
	TransactionType type;

	transactionClass.Initialize();
	account.Initialize();
	counterparty.Initialize();
	type.Initialize();

	// Populate related objects
	m_databaseLayer->GetAccount(transaction->GetIntAttribute(std::string("ACCOUNT_ID")), &account);
	m_databaseLayer->GetCounterparty(transaction->GetIntAttribute(std::string("COUNTERPARTY_ID")), &counterparty);
	m_databaseLayer->GetClass(transaction->GetIntAttribute(std::string("CLASS_ID")), &transactionClass);
	m_databaseLayer->GetType(transaction->GetIntAttribute(std::string("TYPE_ID")), &type);

	// Populate fields
	m_nameField.SetCurrentValue(transaction->GetStringAttribute(std::string("NAME")));
	m_amountField.SetCurrentValue(transaction->GetCurrencyAttribute(std::string("AMOUNT")));

	m_counterpartyField.SetCurrentValue(FieldInput::Suggestion(counterparty.GetStringAttribute(std::string("NAME")), counterparty.GetIntAttribute(std::string("ID"))));
	m_classField.SetCurrentValue(FieldInput::Suggestion(transactionClass.GetStringAttribute(std::string("NAME")), transactionClass.GetIntAttribute(std::string("ID"))));
	m_accountField.SetCurrentValue(FieldInput::Suggestion(account.GetStringAttribute(std::string("NAME")), account.GetIntAttribute(std::string("ID"))));
	m_typeField.SetCurrentValue(FieldInput::Suggestion(type.GetStringAttribute(std::string("NAME")), type.GetIntAttribute(std::string("ID"))));

	m_parentIdField.SetCurrentValue(transaction->GetIntAttribute(std::string("PARENT_ENTITY_ID")));
	m_dateField.SetCurrentValue(transaction->GetStringAttribute(std::string("DATE")));
}

void TransactionForm::PopulateTransaction(Transaction *target)
{
	target->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue());
	target->SetCurrencyAttribute(std::string("AMOUNT"), m_amountField.GetDoubleValue());

	target->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_counterpartyField.GetCurrentSuggestion()->Id);
	target->SetIntAttribute(std::string("CLASS_ID"), m_classField.GetCurrentSuggestion()->Id);
	target->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
	target->SetIntAttribute(std::string("ACCOUNT_ID"), m_accountField.GetCurrentSuggestion()->Id);

	target->SetIntAttribute(std::string("PARENT_ENTITY_ID"), m_parentIdField.GetIntValue());
	target->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());
}