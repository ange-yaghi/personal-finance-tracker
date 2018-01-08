#ifndef TRANSACTION_CLASS_H
#define TRANSACTION_CLASS_H

#include "database_object.h"

class TransactionClass : public DatabaseObject
{
public:
  TransactionClass();
  ~TransactionClass();
  
  int m_id;
  std::string m_name;
  int m_parentId;
  
  virtual void SetIntAttribute(std::string &name, int value) = 0;
  virtual int GetIntAttribute(std::string &name) = 0;
  
  virtual void SetStringAttribute(std::string &name, std::string &value) = 0;
  virtual std::string GetStringAttribute() = 0;
};

#endif
