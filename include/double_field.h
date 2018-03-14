#ifndef DOUBLE_FIELD_H
#define DOUBLE_FIELD_H

#include "field_input.h"

#include <string>

namespace pft {

	class DoubleField : public FieldInput {
		public:
			DoubleField();
			~DoubleField();

			virtual std::string GetCurrentValue() const;
			virtual bool SetUserSearch(std::string &search);

			void SetCurrentValue(double value) { m_currentValue = value; m_hasValue = true; }
			double GetDoubleValue() const { return m_currentValue; }

		protected:
			double m_currentValue;
	};

} /* namespace pft */

#endif /* DOUBLE_FIELD_H */
