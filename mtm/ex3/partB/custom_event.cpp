#include "custom_event.h"
using mtm::CustomEvent;

template<typename CanRegister>
CustomEvent<CanRegister>::CustomEvent(const DateWrap date, const string name, CanRegister cr):
    BaseEvent(date, name), cr(cr) {  
}

template<typename CanRegister>
void CustomEvent<CanRegister>::isRegistrationBlocked(int student_id) const {
    if(!cr) {
        throw RegistrationBlocked();
    }
}

template<typename CanRegister>
CustomEvent<CanRegister>& CustomEvent<CanRegister>::clone() {
    CustomEvent<CanRegister> copy(*this);
    return copy;
}