#ifndef FIELD_INPUT_H
#define FIELD_INPUT_H

#include <string>
#include <vector>

namespace pft {

    /* Forward Declarations */
    class DatabaseLayer;


    class FieldInput {
    public:

        struct Suggestion {
            Suggestion(std::string suggestionString, int id) { SuggestionString = suggestionString; Id = id; }
            Suggestion() {}
            ~Suggestion() {}

            std::string SuggestionString;
            int Id;
        };

        enum ACTIONS {
            CONTINUE,
            PRESENT_SUGGESTION,
            WAIT_FOR_USER_INPUT,
        };

        enum INPUT_TYPE {
            INPUT_DOUBLE,
            INPUT_SHORT_STRING,
            INPUT_LONG_STRING,
            INPUT_LOOKUP,
            INPUT_INT,
            INPUT_CONFIRM
        };

    public:
        FieldInput();
        ~FieldInput();

        virtual bool SetUserSearch(std::string &search);
        virtual void OnFieldFinished();
        virtual void UseSuggestion(int n);
        std::string GetSuggestion(int n) const;

        void ClearSuggestions();
        void AddSuggestion(int ID, std::string name);
        int GetSuggestionCount() const;

        const std::string &GetFieldName() const { return m_fieldName; }
        void SetFieldName(std::string &name) { m_fieldName = name; }

        bool HasValue() const { return m_hasValue; }

        void SetInputType(INPUT_TYPE type) { m_type = type; }
        INPUT_TYPE GetInputType() const { return m_type; }

        virtual std::string GetCurrentValue() const = 0;

        void SetDatabase(DatabaseLayer *database) { m_database = database; }

    protected:
        INPUT_TYPE m_type;
        DatabaseLayer *m_database;

        std::vector<Suggestion *> m_suggestions;

        std::string m_userSearch;
        std::string m_fieldName;

        bool m_hasValue;
    };

} /* namespace pft */

#endif /* FIELD_INPUT_H */
