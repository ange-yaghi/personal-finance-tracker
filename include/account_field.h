#ifndef ACCOUNT_FIELD_H
#define ACCOUNT_FIELD_H

#include <field_input.h>

class AccountField : public FieldInput
{
public:
	AccountField();
	~AccountField();

	virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
	virtual bool SetUserSearch(std::string &search);
	virtual void UseSuggestion(int n);

	Suggestion m_currentValue;

};

#endif /* ACCOUNT_FIELD_H */
