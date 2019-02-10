#include <counterparty_field.h>
#include <database_layer.h>

pft::CounterpartyField::CounterpartyField() {
    m_hasValue = false;
}

pft::CounterpartyField::~CounterpartyField() {

}

bool pft::CounterpartyField::SetUserSearch(std::string &search) {
    FieldInput::SetUserSearch(search);

    m_database->GetAllCounterpartySuggestions(search.c_str(), this);

    return true;
}

void pft::CounterpartyField::UseSuggestion(int n) {
    m_hasValue = true;
    m_currentValue = *m_suggestions[n];
}
