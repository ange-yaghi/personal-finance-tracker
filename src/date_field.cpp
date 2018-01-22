#include <date_field.h>

#include <sstream>

DateField::DateField()
{
	m_currentString = "";
	m_hasValue = false;
}

DateField::~DateField()
{

}

bool DateField::SetUserSearch(std::string &search)
{
	FieldInput::SetUserSearch(search);
	m_currentString = search;

	std::stringstream inputString(search);

	std::string yearString;
	std::string  monthString;
	std::string  dayString;

	std::getline(inputString, yearString, '-');
	if (inputString.eof()) return false;
	std::getline(inputString, monthString, '-');
	if (inputString.eof()) return false;
	std::getline(inputString, dayString, '-');
	if (!inputString.eof()) return false;

	if (yearString.length() != 4) return false;
	if (monthString.length() != 2) return false;
	if (dayString.length() != 2) return false;

	int year, month, day;

	std::stringstream ss;
	ss << yearString;
	ss >> year;

	if (!ss.eof() || ss.fail()) return false;

	ss.clear();
	ss << monthString;
	ss >> month;

	if (!ss.eof() || ss.fail()) return false;

	ss.clear();
	ss << dayString;
	ss >> day;

	if (!ss.eof() || ss.fail()) return false;

	if (month <= 0) return false;
	if (month > 12) return false;
	if (day <= 0) return false;
	if (day > 31) return false;

	m_hasValue = true;
	m_currentString = search;

	return true;
}