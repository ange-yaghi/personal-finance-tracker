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
  
  virtual void SetIntAttribute(std::string &name, int value);
  virtual int GetIntAttribute(std::string &name);
  
  virtual void SetStringAttribute(std::string &name, std::string &value);
  virtual std::string GetStringAttribute(std::string &name);
};

#endif /* ACCOUNT_H */
