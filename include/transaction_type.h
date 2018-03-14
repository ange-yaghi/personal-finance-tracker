#ifndef TRANSACTION_TYPE_H
#define TRANSACTION_TYPE_H

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

}

#endif /* TRANSACTION_TYPE_H */