#include "field_input.h"

namespace pft {

	FieldInput::FieldInput() {
		m_hasValue = false;
	}

	FieldInput::~FieldInput() {}

	bool FieldInput::SetUserSearch(std::string &search) {
		return true;
	}

	void FieldInput::OnFieldFinished() {}

	void FieldInput::UseSuggestion(int n) {}

	std::string FieldInput::GetSuggestion(int n) const {
		return m_suggestions[n]->SuggestionString;
	}

	int FieldInput::GetSuggestionCount() const {
		return m_suggestions.size();
	}

	void FieldInput::ClearSuggestions() {
		int size = m_suggestions.size();

		for (int i = 0; i < size; i++) {
			delete m_suggestions[i];
		}

		m_suggestions.clear();
	}

	void FieldInput::AddSuggestion(int ID, std::string name) {
		Suggestion *newSuggestion = new Suggestion;
		newSuggestion->Id = ID;
		newSuggestion->SuggestionString = name;
		m_suggestions.push_back(newSuggestion);
	}

} /* namespace pft */
