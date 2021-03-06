#ifndef PFT_DATE_FIELD_H
#define PFT_DATE_FIELD_H

#include "field_input.h"

namespace pft {

    class DateField : public FieldInput {
    public:
        DateField();
        ~DateField();

        virtual std::string GetCurrentValue() const { return m_currentString; };
        virtual bool SetUserSearch(const std::string &search);

        void SetCurrentValue(std::string value) { m_currentString = value; m_hasValue = true; }

        void SetMonthOnly(bool monthOnly) { m_monthOnly = monthOnly; }

    protected:
        void SetDateToday();

        std::string m_currentString;
        bool m_monthOnly;
    };

} /* namespace pft */

#endif /* PFT_DATE_FIELD_H */