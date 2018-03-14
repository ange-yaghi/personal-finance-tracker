#ifndef CHECK_BALANCE_FORM_H
#define CHECK_BALANCE_FORM_H

#include <form.h>

#include <type_field.h>
#include <account_field.h>
#include <date_field.h>

namespace pft {

	// Implements a UI form for checking the balance of an account
	class CheckBalanceForm : public Form {
		public:
			CheckBalanceForm();
			~CheckBalanceForm();

			virtual void Initialize();
			virtual void Copy(Form *target);

			/* Getters for all field values */

			// Get the type
			int GetType() const { return m_typeField.GetCurrentSuggestion()->Id; }

			// Get the account
			int GetAccount() const { return m_accountField.GetCurrentSuggestion()->Id; }

			// Get the date
			std::string GetDate() const { return m_dateField.GetCurrentValue(); }

		protected:
			TypeField m_typeField;
			AccountField m_accountField;
			DateField m_dateField;
	};

} /* namespace pft */

#endif /* CHECK_BALANCE_FORM_H */