#include <form.h>

namespace pft {

    Form::Form() {
        m_initialized = false;
    }

    Form::~Form() {

    }

    void Form::Initialize() {
        m_initialized = true;
    }

    int Form::GetNextEmptyField(int start) {
        int nFields = GetFieldCount();

        int i = start + 1;
        while (true) {
            // Increment
            if (i >= nFields) i = 0;
            if (i == start) return -1;
            if (!GetField(i)->HasValue()) return i;

            i++;
        }

        return -1;
    }

} /* namespace pft */
