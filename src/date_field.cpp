#include <date_field.h>

#include <sstream>
#include <iomanip>
#include <time.h>

pft::DateField::DateField() {
    m_currentString = "";
    m_hasValue = false;
    m_monthOnly = false;
}

pft::DateField::~DateField() {

}

void pft::DateField::SetDateToday() {
    std::time_t time = std::time(nullptr);
	std::tm bt{};

	// Credit to Galik (StackOverflow)
#if defined(__unix__)
	localtime_r(&time, &bt);
#elif defined(_MSC_VER)
	localtime_s(&bt, &time);
#endif

    std::stringstream ss;
    ss << std::put_time(&bt, "%F");

    m_hasValue = true;
    m_currentString = ss.str();
}

bool pft::DateField::SetUserSearch(const std::string &search) {
    if (search == "t") {
        SetDateToday();
        return true;
    }

    FieldInput::SetUserSearch(search);
    m_currentString = search;

    std::stringstream inputString(search);

    std::string yearString;
    std::string  monthString;
    std::string  dayString;

    std::getline(inputString, yearString, '-');
    if (inputString.eof()) return false;
    std::getline(inputString, monthString, '-');
    if (inputString.eof()) {
        if (!m_monthOnly) return false;
    } else {
        if (m_monthOnly) return false;
    }

    if (!m_monthOnly) {
        std::getline(inputString, dayString, '-');
        if (!inputString.eof()) return false;
    }

    if (yearString.length() != 4) return false;
    if (monthString.length() != 2) return false;
    if (!m_monthOnly) {
        if (dayString.length() != 2) return false;
    }

    int year, month, day;

    std::stringstream ss;
    ss << yearString;
    ss >> year;

    if (!ss.eof() || ss.fail()) return false;

    ss.clear();
    ss << monthString;
    ss >> month;

    if (!ss.eof() || ss.fail()) return false;

    if (!m_monthOnly)
    {
        ss.clear();
        ss << dayString;
        ss >> day;

        if (!ss.eof() || ss.fail()) return false;
    }

    if (month <= 0) return false;
    if (month > 12) return false;

    if (!m_monthOnly)
    {
        if (day <= 0) return false;
        if (day > 31) return false;
    }

    m_hasValue = true;
    m_currentString = search;

    return true;
}
