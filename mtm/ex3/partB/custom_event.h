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
        void isRegistrationBlocked(int student_id) override;
        CustomEvent* clone() override;

        class RegistrationBlocked : public Exception {};
    };

    template<typename CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const DateWrap date, const string name, CanRegister cr):
        BaseEvent(date, name), cr(cr) {  
    }

    template<typename CanRegister>
    void CustomEvent<CanRegister>::isRegistrationBlocked(int student_id) {
        if(!cr) {
            throw RegistrationBlocked();
        }
    }

    template<typename CanRegister>
    CustomEvent<CanRegister>* CustomEvent<CanRegister>::clone() {
        CustomEvent<CanRegister> copy(*this);
        return new CustomEvent<CanRegister>(copy);
    }
}

#endif /* CUSTOM_EVENT_H */