#include <transaction_class.h>

TransactionClass::TransactionClass()
{
    m_id = 0;
    m_name = "";
    m_parentId = 0;
}

TransactionClass::~TransactionClass()
{
}

void TransactionClass::SetIntAttribute(std::string &name, int value)
{
    if (name == "ID")
		m_id = value;
	else if (name == "PARENT_ID")
        m_parentId = value;
}

int TransactionClass::GetIntAttribute(std::string &name)
{
    if (name == "ID")
        return m_id;
    else if (name == "PARENT_ID")
        return m_parentId;
	else
	{
		/* TODO */
		return 0;
	}
}

void TransactionClass::SetStringAttribute(std::string &name, std::string &value)
{
    if (name == "NAME")
        m_name = value;
}

std::string TransactionClass::GetStringAttribute(std::string &name)
{
    if (name == "NAME")
        return m_name;
	else
	{
        /* TODO */
        return "";
    }   
}
