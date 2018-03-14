#include "type_field.h"
#include <database_layer.h>

namespace pft {

    TypeField::TypeField() {
        m_hasValue = false;
    }

    TypeField::~TypeField() {}

    bool TypeField::SetUserSearch(std::string &search) {
        FieldInput::SetUserSearch(search);
        m_database->GetAllTypeSuggestions(search.c_str(), this);

        return true;
    }

    void TypeField::UseSuggestion(int n) {
        m_hasValue = true;
        m_currentValue = *m_suggestions[n];
    }

} /* namespace pft */
