#include <counterparty.h>

Counterparty::Counterparty()
{
    m_id = 0;
    m_name = "";
    m_location = "";
    m_notes = "";
    m_parentId = 0;
}

Counterparty::~Counterparty()
{
}

void Counterparty::SetIntAttribute(std::string &name, int value)
{
    switch(name)
    {
    case "ID":
        m_id = value;
        break;
    case "PARENT_ID":
        m_parentId = value;
        break;
    }
}

int Counterparty::GetIntAttribute(std::string &name)
{
    switch(name)
    {
        case "ID":
            return m_id;
        case "PARENT_ID":
            return m_parentId;
        default:
            /* TODO: raise an error */
            return 0;
    }
}

void Counterparty::SetStringAttribute(std::string &name, std::string &value)
{
    switch(name)
    {
    case "NAME":
        m_name = value;
        break;
    case "LOCATION":
        m_location = value;
        break;
    case "NOTES":
        m_notes = value;
        break;
    }  
}

std::string Counterparty::GetStringAttribute(std::string &name)
{
    switch(name)
    {
    case "NAME":
        return m_name;
    case "LOCATION":
        return m_location;
    case "NOTES":
        return m_notes;
    default:
        return "";
    }     
}
