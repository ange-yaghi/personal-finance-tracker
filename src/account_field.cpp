#include "../include/account_field.h"

#include "../include/database_layer.h"

pft::AccountField::AccountField() {
    m_hasValue = false;
	m_acceptNone = false;
}

pft::AccountField::~AccountField() {
    /* void */
}

bool pft::AccountField::SetUserSearch(const std::string &search) {
    FieldInput::SetUserSearch(search);

	if (m_acceptNone && (search == "NA" || search == "NONE")) {
		m_hasValue = true;

		m_currentValue.SuggestionString = "NONE";
		m_currentValue.Id = -1;
	}
	else {
		m_database->GetAllAccountSuggestions(search.c_str(), this);
	}

    return true;
}

void pft::AccountField::UseSuggestion(int n) {
    m_hasValue = true;
    m_currentValue = *m_suggestions[n];
}

void pft::AccountField::SetCurrentValue(Suggestion suggestion) {
	m_currentValue = suggestion;
	m_hasValue = true;

	if (m_currentValue.Id == -1) {
		m_currentValue.SuggestionString = "NONE";
	}
}
