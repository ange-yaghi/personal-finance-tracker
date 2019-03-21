#include <account_form.h>

#include <transaction.h>
#include <transaction_class.h>
#include <account.h>
#include <transaction_type.h>

#include <database_layer.h>

pft::AccountForm::AccountForm() {

}

pft::AccountForm::~AccountForm() {

}

void pft::AccountForm::Initialize() {
	Form::Initialize();

	m_nameField.SetFieldName(std::string("NAME"));
	m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_parentField.SetFieldName(std::string("PARENT"));
	m_parentField.SetInputType(FieldInput::INPUT_LOOKUP);
	m_parentField.SetAcceptNone(true);

	m_locationField.SetFieldName("LOCATION");
	m_locationField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	m_notesField.SetFieldName("NOTES");
	m_notesField.SetInputType(FieldInput::INPUT_SHORT_STRING);

	/* Register all fields */
	RegisterField(&m_nameField);
	RegisterField(&m_parentField);
	RegisterField(&m_locationField);
	RegisterField(&m_notesField);
}

void pft::AccountForm::Copy(Form *target) {
	// UNIMPLEMENTED
}

void pft::AccountForm::PopulateFields(const Account *account) {
	Account parentAccount;
	parentAccount.Initialize();

	// Fetch related objects from the database
	m_databaseLayer->GetAccount(account->GetIntAttribute("PARENT_ID"), &parentAccount);

	// Populate fields
	m_nameField.SetCurrentValue(account->GetStringAttribute("NAME"));
	m_locationField.SetCurrentValue(account->GetStringAttribute("LOCATION"));
	m_parentField.SetCurrentValue(FieldInput::Suggestion(parentAccount.GetStringAttribute(std::string("NAME")), parentAccount.GetIntAttribute(std::string("ID"))));
	m_notesField.SetCurrentValue(account->GetStringAttribute("NOTES"));
}

void pft::AccountForm::PopulateAccount(Account *target) const {
	target->SetStringAttribute("NAME", m_nameField.GetCurrentValue());
	target->SetIntAttribute("PARENT_ID", m_parentField.GetCurrentSuggestion()->Id);
	target->SetStringAttribute("LOCATION", m_locationField.GetCurrentValue());
	target->SetStringAttribute("NOTES", m_notesField.GetCurrentValue());
}
