#include <class_form.h>

#include <transaction.h>
#include <transaction_class.h>
#include <account.h>
#include <transaction_type.h>

#include <database_layer.h>

pft::ClassForm::ClassForm() {

}

pft::ClassForm::~ClassForm() {

}

void pft::ClassForm::Initialize() {
	Form::Initialize();

	m_nameField.SetFieldName(std::string("NAME"));
	m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_parentField.SetFieldName(std::string("PARENT"));
	m_parentField.SetInputType(FieldInput::INPUT_LOOKUP);
	m_parentField.SetAcceptNone(true);

	m_descriptionField.SetFieldName("DESCRIPTION");
	m_descriptionField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	/* Register all fields */
	RegisterField(&m_nameField);
	RegisterField(&m_parentField);
	RegisterField(&m_descriptionField);
}

void pft::ClassForm::Copy(Form *target) {
	// UNIMPLEMENTED
}

void pft::ClassForm::PopulateFields(const TransactionClass *tClass) {
	TransactionClass parentClass;
	parentClass.Initialize();

	// Fetch related objects from the database
	m_databaseLayer->GetClass(tClass->GetIntAttribute("PARENT_ID"), &parentClass);

	// Populate fields
	m_nameField.SetCurrentValue(tClass->GetStringAttribute("NAME"));
	m_parentField.SetCurrentValue(
		FieldInput::Suggestion(parentClass.GetStringAttribute("NAME"), 
			parentClass.GetIntAttribute("ID")));
	m_descriptionField.SetCurrentValue(tClass->GetStringAttribute("DESCRIPTION"));
}

void pft::ClassForm::PopulateClass(TransactionClass *target) const {
	target->SetStringAttribute("NAME", m_nameField.GetCurrentValue());
	target->SetIntAttribute("PARENT_ID", m_parentField.GetCurrentSuggestion()->Id);
	target->SetStringAttribute("DESCRIPTION", m_descriptionField.GetCurrentValue());
}
