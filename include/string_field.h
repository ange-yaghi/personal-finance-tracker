#include "field_input.h"

class StringField : public FieldInput
{
public:
	StringField();
	~StringField();

	virtual std::string GetCurrentValue() const { return m_currentString; };
	virtual bool SetUserSearch(std::string &search);

	void SetCurrentValue(std::string &value) { m_currentString = value; m_hasValue = true; }

protected:

	std::string m_currentString;

};
