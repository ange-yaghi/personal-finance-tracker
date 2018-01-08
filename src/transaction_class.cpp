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
    switch (name)
    {
        case "ID":
            m_id = value;
            break;
        case "PARENT_ID":
            m_parentId = value;
            break;
    }
}

int TransactionClass::GetIntAttribute(std::string &name)
{
    switch (name)
    {
        case "ID":
            return m_id;
        case "PARENT_ID":
            return m_parentId;
        default:
            /* TODO */
            return 0;
    }
}

void TransactionClass::SetStringAttribute(std::string &name, std::string &value)
{
    switch (name)
    {
        case "NAME":
            m_name = value;
            break;
    }
}

std::string TransactionClass::GetStringAttribute(std::string &name)
{
    switch (name)
    {
        case "NAME":
            return m_name;
        default:
            /* TODO */
            return "";
    }   
}
