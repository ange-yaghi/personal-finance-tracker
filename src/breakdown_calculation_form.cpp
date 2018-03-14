#include <breakdown_calculation_form.h>

BreakdownCalculationForm::BreakdownCalculationForm()
{

}

BreakdownCalculationForm::~BreakdownCalculationForm()
{

}

void BreakdownCalculationForm::Copy(Form *target)
{

}

void BreakdownCalculationForm::Initialize()
{
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

	RegisterField(&m_outputFile);
	RegisterField(&m_dateField);
	RegisterField(&m_classField);
	RegisterField(&m_mainTypeField);
	RegisterField(&m_budgetTypeField);
}