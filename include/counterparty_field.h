#ifndef COUNTERPARTY_FIELD_H
#define COUNTERPARTY_FIELD_H

#include <field_input.h>

namespace pft {

	class CounterpartyField : public FieldInput {
	public:
		CounterpartyField();
		~CounterpartyField();

		virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
		virtual bool SetUserSearch(std::string &search);
		virtual void UseSuggestion(int n);

		Suggestion m_currentValue;

		void SetCurrentValue(Suggestion suggestion) { m_currentValue = suggestion; m_hasValue = true; }
		const Suggestion *GetCurrentSuggestion() const { return &m_currentValue; }
	};

} /* namespace pft */

#endif /* COUNTERPARTY_FIELD_H */