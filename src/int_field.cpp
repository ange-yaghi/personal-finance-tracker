#include "int_field.h"
#include <database_layer.h>

#include <sstream>

namespace pft {

    IntField::IntField() {
        m_hasValue = false;
        m_currentValue = 0;
    }

    IntField::~IntField() {}

    std::string IntField::GetCurrentValue() const {
        std::stringstream ss;
        ss << m_currentValue;

        return ss.str();
    }

    bool IntField::SetUserSearch(std::string &search) {
        FieldInput::SetUserSearch(search);

        if (search == "") {
            m_hasValue = true;
            m_currentValue = 0;
            return true;
        }

        std::stringstream ss;
        ss << search;

        int value;
        ss >> value;

        if (!ss.eof() || ss.fail()) {
            m_hasValue = false;
            return false;
        } else {
            m_currentValue = value;
            m_hasValue = true;
            return true;
        }

        return true;
    }

} /* namespace pft */
