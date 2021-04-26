#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace mtm
{

    class Exception : public std::exception {};

    class InvalidDate : public Exception
    {
    public:
        InvalidDate() = default;
        const std::string what();
    };

    class NegativeDays : public Exception 
    {
    public:
        NegativeDays() = default;
        const std::string what();
    };

    class DateMismatch : public Exception 
    {
    public:
        DateMismatch() = default;
        const std::string what();
    };

    class InvalidStudent : public Exception 
    {
    public:
        InvalidStudent() = default;
        const std::string what();
    };

    class AlreadyRegistered : public Exception 
    {
    public:
        AlreadyRegistered() = default;
        const std::string what();
    };

    class RegistrationBlocked : public Exception 
    {
    public:
        RegistrationBlocked() = default;
        const std::string what();
    };

    class NotRegistered : public Exception 
    {
    public:
        NotRegistered() = default;
        const std::string what();
    };

    class AlreadyInvited : public Exception {
    public:
        AlreadyInvited() = default;
        const std::string what();
    };

    class NotSupported : public Exception {
    public:
        NotSupported() = default;
        const std::string what();
    };

    class InvalidNumber : public Exception {
    public:
        InvalidNumber() = default;
        const std::string what();
    };

    class InvalidInterval : public Exception {
    public:
        InvalidInterval() = default;
        const std::string what();
    };
    
    class EventAlreadyExists : public Exception {
    public:
        EventAlreadyExists() = default;
        const std::string what();
    };

    class EventDoesNotExist : public Exception {
    public:
        EventDoesNotExist() = default;
        const std::string what();
    };

}

#endif /* EXCEPTIONS_H */