#ifndef OPEN_EVENT_H
#define OPEN_EVENT_H

#include "base_event.h"

namespace mtm 
{

    class OpenEvent : public BaseEvent 
    {

    public:

        OpenEvent(const DateWrap& date, const std::string name);
        ~OpenEvent() override=default;
        void registerParticipant(int student_id) override;
        BaseEvent* clone() const override;

    };

}

#endif /* OPEN_EVENT_H */