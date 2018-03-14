#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "database_object.h"

#include <string>

namespace pft {

    // Implements a data structure for storing account information. This is usually
    // mapped to the ACCOUNTS database table
    class Account : public DatabaseObject {
    public:
        Account();
        ~Account();

        // Account ID
        int m_id;

        // Account Name
        std::string m_name;

        // Account Parent Account
        int m_parentId;

        virtual void RegisterAttributes();
    };

} /* namespace pft */

#endif /* ACCOUNT_H */
