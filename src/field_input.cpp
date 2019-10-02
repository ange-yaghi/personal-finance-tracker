#include "../include/field_input.h"

pft::FieldInput::FieldInput() {
    m_hasValue = false;
}

pft::FieldInput::~FieldInput() {
    /* void */
}

bool pft::FieldInput::SetUserSearch(const std::string &search) {
    return true;
}

void pft::FieldInput::OnFieldFinished() {
    /* void */
}

void pft::FieldInput::UseSuggestion(int n) {
    /* void */
}

std::string pft::FieldInput::GetSuggestion(int n) const {
    return m_suggestions[n]->SuggestionString;
}

int pft::FieldInput::GetSuggestionCount() const {
    return m_suggestions.size();
}

void pft::FieldInput::ClearSuggestions() {
    int size = m_suggestions.size();

    for (int i = 0; i < size; i++) {
        delete m_suggestions[i];
    }

    m_suggestions.clear();
}

void pft::FieldInput::AddSuggestion(int ID, std::string name) {
    Suggestion *newSuggestion = new Suggestion;
    newSuggestion->Id = ID;
    newSuggestion->SuggestionString = name;
    m_suggestions.push_back(newSuggestion);
}
