#ifndef TRANSACTION_CLASS_H
#define TRANSACTION_CLASS_H

#include <database_object.h>

#include <string>
#include <vector>

namespace pft {

    class TransactionClass : public DatabaseObject {
    public:
        TransactionClass();
        ~TransactionClass();

        int m_id;
        std::string m_name;
        std::string m_fullName;
		std::string m_description;
        int m_parentId;

        virtual void RegisterAttributes();

        TransactionClass *NewChild();
        int GetChildCount() { return (int)m_children.size(); }
        TransactionClass *GetChild(int i) { return m_children[i]; }

    protected:
        std::vector<TransactionClass *> m_children;
    };

} /* namespace pft */

#endif /* TRANSACTION_CLASS_H */
