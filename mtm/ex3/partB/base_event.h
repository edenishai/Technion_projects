#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include "../partA/date_wrap.h"
using mtm::DateWrap;
#include "../partA/exceptions.h"
using mtm::Exception;
#include <string.h>
using std::string;
#include "linked_list.h"
#include <iostream>
#include <stdbool.h>
using std::ostream;

namespace mtm {
    class BaseEvent {
        DateWrap date;
        string event_name;
        List<int> members_list;
    public:
        BaseEvent(DateWrap date, const string event_name = "");
        ~BaseEvent() = default;
        BaseEvent(const BaseEvent& event) = default;
        BaseEvent& operator=(const BaseEvent& event) = default;
        void registerParticipant(int student_id);
        void unregisterParticipant(int student_id);
        virtual bool isRegistrationBlocked(List<int> members_list, int student_id);
        ostream& printShort(ostream& os);
        ostream& printLong(ostream& os);
        BaseEvent& clone();

        class AlreadyRegistered : public Exception {};
        class RegistrationBlocked : public Exception {};
        class NotRegistered : public Exception {};
    };
}

#endif /* BASE_EVENT_H */