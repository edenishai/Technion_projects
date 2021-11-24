#ifndef CLOSED_EVENT_H
#define CLOSED_EVENT_H

#include "base_event.h"

namespace mtm 
{

    class ClosedEvent : public BaseEvent 
    {

        LinkedList<int> invitees_list;

    public:

        ClosedEvent(const DateWrap& date, const std::string name);
        ClosedEvent(const ClosedEvent& event)=default;
        ~ClosedEvent() override=default;
        void addInvitee(int student_id);
        void registerParticipant(int student_id) override;
        BaseEvent* clone() const override;

    };

}

#endif /* CLOSED_EVENT_H */