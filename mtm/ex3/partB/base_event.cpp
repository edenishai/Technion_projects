#include "base_event.h"
using mtm::BaseEvent;

BaseEvent::BaseEvent(const DateWrap date, const string name):
    date(date), name(name), members_list() {
        //Node<int>* head = members_list.getHead();
        //head = NULL;
}

BaseEvent::BaseEvent(const BaseEvent& event):
    date(event.date), name(event.name), members_list(event.members_list) {
}

void BaseEvent::registerParticipant(int student_id) {
    if(student_id < 1 || student_id > 1234567890) {
        throw InvalidStudent();
    }
    if(members_list.contains(student_id)) {
        throw AlreadyRegistered();
    }
    isRegistrationBlocked(student_id);
    members_list.insert(student_id);
}

void BaseEvent::unregisterParticipant(int student_id) {
    if(student_id < 1 || student_id > 1234567890) {
        throw InvalidStudent();
    }
    if(!members_list.contains(student_id)) {
        throw NotRegistered();
    }
    members_list.remove(student_id);
}

ostream& BaseEvent::printShort(ostream& os) {
    return os << name << " " << date << "\n";
}

ostream& BaseEvent::printLong(ostream& os) {
    return os << name << " " << date << "\n" << members_list;
}

const DateWrap& BaseEvent::getDate() const {
    return date;
}

bool BaseEvent::operator>(const BaseEvent& event) const {
    if(date > event.date) {
        return true;
    }
    if(date == event.date) {
        if(name.compare(event.name) > 0) {
            return true;
        }
    }
    return false;
}

bool BaseEvent::operator==(const BaseEvent& event) const {
    if(date == event.date && !name.compare(event.name)) {
        return true;
    }
    return false;
}

bool BaseEvent::operator<(const BaseEvent& event) const {
    if(!operator>(event) && !operator==(event)) {
        return true;
    }
    return false;
}