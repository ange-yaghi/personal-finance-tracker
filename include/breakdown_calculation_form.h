#ifndef BREAKDOWN_CALCULATION_FORM_H
#define BREAKDOWN_CALCULATION_FORM_H

#include <form.h>

#include <string_field.h>
#include <type_field.h>
#include <class_field.h>
#include <counterparty_field.h>
#include <int_field.h>
#include <account_field.h>
#include <double_field.h>
#include <date_field.h>

class BreakdownCalculationForm : public Form
{
public:
	BreakdownCalculationForm();
	~BreakdownCalculationForm();

	virtual void Initialize();
	virtual void Copy(Form *target);

	std::string GetOutputFile() const { return m_outputFile.GetCurrentValue(); }
	int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }
	std::string GetDate() const { return m_dateField.GetCurrentValue(); }
	int GetMainType() const { return m_mainTypeField.GetCurrentSuggestion()->Id; }
	int GetBudgetType() const { return m_budgetTypeField.GetCurrentSuggestion()->Id; }

protected:
	StringField m_outputFile;
	ClassField m_classField;
	TypeField m_mainTypeField;
	TypeField m_budgetTypeField;
	DateField m_dateField;
};

#endif /* BREAKDOWN_CALCULATION_FORM_H */
