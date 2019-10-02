#include "../include/type_form.h"

#include "../include/transaction.h"
#include "../include/transaction_class.h"
#include "../include/account.h"
#include "../include/transaction_type.h"
#include "../include/database_layer.h"

pft::TypeForm::TypeForm() {
    /* void */
}

pft::TypeForm::~TypeForm() {
    /* void */
}

void pft::TypeForm::Initialize() {
	Form::Initialize();

	m_nameField.SetFieldName(std::string("NAME"));
	m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_descriptionField.SetFieldName(std::string("DESCRIPTION"));
	m_descriptionField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	/* Register all fields */
	RegisterField(&m_nameField);
	RegisterField(&m_descriptionField);
}

void pft::TypeForm::Copy(Form *target) {
	// UNIMPLEMENTED
}

void pft::TypeForm::PopulateFields(const TransactionType *type) {
	// Populate fields
	m_nameField.SetCurrentValue(type->GetStringAttribute("NAME"));
	m_descriptionField.SetCurrentValue(type->GetStringAttribute("DESCRIPTION"));
}

void pft::TypeForm::PopulateType(TransactionType *target) const {
	target->SetStringAttribute("NAME", m_nameField.GetCurrentValue());
	target->SetStringAttribute("DESCRIPTION", m_descriptionField.GetCurrentValue());
}
