#ifndef CLOSED_EVENT_H
#define CLOSED_EVENT_H

#include "base_event.h"
using mtm::BaseEvent;

namespace mtm {
    class ClosedEvent : public BaseEvent {
        LinkedList<int> guest_list;
    public:
        ClosedEvent(const DateWrap date, const string name = "");
        void addInvitee(int student_id);
        void isRegistrationBlocked(int student_id) override;
        ClosedEvent* clone() const override;

        class RegistrationBlocked : public Exception {};
        class AlreadyInvited: public Exception {};
    };
}

#endif /* CLOSED_EVENT_H */