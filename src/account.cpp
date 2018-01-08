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

int Account::GetIntAttribute(std::string &name)
{
    switch(name)
    {
    case "ID":
        return m_name;
    case "PARENT_ID":
        return m_parentId;
    }
}

void Account::SetStringAttribute(std::string &name, std::string &value)
{
    switch(name)
    {
    case "NAME":
        m_name = value;
        break;
    }
}

std::string Account::GetStringAttribute(std::string &name)
{
    switch(name)
    {
    case "NAME":
        return m_name;
    }
}