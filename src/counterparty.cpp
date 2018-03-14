#include <counterparty.h>

namespace pft {

    Counterparty::Counterparty() {
        m_id = 0;
        m_name = "";
        m_location = "";
        m_notes = "";
        m_parentId = 0;
    }

    Counterparty::~Counterparty() {}

    void Counterparty::RegisterAttributes() {
        /* Register all attributes */
        RegisterAttribute(std::string("ID"), DataAttribute::TYPE_INT, (void *)&m_id);
        RegisterAttribute(std::string("PARENT_ID"), DataAttribute::TYPE_INT, (void *)&m_parentId);
        RegisterAttribute(std::string("NAME"), DataAttribute::TYPE_STRING, (void *)&m_name);
        RegisterAttribute(std::string("LOCATION"), DataAttribute::TYPE_STRING, (void *)&m_location);
        RegisterAttribute(std::string("NOTES"), DataAttribute::TYPE_STRING, (void *)&m_notes);
    }

} /* namespace pft */
