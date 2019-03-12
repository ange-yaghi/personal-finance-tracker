#ifndef CLASS_FIELD_H
#define CLASS_FIELD_H

#include <field_input.h>

namespace pft {

    class ClassField : public FieldInput {
    public:
        ClassField();
        ~ClassField();

        virtual std::string GetCurrentValue() const { return m_currentValue.SuggestionString; };
        virtual bool SetUserSearch(const std::string &search);
        virtual void UseSuggestion(int n);

        Suggestion m_currentValue;

        void SetCurrentValue(Suggestion suggestion) { m_currentValue = suggestion; m_hasValue = true; }
        const Suggestion *GetCurrentSuggestion() const { return &m_currentValue; }
    };

} /* namespace pft */

#endif /* CLASS_FIELD_H */
