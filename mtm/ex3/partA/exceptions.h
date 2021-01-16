#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
//#include <exception> ?

namespace mtm {
    class Exception : public std::exception {
        class InvalidStudent {};
        class AlreadyRegistered {};
        class RegistrationBlocked {};
        class NotRegistered {};
        class AlreadyInvited {};
        class NotSupported {};
    };
}



#endif /* EXCEPTIONS_H */