#include <account.h>

namespace pft {

    Account::Account() {
        m_id = 0;
        m_name = "";
        m_parentId = 0;
    }

    Account::~Account() {}

    void Account::RegisterAttributes() {
        /* Register all attributes (column mappings) */
        RegisterAttribute(std::string("ID"), DataAttribute::TYPE_INT, (void *)&m_id);
        RegisterAttribute(std::string("PARENT_ID"), DataAttribute::TYPE_INT, (void *)&m_parentId);
        RegisterAttribute(std::string("NAME"), DataAttribute::TYPE_STRING, (void *)&m_name);
    }

} /* namespace pft */
