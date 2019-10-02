#ifndef PFT_TRANSACTION_TYPE_H
#define PFT_TRANSACTION_TYPE_H

#include "database_object.h"

#include <string>

namespace pft {

    class TransactionType : public DatabaseObject {
    public:
        TransactionType();
        ~TransactionType();

        int m_id;
        std::string m_name;
        std::string m_description;

        virtual void RegisterAttributes();
    };

} /* namespace pft */

#endif /* PFT_TRANSACTION_TYPE_H */
