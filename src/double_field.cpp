#include <double_field.h>

#include <sstream>

pft::DoubleField::DoubleField() {
    m_type = INPUT_DOUBLE;
    m_currentValue = 0.0;
}

pft::DoubleField::~DoubleField() {}

std::string pft::DoubleField::GetCurrentValue() const {
    if (!m_hasValue) return "";

    std::stringstream ss;
    ss << m_currentValue;
    return ss.str();
}

bool pft::DoubleField::SetUserSearch(const std::string &search) {

    std::stringstream ss;
    ss << search;

    double value;
    ss >> value;

    if (!ss.eof() || ss.fail()) {
        m_hasValue = false;
        return false;
    } else {
        m_currentValue = value;
        m_hasValue = true;
        return true;
    }
}
