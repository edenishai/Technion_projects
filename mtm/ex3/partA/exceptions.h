#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

namespace mtm {
    class Exception : public std::exception {
        class AlreadyRegistered {};
        class RegistrationBlocked {};
        class NotRegistered {};
    };
}



#endif /* EXCEPTIONS_H */