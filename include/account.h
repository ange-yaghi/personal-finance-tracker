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
  
  virtual void SetIntAttribute(std::string &name, int value) = 0;
  virtual int GetIntAttribute(std::string &name) = 0;
  
  virtual void SetStringAttribute(std::string &name, std::string &value) = 0;
  virtual std::string GetStringAttribute(std::string &name) = 0;
};

#endif /* ACCOUNT_H */
