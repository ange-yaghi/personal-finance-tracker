#include <confirm_field.h>

ConfirmField::ConfirmField()
{
	m_currentString = "";
	m_hasValue = false;
}

ConfirmField::~ConfirmField()
{

}

bool ConfirmField::SetUserSearch(std::string &search)
{
	FieldInput::SetUserSearch(search);
	m_currentString = search;
	m_hasValue = true;

	return true;
}