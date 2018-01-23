#include <transaction_type.h>

TransactionType::TransactionType()
{
	m_id = 0;
	m_name = "";
}

TransactionType::~TransactionType()
{
}

void TransactionType::SetIntAttribute(std::string &name, int value)
{
	if (name == "ID")
		m_id = value;
}

int TransactionType::GetIntAttribute(std::string &name)
{
	if (name == "ID")
		return m_id;
}

void TransactionType::SetStringAttribute(std::string &name, std::string &value)
{
	if (name == "NAME")
		m_name = value;
}

std::string TransactionType::GetStringAttribute(std::string &name)
{
	if (name == "NAME")
		return m_name;
}
