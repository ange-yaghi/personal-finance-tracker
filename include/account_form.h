#ifndef PFT_ACCOUNT_FORM_H
#define PFT_ACCOUNT_FORM_H

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
	class Account;

	// Implements a UI form for entering accounts
	class AccountForm : public Form {
	public:
		AccountForm();
		~AccountForm();

		virtual void Initialize();
		virtual void Copy(Form *target);

		// Populate all fields using an account as a reference
		void PopulateFields(const Account *account);

		// Populate a transaction using the data entered in the form fields
		void PopulateAccount(Account *target) const;

	protected:
		StringField m_nameField;
		AccountField m_parentField;
		StringField m_notesField;
		StringField m_locationField;
	};

} /* namespace pft */

#endif /* PFT_ACCOUNT_FORM_H */
