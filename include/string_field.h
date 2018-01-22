#include "field_input.h"

class StringField : public FieldInput
{
public:
	StringField();
	~StringField();

	virtual std::string GetCurrentValue() const { return m_currentString; };
	virtual bool SetUserSearch(std::string &search);

protected:

	std::string m_currentString;

};
