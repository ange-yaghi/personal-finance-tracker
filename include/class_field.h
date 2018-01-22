#ifndef CLASS_FIELD_H
#define CLASS_FIELD_H

#include <field_input.h>

class ClassField : public FieldInput
{
public:
	ClassField();
	~ClassField();

	virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
	virtual bool SetUserSearch(std::string &search);
	virtual void UseSuggestion(int n);

	Suggestion m_currentValue;

};

#endif /* CLASS_FIELD_H */
