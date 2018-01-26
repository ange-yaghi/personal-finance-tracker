#ifndef CHECK_BALANCE_FORM_H
#define CHECK_BALANCE_FORM_H

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
class CheckBalanceForm : public Form
{
public:
	CheckBalanceForm();
	~CheckBalanceForm();

	virtual void Initialize();
	virtual void Copy(Form *target);

	int GetType() const { return m_typeField.GetCurrentSuggestion()->Id; }
	int GetAccount() const { return m_accountField.GetCurrentSuggestion()->Id; }
	std::string GetDate() const { return m_dateField.GetCurrentValue(); }

protected:

	TypeField m_typeField;
	AccountField m_accountField;
	DateField m_dateField;
};

#endif /* CHECK_BALANCE_FORM_H */