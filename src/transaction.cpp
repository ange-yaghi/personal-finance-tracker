#include <transaction.h>

Transaction::Transaction()
{
    m_id = 0;
    m_name = "";
    m_typeId = 0;
    m_classId = 0;
    m_parentEntityId = 0;
    m_accountId = 0;
    m_amount = 0;
    m_date = "";
    m_counterpartyId = 0;
    m_notes = "";
}

Transaction::~Transaction()
{
}

void Transaction::SetIntAttribute(std::string &name, int value)
{
    if (name == "ID")
		m_id = value;
	else if (name == "TYPE_ID")
		m_typeId = value;
	else if (name == "CLASS_ID")
		m_classId = value;
	else if (name == "PARENT_ENTITY_ID")
        m_parentEntityId = value;
	else if (name == "ACCOUNT_ID")
        m_accountId = value;
	else if (name == "AMOUNT")
        m_amount = value;
	else if (name == "COUNTERPARTY_ID")
        m_counterpartyId = value;
}

int Transaction::GetIntAttribute(std::string &name)
{
	if (name == "ID")
		return m_id;
	else if (name == "TYPE_ID")
		return m_typeId;
	else if (name == "CLASS_ID")
		return m_classId;
	else if (name == "PARENT_ENTITY_ID")
		return m_parentEntityId;
	else if (name == "ACCOUNT_ID")
		return m_accountId;
	else if (name == "AMOUNT")
		return m_amount;
	else if (name == "COUNTERPARTY_ID")
		return m_counterpartyId;
	return 0;
}

void Transaction::SetStringAttribute(std::string &name, std::string &value)
{
    if (name == "NAME")
        m_name = value;
	else if (name == "DATE")
		m_date = value;
	else if (name == "NOTES")
        m_notes = value;
}

std::string Transaction::GetStringAttribute(std::string &name)
{
	if (name == "NAME")
		return m_name;
	else if (name == "DATE")
		return m_date;
	else if (name == "NOTES")
		return m_notes;
	return "";
}
