#ifndef TOTAL_CALCULATION_FORM_H
#define TOTAL_CALCULATION_FORM_H

#include <form.h>

#include <type_field.h>
#include <class_field.h>
#include <date_field.h>

namespace pft {

    // Implements at UI form for calculating the total transactions over a specific
    // transaction class.
    class TotalCalculationForm : public Form {
    public:
        TotalCalculationForm();
        ~TotalCalculationForm();

        virtual void Initialize();
        virtual void Copy(Form *target);

        /* Getters for field data */

        // Get the type entered
        int GetType() const { return m_typeField.GetCurrentSuggestion()->Id; }

        // Get the transaction class entered
        int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }

        // Get the date entered
        std::string GetDate() const { return m_dateField.GetCurrentValue(); }

    protected:
        TypeField m_typeField;
        ClassField m_classField;
        DateField m_dateField;
    };

} /* namespace pft */

#endif /* TOTAL_CALCULATION_FORM_H */
