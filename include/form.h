#ifndef PFT_FORM_H
#define PFT_FORM_H

#include "field_input.h"

#include <vector>

namespace pft {

    /* Forward Declarations */
    class DatabaseLayer;

    class Form {
    public:
        Form();
        ~Form();

        virtual void Initialize();
        bool IsInitialized() const { return m_initialized; }

        virtual void Copy(Form *target) = 0;

        int GetFieldCount() const { return (int)m_fields.size(); }
        FieldInput *GetField(int i) { return m_fields[i]; }

        void SetDatabaseLayer(DatabaseLayer *db) { m_databaseLayer = db; }

        int GetNextEmptyField(int start);

    protected:
        bool m_initialized;

        void RegisterField(FieldInput *field) {
            field->SetDatabase(m_databaseLayer);
            m_fields.push_back(field);
        }

        std::vector<FieldInput *> m_fields;

        DatabaseLayer *m_databaseLayer;
    };

} /* namespace pft */

#endif /* PFT_FORM_H */
