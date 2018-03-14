#include <string_field.h>

namespace pft {

	StringField::StringField() {
		m_currentString = "";
		m_hasValue = false;
	}

	StringField::~StringField() {}

	bool StringField::SetUserSearch(std::string &search) {
		FieldInput::SetUserSearch(search);
		m_currentString = search;
		m_hasValue = true;

		return true;
	}

} /* namespace pft */
