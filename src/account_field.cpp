#include <account_field.h>
#include <database_layer.h>

namespace pft {

    AccountField::AccountField() {
        m_hasValue = false;
    }

    AccountField::~AccountField() {}

    bool AccountField::SetUserSearch(std::string &search) {
        FieldInput::SetUserSearch(search);

        m_database->GetAllAccountSuggestions(search.c_str(), this);

        return true;
    }

    void AccountField::UseSuggestion(int n) {
        m_hasValue = true;
        m_currentValue = *m_suggestions[n];
    }

} /* namespace pft */
