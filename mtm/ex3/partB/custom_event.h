#ifndef CUSTOM_EVENT_H
#define CUSTOM_EVENT_H

#include "base_event.h"
using mtm::BaseEvent;

namespace mtm {
    template<typename CanRegister>
    class CustomEvent : public BaseEvent {
        CanRegister cr;
    public:
        CustomEvent(const DateWrap date, const string name, CanRegister cr);
        void isRegistrationBlocked(int student_id) const override;
        CustomEvent& clone() override;

        class RegistrationBlocked : public Exception {};
    };
}

#endif /* CUSTOM_EVENT_H */