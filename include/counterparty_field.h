#ifndef COUNTERPARTY_FIELD_H
#define COUNTERPARTY_FIELD_H

#include <field_input.h>

class CounterpartyField : public FieldInput
{
public:
	CounterpartyField();
	~CounterpartyField();

	virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
	virtual bool SetUserSearch(std::string &search);
	virtual void UseSuggestion(int n);

	Suggestion m_currentValue;

};

#endif /* COUNTERPARTY_FIELD_H */