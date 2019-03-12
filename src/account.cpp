#include <account.h>

pft::Account::Account() {
    m_id = 0;
    m_name = "";
    m_parentId = 0;
}

pft::Account::~Account() {}

void pft::Account::RegisterAttributes() {
    /* Register all attributes (column mappings) */
    RegisterAttribute(std::string("ID"), DataAttribute::TYPE_INT, (void *)&m_id);
	RegisterAttribute(std::string("NAME"), DataAttribute::TYPE_STRING, (void *)&m_name);
	RegisterAttribute(std::string("LOCATION"), DataAttribute::TYPE_STRING, (void *)&m_location);
	RegisterAttribute(std::string("NOTES"), DataAttribute::TYPE_STRING, (void *)&m_notes);
    RegisterAttribute(std::string("PARENT_ID"), DataAttribute::TYPE_INT, (void *)&m_parentId);
}
