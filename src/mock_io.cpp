#include "../include/mock_io.h"

pft::MockIo::MockIo() {
    /* void */
}

pft::MockIo::~MockIo() {
    /* void */
}

std::string pft::MockIo::getLine() {
    std::string line = m_inputs.front();
    m_inputs.pop();

    return line;
}

void pft::MockIo::put(const std::string &s) {
    m_outputRecorder << s;
}

void pft::MockIo::addInput(const std::string &input) {
    m_inputs.push(input);
}

std::string pft::MockIo::getOutput() const {
    return m_outputRecorder.str();
}

void pft::MockIo::clearOutput() {
    m_outputRecorder.clear();
}
