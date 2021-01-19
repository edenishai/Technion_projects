#include "open_event.h"
using mtm::OpenEvent;

using mtm::InvalidStudent;
using mtm::AlreadyRegistered;

OpenEvent::OpenEvent(const DateWrap date, const string name):
    BaseEvent(date, name) {
        /*
        Node<int>* temp = members_list.getHead();
        temp = NULL;
        */
}

void OpenEvent::registerParticipant(int student_id) {
    if(student_id < 1 || student_id > 1234567890) {
        throw InvalidStudent();
    }
    if(members_list.contains(student_id)) {
        throw AlreadyRegistered();
    }
    members_list.insert(student_id);
}

BaseEvent* OpenEvent::clone() const {
    return new OpenEvent(*this);
}