#ifndef PFT_TYPE_FIELD_H
#define PFT_TYPE_FIELD_H

#include "field_input.h"

namespace pft {

    class TypeField : public FieldInput {
    public:
        TypeField();
        ~TypeField();

        virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
        virtual bool SetUserSearch(const std::string &search);
        virtual void UseSuggestion(int n);

        Suggestion m_currentValue;

		void SetCurrentValue(Suggestion suggestion);
        const Suggestion *GetCurrentSuggestion() const { return &m_currentValue; }

		void SetAcceptNone(bool acceptNone) { m_acceptNone = acceptNone; }
		bool DoesAcceptNone() const { return m_acceptNone; }

	protected:
		bool m_acceptNone;
    };

} /* namespace pft */

#endif /* PFT_TYPE_FIELD_H */
