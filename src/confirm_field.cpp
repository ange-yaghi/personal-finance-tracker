#include "../include/confirm_field.h"

pft::ConfirmField::ConfirmField() {
	m_currentString = "";
	m_hasValue = false;
}

pft::ConfirmField::~ConfirmField() {
    /* void */
}

bool pft::ConfirmField::SetUserSearch(std::string &search) {
	FieldInput::SetUserSearch(search);
	m_currentString = search;
	m_hasValue = true;

	return true;
}
