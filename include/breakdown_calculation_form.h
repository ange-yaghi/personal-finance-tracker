#ifndef BREAKDOWN_CALCULATION_FORM_H
#define BREAKDOWN_CALCULATION_FORM_H

#include <form.h>

#include <string_field.h>
#include <type_field.h>
#include <class_field.h>
#include <date_field.h>

namespace pft {

    // Implements a UI form for a "breakdown" calculation
    class BreakdownCalculationForm : public Form {
    public:
        BreakdownCalculationForm();
        ~BreakdownCalculationForm();

        virtual void Initialize();
        virtual void Copy(Form *target);

        /* Getters and setters for the field values */

        // Get the output file path
        std::string GetOutputFile() const { return m_outputFile.GetCurrentValue(); }

        // Get the class to calculate the breakdown for
        int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }

        // Get the date (month) to calculate the breakdown for
        std::string GetDate() const { return m_dateField.GetCurrentValue(); }

        // Get the primary type (usually real transfers)
        int GetMainType() const { return m_mainTypeField.GetCurrentSuggestion()->Id; }

        // Get the type that stores the budget value
        int GetBudgetType() const { return m_budgetTypeField.GetCurrentSuggestion()->Id; }

    protected:
        StringField m_outputFile;
        ClassField m_classField;
        TypeField m_mainTypeField;
        TypeField m_budgetTypeField;
        DateField m_dateField;
    };

} /* namespace pft */

#endif /* BREAKDOWN_CALCULATION_FORM_H */
