#include "../include/database_layer.h"

#include <sstream>
#include <iomanip>

pft::DatabaseLayer::DatabaseLayer() {
    /* void */
}

pft::DatabaseLayer::~DatabaseLayer() {
    /* void */
}

int pft::DatabaseLayer::StringToInt(const std::string &s) {
    std::stringstream ss(s);
    int result;

    ss >> result;
    return result;
}

std::string pft::DatabaseLayer::IntToString(int value) {
    std::stringstream ss;
    ss.fill('0');
    ss << std::setw(2) << value;
    return ss.str();
}

void pft::DatabaseLayer::ParseMonth(const std::string &s, int *year, int *month) {
    std::stringstream ss(s);

    std::string yearBuffer, monthBuffer;

    std::getline(ss, yearBuffer, '-');
    std::getline(ss, monthBuffer, '-');

    *year = StringToInt(yearBuffer);
    *month = StringToInt(monthBuffer);
}
