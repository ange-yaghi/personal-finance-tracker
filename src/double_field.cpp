#include <double_field.h>

#include <sstream>

namespace pft {

    DoubleField::DoubleField() {
        m_type = INPUT_DOUBLE;
        m_currentValue = 0.0;
    }

    DoubleField::~DoubleField() {}

    std::string DoubleField::GetCurrentValue() const {
        if (!m_hasValue) return "";

        std::stringstream ss;
        ss << m_currentValue;
        return ss.str();
    }

    bool DoubleField::SetUserSearch(std::string &search) {

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

} /* namespace pft */
