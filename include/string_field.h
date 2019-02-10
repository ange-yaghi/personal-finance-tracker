#ifndef STRING_FIELD_H
#define STRING_FIELD_H

#include "field_input.h"

namespace pft {

    class StringField : public FieldInput {
    public:
        StringField();
        ~StringField();

        virtual std::string GetCurrentValue() const { return m_currentString; };
        virtual bool SetUserSearch(const std::string &search);

        void SetCurrentValue(const std::string &value) { m_currentString = value; m_hasValue = true; }

    protected:
        std::string m_currentString;
    };

} /* namespace pft */

#endif /* STRING_FIELD_H */
