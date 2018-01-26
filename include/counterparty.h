#ifndef COUNTERPARTY_H
#define COUNTERPARTY_H

#include "database_object.h"

#include <string>

class Counterparty : public DatabaseObject
{
public:
	Counterparty();
	~Counterparty();
  
	int m_id;
	std::string m_name;
	std::string m_location;
	std::string m_notes;
	int m_parentId;
  
	virtual void RegisterAttributes();
};

#endif /* COUNTERPART_H */
