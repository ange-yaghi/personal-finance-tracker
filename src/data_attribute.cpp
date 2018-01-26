#include <data_attribute.h>

DataAttribute::DataAttribute()
{

}

DataAttribute::~DataAttribute()
{

}

int DataAttribute::GetAsInt() const
{
	return *((int *)(m_binding));
}

float DataAttribute::GetAsFloat() const
{
	return *((float *)(m_binding));
}

const std::string *DataAttribute::GetAsString() const
{
	return ((const std::string *)(m_binding));
}