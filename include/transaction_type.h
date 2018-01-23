#ifndef TRANSACTION_TYPE_H
#define TRANSACTION_TYPE_H

#include "database_object.h"

#include <string>

class TransactionType : public DatabaseObject
{
public:
	TransactionType();
	~TransactionType();

	int m_id;
	std::string m_name;

	virtual void SetIntAttribute(std::string &name, int value);
	virtual int GetIntAttribute(std::string &name);

	virtual void SetStringAttribute(std::string &name, std::string &value);
	virtual std::string GetStringAttribute(std::string &name);
};

#endif /* TRANSACTION_TYPE_H */