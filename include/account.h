#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "database_object.h"

#include <string>

class Account : public DatabaseObject
{
public:
	Account();
	~Account();
  
	int m_id;
	std::string m_name;
	int m_parentId;
  
	virtual void RegisterAttributes();
};

#endif /* ACCOUNT_H */
