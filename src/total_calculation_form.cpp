#include <total_calculation_form.h>

namespace pft {

    TotalCalculationForm::TotalCalculationForm() {}
    TotalCalculationForm::~TotalCalculationForm() {}

    void TotalCalculationForm::Copy(Form *target) {
        // UNIMPLEMENTED
    }

    void TotalCalculationForm::Initialize() {
        Form::Initialize();

        m_classField.SetFieldName(std::string("CLASS"));
        m_classField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_typeField.SetFieldName(std::string("TYPE"));
        m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_dateField.SetFieldName(std::string("DATE"));
        m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);
        m_dateField.SetMonthOnly(true);

        /* Register all fields */
        RegisterField(&m_dateField);
        RegisterField(&m_typeField);
        RegisterField(&m_classField);
    }

} /* namespace pft */
