#ifndef DATABASE_OBJECT_H
#define DATABASE_OBJECT_H

#include <string>
#include <vector>
#include <data_attribute.h>

namespace pft {

    class DatabaseObject {
    public:
        DatabaseObject();
        ~DatabaseObject();

        void SetIntAttribute(const std::string &name, int value);
        int GetIntAttribute(const std::string &name);

        void SetCurrencyAttribute(const std::string &name, double value);
        double GetCurrencyAttribute(const std::string &name);

        void SetStringAttribute(const std::string &name, const std::string &value);
        std::string GetStringAttribute(const std::string &name);

        DataAttribute::ATTRIBUTE_TYPE GetAttributeType(const std::string &name);

        virtual void RegisterAttributes() = 0;

        void Initialize();

    protected:
        void RegisterAttribute(const std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void *binding);
        DataAttribute *FindDataAttribute(const std::string &name);

    private:
        std::vector<DataAttribute *> m_attributes;
    };

} /* namespace pft */

#endif /* DATABASE_OBJECT_H */
