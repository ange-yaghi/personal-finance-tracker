#include "transaction_form.h"

TransactionForm::TransactionForm()
{

}

TransactionForm::~TransactionForm()
{

}

void TransactionForm::Initialize()
{
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

}