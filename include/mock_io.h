#ifndef PFT_MOCK_IO_H
#define PFT_MOCK_IO_H

#include "io.h"

#include <queue>
#include <sstream>

namespace pft {

    class MockIo : public Io {
    public:
        MockIo();
        ~MockIo();

        virtual std::string getLine();
        virtual void put(const std::string &s);

        void addInput(const std::string &input);

        std::string getOutput() const;
        void clearOutput();

    protected:
        std::queue<std::string> m_inputs;
        std::stringstream m_outputRecorder;
    };

} /* namespace pft */

#endif /* PFT_MOCK_IO_H */
