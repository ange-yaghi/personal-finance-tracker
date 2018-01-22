#ifndef DOUBLE_FIELD_H
#define DOUBLE_FIELD_H

#include "field_input.h"

#include <string>

class DoubleField : public FieldInput
{
public:
	DoubleField();
	~DoubleField();

	virtual std::string GetCurrentValue() const;
	virtual bool SetUserSearch(std::string &search);

protected:

	double m_currentValue;

};

#endif /* DOUBLE_FIELD_H */
