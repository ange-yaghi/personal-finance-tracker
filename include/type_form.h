#ifndef PFT_TYPE_FORM_H
#define PFT_TYPE_FORM_H

#include "form.h"

#include "string_field.h"
#include "type_field.h"
#include "class_field.h"
#include "int_field.h"
#include "account_field.h"
#include "double_field.h"
#include "date_field.h"

namespace pft {

	/* Forward declarations */
	class TransactionType;

	// Implements a UI form for entering accounts
	class TypeForm : public Form {
	public:
		TypeForm();
		~TypeForm();

		virtual void Initialize();
		virtual void Copy(Form *target);

		// Populate all fields using an account as a reference
		void PopulateFields(const TransactionType *type);

		// Populate a transaction using the data entered in the form fields
		void PopulateType(TransactionType *target) const;

	protected:
		StringField m_nameField;
		StringField m_descriptionField;
	};

} /* namespace pft */

#endif /* PFT_TYPE_FORM_H */