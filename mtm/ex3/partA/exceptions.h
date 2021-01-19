#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>

using std::string;
using std::exception;

namespace mtm{
    class Exception : public exception {};
    class InvalidDate : public Exception {
    public:
        InvalidDate() = default;
        const string what();
    };
    class NegativeDays : public Exception {
    public:
        NegativeDays() = default;
        const string what();
    };
    class DateMismatch : public Exception {
    public:
        DateMismatch() = default;
        const string what();
    };
    class InvalidStudent : public Exception {
    public:
        InvalidStudent() = default;
        const string what();
    };
    class AlreadyRegistered : public Exception {
    public:
        AlreadyRegistered() = default;
        const string what();
    };
    class RegistrationBlocked : public Exception {
    public:
        RegistrationBlocked() = default;
        const string what();
    };
    class NotRegistered : public Exception {
    public:
        NotRegistered() = default;
        const string what();
    };
    class AlreadyInvited : public Exception {
    public:
        AlreadyInvited() = default;
        const string what();
    };
    class NotSupported : public Exception {
    public:
        NotSupported() = default;
        const string what();
    };
    class InvalidNumber : public Exception {
    public:
        InvalidNumber() = default;
        const string what();
    };
    class InvalidInterval : public Exception {
    public:
        InvalidInterval() = default;
        const string what();
    };
}

#endif /* EXCEPTIONS_H */