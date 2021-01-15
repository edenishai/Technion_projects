#include "base_event.h"
using mtm::BaseEvent;

BaseEvent::BaseEvent(DateWrap date, const string event_name):
    date(date),
    event_name(string(event_name)),
    members_list() {
}

void BaseEvent::registerParticipant(int student_id) {
    if(members_list.contains(student_id)) {
        throw AlreadyRegistered();
    }
    isRegistrationBlocked(members_list, student_id);
    members_list.insert(student_id);
}

void BaseEvent::unregisterParticipant(int student_id) {
    if(!members_list.contains(student_id)) {
        throw NotRegistered();
    }
    members_list.remove(student_id);
}

ostream& BaseEvent::printShort(ostream& os) {
    return os << event_name << " " << date;
}

ostream& BaseEvent::printLong(ostream& os) {
    printShort(os);
    return os << members_list;
}

BaseEvent& BaseEvent::clone() {
    BaseEvent copy(date, event_name);
    members_list(copy.members_list);
    
}
