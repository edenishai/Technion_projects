#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include "linked_list.h"
#include <string.h>
#include <iostream>
#include <cstdbool>
using std::string;
using std::ostream;
using mtm::DateWrap;

namespace mtm {
    class BaseEvent {
        DateWrap date;
        string name;
    protected:
        LinkedList<int> members_list;
    public:
        BaseEvent(const DateWrap date, const string name = "");
        BaseEvent(const BaseEvent& event) = default;
        ~BaseEvent() = default;
        BaseEvent& operator=(const BaseEvent& event) = default;
        virtual void registerParticipant(int student_id) = 0;
        void unregisterParticipant(int student_id);
        ostream& printShort(ostream& os);
        ostream& printLong(ostream& os);
        virtual BaseEvent* clone() const = 0;
        const DateWrap& getDate() const;
        bool operator>(const BaseEvent& event) const;
        bool operator<(const BaseEvent& event) const;
        bool operator==(const BaseEvent& event) const;
    };
}

#endif /* BASE_EVENT_H */