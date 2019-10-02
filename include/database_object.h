#ifndef PFT_DATABASE_OBJECT_H
#define PFT_DATABASE_OBJECT_H

#include "data_attribute.h"

#include <string>
#include <vector>

namespace pft {

    class DatabaseObject {
    public:
        DatabaseObject();
        ~DatabaseObject();

        void SetIntAttribute(const std::string &name, int value);
        int GetIntAttribute(const std::string &name) const;

        void SetCurrencyAttribute(const std::string &name, double value);
        double GetCurrencyAttribute(const std::string &name) const;

        void SetStringAttribute(const std::string &name, const std::string &value);
        const std::string &GetStringAttribute(const std::string &name) const;

        DataAttribute::ATTRIBUTE_TYPE GetAttributeType(const std::string &name);

        virtual void RegisterAttributes() = 0;

        void Initialize();

    protected:
        void RegisterAttribute(const std::string &name, DataAttribute::ATTRIBUTE_TYPE type, void *binding);
        DataAttribute *FindDataAttribute(const std::string &name) const;

    private:
        std::vector<DataAttribute *> m_attributes;
    };

} /* namespace pft */

#endif /* PFT_DATABASE_OBJECT_H */
