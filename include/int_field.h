#ifndef PFT_INT_FIELD_H
#define PFT_INT_FIELD_H

#include "field_input.h"

namespace pft {

    class IntField : public FieldInput {
    public:
        IntField();
        ~IntField();

        virtual std::string GetCurrentValue() const;
        virtual bool SetUserSearch(const std::string &search);

        int m_currentValue;

        void SetCurrentValue(int value) { m_currentValue = value; m_hasValue = true; }
        int GetIntValue() const { return m_currentValue; }
    };

} /* namespace pft */

#endif /* PFT_INT_FIELD_H */
