#include <transaction.h>

Transaction::Transaction()
{
    m_id = 0;
    m_name = "";
    m_type = "";
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
    switch(name)
    {
        case "ID":
            m_id = value;
            break;
        case "CLASS_ID":
            m_classId = value;
            break;
        case "PARENT_ENTITY_ID":
            m_parentEntityId = value;
            break;
        case "ACCOUNT_ID":
            m_accountId = value;
            break;
        case "AMOUNT":
            m_amount = value;
            break;
        case "COUNTERPARTY_ID":
            m_counterpartyId = value;
            break;
    }
}

int Transaction::GetIntAttribute(std::string &name)
{
    switch(name)
    {
        case "ID":
            return m_id;
        case "CLASS_ID":
            return m_classId;
        case "PARENT_ENTITY_ID":
            return m_parentEntityId;
        case "ACCOUNT_ID":
            return m_accountId;
        case "AMOUNT":
            return m_amount;
        case "COUNTERPARTY_ID":
            return m_counterpartyId;
        default:
            /* TODO: Do something when there is an error */
            return 0;
    }
}

void Transaction::SetStringAttribute(std::string &name, std::string &value)
{
    switch(name)
    {
        case "NAME":
            m_name = value;
            break;
        case "TYPE":
            m_type = value;
            break;
        case "DATE":
            m_date = value;
            break;
        case "NOTES":
            m_notes = value;
            break;
    }
}

std::string Transaction::GetStringAttribute(std::string &name)
{
    switch(name)
    {
        case "NAME":
            return m_name;
        case "TYPE":
            return m_type;
        case "DATE":
            return m_date;
        case "NOTES":
            return m_notes;
        default:
            /* TODO */
            return "";
    }
}
