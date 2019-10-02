#ifndef PFT_TRANSACTION_H
#define PFT_TRANSACTION_H

#include "database_object.h"

#include <string>

namespace pft {

    // Implements a transaction object which can be mapped to the 
    // TRANSACTIONS database table
    class Transaction : public DatabaseObject {
    public:
        Transaction();
        ~Transaction();

        // Transaction ID
        int m_id;

        // Transaction name
        std::string m_name;

        // Transaction type ID
        int m_typeId;

        // Transaction class ID
        int m_classId;

        // Transaction parent ID
        int m_parentEntityId;

        // Source account ID
        int m_sourceAccountId;

        // Transaction amount (in cents)
        int m_amount;

        // Transaction date
        std::string m_date;

        // Target account ID
        int m_targetAccountId;

        // Transaction notes
        std::string m_notes;

        virtual void RegisterAttributes();
    };

} // namespace pft

#endif /* PFT_TRANSACTION_H */
