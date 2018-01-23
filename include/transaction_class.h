#ifndef TRANSACTION_CLASS_H
#define TRANSACTION_CLASS_H

#include "database_object.h"

#include <string>

class TransactionClass : public DatabaseObject
{
public:
  TransactionClass();
  ~TransactionClass();
  
  int m_id;
  std::string m_name;
  int m_parentId;
  
  virtual void SetIntAttribute(std::string &name, int value);
  virtual int GetIntAttribute(std::string &name);
  
  virtual void SetStringAttribute(std::string &name, std::string &value);
  virtual std::string GetStringAttribute(std::string &name);
};

#endif
