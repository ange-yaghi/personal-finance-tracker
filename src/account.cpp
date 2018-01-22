#include <account.h>

Account::Account()
{
    m_id = 0;
    m_name = "";
    m_parentId = 0;
}

Account::~Account()
{
}

void Account::SetIntAttribute(std::string &name, int value)
{
    if (name == "ID")
        m_id = value;
	else if (name == "PARENT_ID")
        m_parentId = value;
}

int Account::GetIntAttribute(std::string &name)
{
	if (name == "ID")
		return m_id;
	else if (name == "PARENT_ID")
		return m_parentId;
}

void Account::SetStringAttribute(std::string &name, std::string &value)
{
	if (name == "NAME")
		m_name = value;
}

std::string Account::GetStringAttribute(std::string &name)
{
	if (name == "NAME")
		return m_name;
}
