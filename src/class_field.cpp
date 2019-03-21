#include <class_field.h>
#include <database_layer.h>

pft::ClassField::ClassField() {
    m_hasValue = false;

	m_acceptNone = false;
}

pft::ClassField::~ClassField() {

}

bool pft::ClassField::SetUserSearch(const std::string &search) {
    FieldInput::SetUserSearch(search);

	if (m_acceptNone && (search == "NA" || search == "NONE")) {
		m_hasValue = true;

		m_currentValue.SuggestionString = "NONE";
		m_currentValue.Id = -1;
	}
	else {
		m_database->GetAllClassSuggestions(search.c_str(), this);
	}

    return true;
}

void pft::ClassField::UseSuggestion(int n) {
    m_hasValue = true;
    m_currentValue = *m_suggestions[n];
}

void pft::ClassField::SetCurrentValue(Suggestion suggestion) {
	m_currentValue = suggestion;
	m_hasValue = true;

	if (m_currentValue.Id == -1) {
		m_currentValue.SuggestionString = "NONE";
	}
}
