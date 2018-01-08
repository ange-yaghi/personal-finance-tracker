#ifndef TRANSACTION_CLASS_H
#define TRANSACTION_CLASS_H

class TransactionClass
{
public:
  TransactionClass();
  ~TransactionClass();
  
  int m_id;
  std::string m_name;
  int m_parentId;
};

#endif
