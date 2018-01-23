#include <database_object.h>

DatabaseObject::DatabaseObject()
{
}

DatabaseObject::~DatabaseObject()
{
}

void DatabaseObject::RegisterAttribute(std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void **binding)
{
	DataAttribute *newAttribute = new DataAttribute;
	newAttribute->SetName(name);
	newAttribute->SetType(type);
	newAttribute->SetBinding(binding);

	m_attributes.push_back(newAttribute);
}
