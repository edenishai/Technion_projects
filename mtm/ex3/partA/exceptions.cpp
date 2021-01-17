#include "exceptions.h"

namespace mtm {
    const string InvalidDate::what() {
        return string("InvalideDate");
    }

    const string NegativeDays::what() {
        return string("NegativeDays");
    }

    const string DateMismatch::what() {
        return string("DateMismatch");
    }

    const string InvalidStudent::what() {
        return string("InvalidStudent");
    }

    const string AlreadyRegistered::what() {
        return string("AlreadyRegistered");
    }

    const string RegistrationBlocked::what() {
        return string("RegistrationBlocked");
    }

    const string NotRegistered::what() {
        return string("NotRegistered");
    }

    const string AlreadyInvited::what() {
        return string("AlreadyInvited");
    }

    const string NotSupported::what() {
        return string("NotSupported");
    }

    const string InvalidNumber::what() {
        return string("InvalidNumber");
    }

    const string InvalidInterval::what() {
        return string("InvalidInterval");
    }
}