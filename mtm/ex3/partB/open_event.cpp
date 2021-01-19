#include "open_event.h"
using mtm::OpenEvent;

OpenEvent::OpenEvent(const DateWrap date, const string name):
    BaseEvent(date, name) {
}

void OpenEvent::isRegistrationBlocked(int student_id) {
    return;
}

BaseEvent* OpenEvent::clone() const {
    return new OpenEvent(*this);
}