#ifndef TOTAL_CALCULATION_FORM_H
#define TOTAL_CALCULATION_FORM_H

#include <form.h>

#include <string_field.h>
#include <type_field.h>
#include <class_field.h>
#include <counterparty_field.h>
#include <int_field.h>
#include <account_field.h>
#include <double_field.h>
#include <date_field.h>

class TotalCalculationForm : public Form
{
public:
	TotalCalculationForm();
	~TotalCalculationForm();

	virtual void Initialize();
	virtual void Copy(Form *target);

	int GetType() const { return m_typeField.GetCurrentSuggestion()->Id; }
	int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }
	std::string GetDate() const { return m_dateField.GetCurrentValue(); }

protected:
	TypeField m_typeField;
	ClassField m_classField;
	DateField m_dateField;

};

#endif /* TOTAL_CALCULATION_FORM_H */
