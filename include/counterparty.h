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
  
  virtual void SetIntAttribute(std::string &name, int value);
  virtual int GetIntAttribute(std::string &name);
  
  virtual void SetStringAttribute(std::string &name, std::string &value);
  virtual std::string GetStringAttribute(std::string &name);
};

#endif /* COUNTERPART_H */
