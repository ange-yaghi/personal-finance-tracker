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

        void SetIntAttribute(std::string &name, int value);
        int GetIntAttribute(std::string &name);

        void SetCurrencyAttribute(std::string &name, double value);
        double GetCurrencyAttribute(std::string &name);

        void SetStringAttribute(std::string &name, std::string &value);
        std::string GetStringAttribute(std::string &name);

        DataAttribute::ATTRIBUTE_TYPE GetAttributeType(std::string &name);

        virtual void RegisterAttributes() = 0;

        void Initialize();

    protected:
        void RegisterAttribute(std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void *binding);
        DataAttribute *FindDataAttribute(std::string &name);

    private:
        std::vector<DataAttribute *> m_attributes;
    };

} /* namespace pft */

#endif /* DATABASE_OBJECT_H */
