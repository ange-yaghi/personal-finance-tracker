#ifndef INT_FIELD_H
#define INT_FIELD_H

#include <field_input.h>

class IntField : public FieldInput
{
public:
	IntField();
	~IntField();

	virtual std::string GetCurrentValue() const;
	virtual bool SetUserSearch(std::string &search);

	int m_currentValue;

	void SetCurrentValue(int value) { m_currentValue = value; m_hasValue = true; }
	int GetIntValue() const { return m_currentValue; }
};

#endif /* INT_FIELD_H */