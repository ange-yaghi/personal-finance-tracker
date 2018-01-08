#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction
{
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
};

#endif
