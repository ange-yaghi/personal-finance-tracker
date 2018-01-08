#ifndef DATABASE_OBJECT_H
#define DATABASE_OBJECT_H

class DatabaseObject
{
public:
  DatabaseObject();
  ~DatabaseObject();
  
  virtual void SetIntAttribute(std::string &name, int value) = 0;
  virtual int GetIntAttribute(std::string &name) = 0;
  
  virtual void SetStringAttribute(std::string &name, std::string &value) = 0;
  virtual std::string GetStringAttribute() = 0;
};

#endif /* DATABASE_OBJECT_H */
