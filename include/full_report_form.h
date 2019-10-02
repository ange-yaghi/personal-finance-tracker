#ifndef PFT_FULL_REPORT_FORM_H
#define PFT_FULL_REPORT_FORM_H

#include "form.h"

#include "string_field.h"
#include "type_field.h"
#include "class_field.h"
#include "date_field.h"

namespace pft {

    // Implements a UI form for generating full reports over a user-specified
    // span of months
    class FullReportForm : public Form {
    public:
        FullReportForm();
        ~FullReportForm();

        virtual void Initialize();
        virtual void Copy(Form *target);

        /* Getters for all fields */

        // Get the output file path
        std::string GetOutputFile() const { return m_folderName.GetCurrentValue() + m_fileName.GetCurrentValue(); }

        // Get the selected class
        int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }

        // Get the selected type
        int GetType() const { return m_typeField.GetCurrentSuggestion()->Id; }

        // Get the selected budget type
        int GetBudgetType() const { return m_budgetTypeField.GetCurrentSuggestion()->Id; }

        // Get the start month
        std::string GetStartMonth() const { return m_startMonth.GetCurrentValue(); }

        // Get the end month
        std::string GetEndMonth() const { return m_endMonth.GetCurrentValue(); }

    protected:
        StringField m_folderName;
        StringField m_fileName;
        ClassField m_classField;
        TypeField m_typeField;
        TypeField m_budgetTypeField;
        DateField m_startMonth;
        DateField m_endMonth;
    };

} /* namespace pft */

#endif /* PFT_FULL_REPORT_FORM_H */
