#include "..\include\console_io.h"

#include <iostream>
#include <fstream>

pft::ConsoleIo::ConsoleIo() {
    /* void */
}

pft::ConsoleIo::~ConsoleIo() {
    /* void */
}

std::string pft::ConsoleIo::getLine() {
    std::string output;
    std::getline(std::cin, output);

    return output;
}

void pft::ConsoleIo::put(const std::string &s) {
    std::cout << s;
}
