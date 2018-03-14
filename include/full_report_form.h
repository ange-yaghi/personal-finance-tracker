#ifndef FULL_REPORT_FORM_H
#define FULL_REPORT_FORM_H

#include <form.h>

#include <string_field.h>
#include <type_field.h>
#include <class_field.h>
#include <counterparty_field.h>
#include <int_field.h>
#include <account_field.h>
#include <double_field.h>
#include <date_field.h>

class Transaction;
class FullReportForm : public Form
{
public:
	FullReportForm();
	~FullReportForm();

	virtual void Initialize();
	virtual void Copy(Form *target);

	std::string GetOutputFile() const { return m_folderName.GetCurrentValue() + m_fileName.GetCurrentValue(); }
	int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }
	int GetType() const { return m_typeField.GetCurrentSuggestion()->Id; }
	int GetBudgetType() const { return m_budgetTypeField.GetCurrentSuggestion()->Id; }
	std::string GetStartMonth() const { return m_startMonth.GetCurrentValue(); }
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

#endif /* FULL_REPORT_FORM_H */
