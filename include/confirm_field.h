#include "field_input.h"

class ConfirmField : public FieldInput
{
public:
	ConfirmField();
	~ConfirmField();

	virtual std::string GetCurrentValue() const { return m_currentString; };
	virtual bool SetUserSearch(std::string &search);

protected:

	std::string m_currentString;

};
