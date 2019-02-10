#include <class_field.h>
#include <database_layer.h>

pft::ClassField::ClassField() {
    m_hasValue = false;
}

pft::ClassField::~ClassField() {}

bool pft::ClassField::SetUserSearch(std::string &search) {
    FieldInput::SetUserSearch(search);

    m_database->GetAllClassSuggestions(search.c_str(), this);

    return true;
}

void pft::ClassField::UseSuggestion(int n) {
    m_hasValue = true;
    m_currentValue = *m_suggestions[n];
}
