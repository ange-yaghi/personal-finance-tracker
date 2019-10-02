#include "../include/total_calculation_form.h"

pft::TotalCalculationForm::TotalCalculationForm() {
    /* void */
}

pft::TotalCalculationForm::~TotalCalculationForm() {
    /* void */
}

void pft::TotalCalculationForm::Copy(Form *target) {
    // UNIMPLEMENTED
}

void pft::TotalCalculationForm::Initialize() {
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
