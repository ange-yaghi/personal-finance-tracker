#ifndef DATABASE_OBJECT_H
#define DATABASE_OBJECT_H

#include <string>
#include <vector>
#include <data_attribute.h>

class DatabaseObject
{
public:
	DatabaseObject();
	~DatabaseObject();
  
	virtual void SetIntAttribute(std::string &name, int value) = 0;
	virtual int GetIntAttribute(std::string &name) = 0;
  
	virtual void SetStringAttribute(std::string &name, std::string &value) = 0;
	virtual std::string GetStringAttribute(std::string &name) = 0;

protected:
	void RegisterAttribute(std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void **binding);

private:
	std::vector<DataAttribute *> m_attributes;

};

#endif /* DATABASE_OBJECT_H */
