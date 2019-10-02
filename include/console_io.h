#ifndef PFT_CONSOLE_IO_H
#define PFT_CONSOLE_IO_H

#include "io.h"

namespace pft {

    class ConsoleIo : public Io {
    public:
        ConsoleIo();
        ~ConsoleIo();

        virtual std::string getLine();
        virtual void put(const std::string &s);
    };

} /* namespace pft */

#endif /* PFT_CONSOLE_IO_H */
