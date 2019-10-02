#include "../include/string_field.h"

pft::StringField::StringField() {
    m_currentString = "";
    m_hasValue = false;
}

pft::StringField::~StringField() {
    /* void */
}

bool pft::StringField::SetUserSearch(const std::string &search) {
    FieldInput::SetUserSearch(search);
    m_currentString = search;
    m_hasValue = true;

    return true;
}
