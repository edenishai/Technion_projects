#include "closed_event.h"
using mtm::ClosedEvent;

ClosedEvent::ClosedEvent(const DateWrap date, const string name):
    BaseEvent(date, name), guest_list() {
}

void ClosedEvent::addInvitee(int student_id) {
    if(student_id < 1 || student_id > 1234567890) {
        throw InvalidStudent();
    }
    if(guest_list.contains(student_id)) {
        throw AlreadyInvited();
    }
    guest_list.insert(student_id);
}

void ClosedEvent::isRegistrationBlocked(int student_id) {
    if(!(guest_list.contains(student_id))) {
        throw RegistrationBlocked();
    }
}

ClosedEvent* ClosedEvent::clone() const {
    return new ClosedEvent(*this);
}