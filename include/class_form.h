#ifndef PFT_CLASS_FORM_H
#define PFT_CLASS_FORM_H

#include "form.h"

#include "string_field.h"
#include "class_field.h"

namespace pft {

	/* Forward declarations */
	class TransactionClass;

	// Implements a UI form for entering accounts
	class ClassForm : public Form {
	public:
		ClassForm();
		~ClassForm();

		virtual void Initialize();
		virtual void Copy(Form *target);

		// Populate all fields using a class as a reference
		void PopulateFields(const TransactionClass *tClass);

		// Populate a class using the data entered in the form fields
		void PopulateClass(TransactionClass *target) const;

	protected:
		StringField m_nameField;
		ClassField m_parentField;
		StringField m_descriptionField;
	};

} /* namespace pft */

#endif /* PFT_CLASS_FORM_H */
