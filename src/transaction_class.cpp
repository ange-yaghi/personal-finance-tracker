#include <transaction_class.h>

pft::TransactionClass::TransactionClass() {
    m_id = 0;
    m_name = "";
    m_parentId = 0;
}

pft::TransactionClass::~TransactionClass() {
    int nChildren = 0;
    for (int i = 0; i < nChildren; i++) {
        delete m_children[i];
    }
}

void pft::TransactionClass::RegisterAttributes() {
    /* Register all column mappings */
    RegisterAttribute(std::string("ID"), DataAttribute::TYPE_INT, (void *)&m_id);
    RegisterAttribute(std::string("NAME"), DataAttribute::TYPE_STRING, (void *)&m_name);
    RegisterAttribute(std::string("PARENT_ID"), DataAttribute::TYPE_INT, (void *)&m_parentId);
}

pft::TransactionClass *pft::TransactionClass::NewChild() {
    TransactionClass *newChild = new TransactionClass();
    newChild->RegisterAttributes();
    m_children.push_back(newChild);
    return newChild;
}
