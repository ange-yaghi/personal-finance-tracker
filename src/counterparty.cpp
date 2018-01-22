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
    if (name == "ID")
        m_id = value;
    else if (name == "PARENT_ID")
        m_parentId = value;
}

int Counterparty::GetIntAttribute(std::string &name)
{
	if (name == "ID")
		return m_id;
	else if (name == "PARENT_ID")
		return m_parentId;
}

void Counterparty::SetStringAttribute(std::string &name, std::string &value)
{
    if (name == "NAME")
        m_name = value;
	else if (name == "LOCATION")
        m_location = value;
	else if (name == "NOTES")
        m_notes = value;
}

std::string Counterparty::GetStringAttribute(std::string &name)
{
	if (name == "NAME")
		return m_name;
	else if (name == "LOCATION")
		return m_location;
	else if (name == "NOTES")
		return m_notes;
}
