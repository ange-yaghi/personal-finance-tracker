#include <class_field.h>
#include <database_layer.h>

namespace pft {

    ClassField::ClassField() {
        m_hasValue = false;
    }

    ClassField::~ClassField() {}

    bool ClassField::SetUserSearch(std::string &search) {
        FieldInput::SetUserSearch(search);

        m_database->GetAllClassSuggestions(search.c_str(), this);

        return true;
    }

    void ClassField::UseSuggestion(int n) {
        m_hasValue = true;
        m_currentValue = *m_suggestions[n];
    }

} /* namespace pft */
