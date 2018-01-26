#ifndef DATA_ATTRIBUTE_H
#define DATA_ATTRIBUTE_H

#include <string>

class DataAttribute
{
public:
	enum ATTRIBUTE_TYPE
	{
		TYPE_INT,
		TYPE_DOUBLE,
		TYPE_STRING,
		TYPE_CURRENCY
	};

public:
	DataAttribute();
	~DataAttribute();

	int GetAsInt() const;
	float GetAsFloat() const;
	const std::string *GetAsString() const;

	int *GetIntBinding() { return (int *)(m_binding); }
	float *GetFloatBinding() { return (float *)(m_binding); }
	std::string *GetStringBinding() { return (std::string *)(m_binding); }

	void SetBinding(void *binding) { m_binding = binding; }
	void SetName(std::string &name) { m_name = name; }
	void SetType(ATTRIBUTE_TYPE type) { m_type = type; }
	const std::string &GetName() const { return m_name; }
	ATTRIBUTE_TYPE GetType() const { return m_type; }

protected:

	void *m_binding;
	std::string m_name;
	ATTRIBUTE_TYPE m_type;

};

#endif /* DATA_ATTRIBUTE_H */