#include <database_object.h>

namespace pft {

	DatabaseObject::DatabaseObject() {}

	DatabaseObject::~DatabaseObject() {
		int n = m_attributes.size();
		for (int i = 0; i < n; i++) {
			delete m_attributes[i];
		}
	}

	void DatabaseObject::SetIntAttribute(std::string &name, int value) {
		*(FindDataAttribute(name)->GetIntBinding()) = value;
	}

	int DatabaseObject::GetIntAttribute(std::string &name) {
		return FindDataAttribute(name)->GetAsInt();
	}

	void DatabaseObject::SetStringAttribute(std::string &name, std::string &value) {
		*(FindDataAttribute(name)->GetStringBinding()) = value;
	}


	std::string DatabaseObject::GetStringAttribute(std::string &name) {
		return *(FindDataAttribute(name)->GetAsString());
	}

	void DatabaseObject::SetCurrencyAttribute(std::string &name, double value) {
		int intValue;
		if (value < 0) intValue = (int)((value * 100.0) - 0.5);
		else intValue = (int)((value * 100.0) + 0.5);
		*(FindDataAttribute(name)->GetIntBinding()) = intValue;
	}

	double DatabaseObject::GetCurrencyAttribute(std::string &name) {
		return (FindDataAttribute(name)->GetAsInt()) / 100.0;
	}

	DataAttribute::ATTRIBUTE_TYPE DatabaseObject::GetAttributeType(std::string &name) {
		return FindDataAttribute(name)->GetType();
	}

	void DatabaseObject::RegisterAttribute(std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void *binding) {
		DataAttribute *newAttribute = new DataAttribute;
		newAttribute->SetName(name);
		newAttribute->SetType(type);
		newAttribute->SetBinding(binding);

		m_attributes.push_back(newAttribute);
	}

	DataAttribute *DatabaseObject::FindDataAttribute(std::string &name) {
		int n = m_attributes.size();
		for (int i = 0; i < n; i++) {
			if (m_attributes[i]->GetName() == name)
				return m_attributes[i];
		}
		return NULL;
	}

	void DatabaseObject::Initialize() {
		RegisterAttributes();
	}

} /* namespace pft */