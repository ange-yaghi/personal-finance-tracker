#include <transfer_form.h>

#include <transaction.h>
#include <transaction_class.h>
#include <account.h>
#include <counterparty.h>
#include <transaction_type.h>

#include <database_layer.h>

TransferForm::TransferForm()
{

}

TransferForm::~TransferForm()
{

}

void TransferForm::Initialize()
{
	Form::Initialize();

	m_nameField.SetFieldName(std::string("NAME"));
	m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_amountField.SetFieldName(std::string("AMOUNT"));
	m_amountField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_intermediateAccount.SetFieldName(std::string("INTERMEDIATE ACCOUNT"));
	m_intermediateAccount.SetInputType(FieldInput::INPUT_LOOKUP);

	m_parentClassField.SetFieldName(std::string("PARENT CLASS"));
	m_parentClassField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_childClassField.SetFieldName(std::string("CHILD CLASS"));
	m_childClassField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_sourceAccount.SetFieldName(std::string("SOURCE ACCOUNT"));
	m_sourceAccount.SetInputType(FieldInput::INPUT_LOOKUP);

	m_destinationAccount.SetFieldName(std::string("DESTINATION ACCOUNT"));
	m_destinationAccount.SetInputType(FieldInput::INPUT_LOOKUP);

	m_overallSourceAccount.SetFieldName(std::string("OVERALL SOURCE ACCOUNT"));
	m_overallSourceAccount.SetInputType(FieldInput::INPUT_LOOKUP);

	m_overallCounterpartyField.SetFieldName(std::string("OVERALL COUNTERPARTY"));
	m_overallCounterpartyField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_containerType.SetFieldName(std::string("CONTAINER TYPE"));
	m_containerType.SetInputType(FieldInput::INPUT_LOOKUP);

	m_typeField.SetFieldName(std::string("CHILD TYPE"));
	m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

	m_parentIdField.SetFieldName(std::string("PARENT ENTITY ID"));
	m_parentIdField.SetInputType(FieldInput::INPUT_INT);

	m_dateField.SetFieldName(std::string("DATE"));
	m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	RegisterField(&m_nameField);
	RegisterField(&m_parentClassField);
	RegisterField(&m_childClassField);
	RegisterField(&m_containerType);
	RegisterField(&m_typeField);
	RegisterField(&m_amountField);
	RegisterField(&m_parentIdField);
	RegisterField(&m_overallSourceAccount);
	RegisterField(&m_overallCounterpartyField);
	RegisterField(&m_sourceAccount);
	RegisterField(&m_intermediateAccount);
	RegisterField(&m_destinationAccount);
	RegisterField(&m_dateField);
}

void TransferForm::Copy(Form *target)
{

}

void TransferForm::PopulateTransactions(Transaction *container, Transaction *fromSource, Transaction *toDest)
{
	// TOP LEVEL TRANSACTION
	container->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue());
	container->SetCurrencyAttribute(std::string("AMOUNT"), 0.00);

	container->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_overallCounterpartyField.GetCurrentSuggestion()->Id);
	container->SetIntAttribute(std::string("CLASS_ID"), m_parentClassField.GetCurrentSuggestion()->Id);
	container->SetIntAttribute(std::string("TYPE_ID"), m_containerType.GetCurrentSuggestion()->Id);
	container->SetIntAttribute(std::string("ACCOUNT_ID"), m_overallSourceAccount.GetCurrentSuggestion()->Id);

	container->SetIntAttribute(std::string("PARENT_ENTITY_ID"), m_parentIdField.GetIntValue());
	container->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

	// CREDIT
	fromSource->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (CREDIT)");
	fromSource->SetCurrencyAttribute(std::string("AMOUNT"), -m_amountField.GetDoubleValue());

	fromSource->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);
	fromSource->SetIntAttribute(std::string("CLASS_ID"), m_childClassField.GetCurrentSuggestion()->Id);
	fromSource->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
	fromSource->SetIntAttribute(std::string("ACCOUNT_ID"), m_sourceAccount.GetCurrentSuggestion()->Id);

	fromSource->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

	// DEBIT
	toDest->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (DEBIT)");
	toDest->SetCurrencyAttribute(std::string("AMOUNT"), m_amountField.GetDoubleValue());

	toDest->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);
	toDest->SetIntAttribute(std::string("CLASS_ID"), m_childClassField.GetCurrentSuggestion()->Id);
	toDest->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
	toDest->SetIntAttribute(std::string("ACCOUNT_ID"), m_destinationAccount.GetCurrentSuggestion()->Id);

	toDest->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());
}