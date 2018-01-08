#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "database_object.h"

class Transaction: public DatabaseObject
{
public:
  Transaction();
  ~Transaction();
  
  int m_id;
  std::string m_name;
  std::string m_type;
  int m_classId;
  int m_parentEntityId;
  int m_accountId;
  int m_amount; // In cents
  std::string m_date;
  int m_counterpartyId;
  std::string m_notes;
  
  virtual void SetIntAttribute(std::string &name, int value);
  virtual int GetIntAttribute(std::string &name);
  
  virtual void SetStringAttribute(std::string &name, std::string &value);
  virtual std::string GetStringAttribute();
};

#endif
