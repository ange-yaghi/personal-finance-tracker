#include <database_object.h>

namespace pft {

    DatabaseObject::DatabaseObject() {}

    DatabaseObject::~DatabaseObject() {
        int n = m_attributes.size();
        for (int i = 0; i < n; i++) {
            delete m_attributes[i];
        }
    }

    void DatabaseObject::SetIntAttribute(const std::string &name, int value) {
        *(FindDataAttribute(name)->GetIntBinding()) = value;
    }

    int DatabaseObject::GetIntAttribute(const std::string &name) const {
        return FindDataAttribute(name)->GetAsInt();
    }

    void DatabaseObject::SetStringAttribute(const std::string &name, const std::string &value) {
        *(FindDataAttribute(name)->GetStringBinding()) = value;
    }


    const std::string &DatabaseObject::GetStringAttribute(const std::string &name) const {
        return *(FindDataAttribute(name)->GetAsString());
    }

    void DatabaseObject::SetCurrencyAttribute(const std::string &name, double value) {
        int intValue;
        if (value < 0) intValue = (int)((value * 100.0) - 0.5);
        else intValue = (int)((value * 100.0) + 0.5);
        *(FindDataAttribute(name)->GetIntBinding()) = intValue;
    }

    double DatabaseObject::GetCurrencyAttribute(const std::string &name) const {
        return (FindDataAttribute(name)->GetAsInt()) / 100.0;
    }

    DataAttribute::ATTRIBUTE_TYPE DatabaseObject::GetAttributeType(const std::string &name) {
        return FindDataAttribute(name)->GetType();
    }

    void DatabaseObject::RegisterAttribute(const std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void *binding) {
        DataAttribute *newAttribute = new DataAttribute;
        newAttribute->SetName(name);
        newAttribute->SetType(type);
        newAttribute->SetBinding(binding);

        m_attributes.push_back(newAttribute);
    }

    DataAttribute *DatabaseObject::FindDataAttribute(const std::string &name) const {
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