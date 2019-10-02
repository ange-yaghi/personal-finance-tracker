#ifndef PFT_IO_H
#define PFT_IO_H

#include <string>

namespace pft {

    class Io {
    public:
        Io();
        ~Io();

        virtual std::string getLine() = 0;
        virtual void put(const std::string &s) = 0;
    };

} /* namespace pft */

#endif /* PFT_IO_H */
