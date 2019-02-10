#include <breakdown_calculation_form.h>

pft::BreakdownCalculationForm::BreakdownCalculationForm() {

}

pft::BreakdownCalculationForm::~BreakdownCalculationForm() {

}

void pft::BreakdownCalculationForm::Copy(Form *target) {
    // UNIMPLEMENTED
}

void pft::BreakdownCalculationForm::Initialize() {
    Form::Initialize();

    m_outputFile.SetFieldName(std::string("OUTPUT FILE"));
    m_outputFile.SetInputType(FieldInput::INPUT_SHORT_STRING);

    m_classField.SetFieldName(std::string("CLASS"));
    m_classField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_dateField.SetFieldName(std::string("DATE"));
    m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);
    m_dateField.SetMonthOnly(true);

    m_mainTypeField.SetFieldName(std::string("REAL TYPE"));
    m_mainTypeField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_budgetTypeField.SetFieldName(std::string("BUDGET TYPE"));
    m_budgetTypeField.SetInputType(FieldInput::INPUT_LOOKUP);

    /* Register all fields */
    RegisterField(&m_outputFile);
    RegisterField(&m_dateField);
    RegisterField(&m_classField);
    RegisterField(&m_mainTypeField);
    RegisterField(&m_budgetTypeField);
}
