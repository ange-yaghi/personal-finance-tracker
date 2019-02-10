#include <data_attribute.h>

pft::DataAttribute::DataAttribute() {

}

pft::DataAttribute::~DataAttribute() {

}

int pft::DataAttribute::GetAsInt() const {
    return *((int *)(m_binding));
}

float pft::DataAttribute::GetAsFloat() const {
    return *((float *)(m_binding));
}

const std::string *pft::DataAttribute::GetAsString() const {
    return ((const std::string *)(m_binding));
}
