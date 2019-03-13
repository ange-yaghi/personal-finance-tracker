#include <transaction.h>

pft::Transaction::Transaction() {
    m_id = 0;
    m_name = "";
    m_typeId = 0;
    m_classId = 0;
    m_parentEntityId = 0;
    m_sourceAccountId = 0;
    m_amount = 0;
    m_date = "";
    m_targetAccountId = 0;
    m_notes = "";
}

pft::Transaction::~Transaction() {

}

void pft::Transaction::RegisterAttributes() {
    /* Register all database attributes */
    RegisterAttribute(std::string("ID"), DataAttribute::TYPE_INT, (void *)&m_id);
    RegisterAttribute(std::string("TYPE_ID"), DataAttribute::TYPE_INT, (void *)&m_typeId);
    RegisterAttribute(std::string("CLASS_ID"), DataAttribute::TYPE_INT, (void *)&m_classId);
    RegisterAttribute(std::string("PARENT_ENTITY_ID"), DataAttribute::TYPE_INT, (void *)&m_parentEntityId);
    RegisterAttribute(std::string("SOURCE_ACCOUNT_ID"), DataAttribute::TYPE_INT, (void *)&m_sourceAccountId);
    RegisterAttribute(std::string("TARGET_ACCOUNT_ID"), DataAttribute::TYPE_INT, (void *)&m_targetAccountId);
    RegisterAttribute(std::string("AMOUNT"), DataAttribute::TYPE_INT, (void *)&m_amount);
    RegisterAttribute(std::string("NAME"), DataAttribute::TYPE_STRING, (void *)&m_name);
    RegisterAttribute(std::string("DATE"), DataAttribute::TYPE_STRING, (void *)&m_date);
    RegisterAttribute(std::string("NOTES"), DataAttribute::TYPE_STRING, (void *)&m_notes);
}
