#ifndef PFT_CONFIRM_FIELD_H
#define PFT_CONFIRM_FIELD_H

#include "field_input.h"

namespace pft {

	class ConfirmField : public FieldInput
	{
	public:
		ConfirmField();
		~ConfirmField();

		virtual std::string GetCurrentValue() const { return m_currentString; };
		virtual bool SetUserSearch(std::string &search);

	protected:

		std::string m_currentString;
	};

} /* namespace pft */

#endif /* PFT_CONFIRM_FIELD */
