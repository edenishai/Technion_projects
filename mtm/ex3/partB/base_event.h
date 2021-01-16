#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include "linked_list.h"
#include <string.h>
#include <iostream>
#include <stdbool.h>
using std::string;
using std::ostream;
using mtm::Exception;
using mtm::DateWrap;

namespace mtm {
    class BaseEvent {
        const DateWrap date;
        const string name;
        LinkedList<int> members_list;
    public:
        BaseEvent(const DateWrap date, const string name = "");
        ~BaseEvent() = default;
        BaseEvent(const BaseEvent& event) = default;
        BaseEvent& operator=(const BaseEvent& event) = default;
        void registerParticipant(int student_id);
        void unregisterParticipant(int student_id);
        virtual void isRegistrationBlocked(int student_id) const;
        ostream& printShort(ostream& os) const;
        ostream& printLong(ostream& os) const;
        virtual BaseEvent& clone();
        bool operator>(const BaseEvent& event) const;
        bool operator<(const BaseEvent& event) const;
        bool operator==(const BaseEvent& event) const;

        class AlreadyRegistered : public Exception {};
        class NotRegistered : public Exception {};
        class InvalidStudent : public Exception {};
    };
}

#endif /* BASE_EVENT_H */