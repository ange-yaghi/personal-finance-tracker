#ifndef COPY_ALL_OF_TYPE_FORM_H
#define COPY_ALL_OF_TYPE_FORM_H

#include <form.h>

#include <string_field.h>
#include <type_field.h>
#include <class_field.h>
#include <counterparty_field.h>
#include <int_field.h>
#include <account_field.h>
#include <double_field.h>
#include <date_field.h>

class CopyAllOfTypeForm : public Form
{
public:
	CopyAllOfTypeForm();
	~CopyAllOfTypeForm();

	virtual void Initialize();
	virtual void Copy(Form *target);

	int GetClass() const { return m_classField.GetCurrentSuggestion()->Id; }
	int GetType() const {  }
	std::string GetSourceDate() const { return m_sourceDateField.GetCurrentValue(); }
	std::string GetDestinationDate() const { return m_destinationDateField.GetCurrentValue(); }

protected:
	ClassField m_classField;
	TypeField m_typeField;
	DateField m_sourceDateField;
	DateField m_destinationDateField;
};

#endif /* COPY_ALL_OF_TYPE_FORM_H */