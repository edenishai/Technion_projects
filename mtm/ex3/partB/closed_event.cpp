#include "closed_event.h"
using mtm::ClosedEvent;

ClosedEvent::ClosedEvent(const DateWrap date, const string name):
    BaseEvent(date, name), invitees_list() {
}

void ClosedEvent::addInvitee(int student_id) {
    if(student_id < 1 || student_id > 1234567890) {
        throw InvalidStudent();
    }
    if(invitees_list.contains(student_id)) {
        throw AlreadyInvited();
    }
    invitees_list.insert(student_id);
}

void ClosedEvent::isRegistrationBlocked(int student_id) {
    if(!(invitees_list.contains(student_id))) {
        throw RegistrationBlocked();
    }
}

ClosedEvent* ClosedEvent::clone() const {
    return new ClosedEvent(*this);
}
