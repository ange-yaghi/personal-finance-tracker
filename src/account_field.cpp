#include <account_field.h>
#include <database_layer.h>

pft::AccountField::AccountField() {
    m_hasValue = false;
}

pft::AccountField::~AccountField() {}

bool pft::AccountField::SetUserSearch(const std::string &search) {
    FieldInput::SetUserSearch(search);
    m_database->GetAllAccountSuggestions(search.c_str(), this);

    return true;
}

void pft::AccountField::UseSuggestion(int n) {
    m_hasValue = true;
    m_currentValue = *m_suggestions[n];
}
