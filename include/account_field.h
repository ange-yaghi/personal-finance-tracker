#ifndef ACCOUNT_FIELD_H
#define ACCOUNT_FIELD_H

#include <field_input.h>

namespace pft {

	class AccountField : public FieldInput {
	public:
		AccountField();
		~AccountField();

		virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
		virtual bool SetUserSearch(const std::string &search);
		virtual void UseSuggestion(int n);

		void SetCurrentValue(Suggestion suggestion);
		const Suggestion *GetCurrentSuggestion() const { return &m_currentValue; }

		Suggestion m_currentValue;

		void SetAcceptNone(bool acceptNone) { m_acceptNone = acceptNone; }
		bool DoesAcceptNone() const { return m_acceptNone; }

	protected:
		bool m_acceptNone;
    };

} /* namespace pft */

#endif /* ACCOUNT_FIELD_H */
