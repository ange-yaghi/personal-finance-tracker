#ifndef COUNTERPARTY_H
#define COUNTERPARTY_H

class Counterparty
{
public:
  Counterparty();
  ~Counterparty();
  
  int m_id;
  std::string m_name;
  std::string m_location;
  std::string m_notes;
  int m_parentId;
};

#endif /* COUNTERPART_H */
