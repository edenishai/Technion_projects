#ifndef ONE_TIME_EVENT_H
#define ONE_TIME_EVENT_H

#include "event_container.h"
#include "ptr_vector.h"

namespace mtm 
{

    template<typename EventType>
    class OneTimeEvent : public EventContainer 
    {
    
        DateWrap date;
        std::string name;
    
    public:
    
        OneTimeEvent(const DateWrap& date, const std::string name);
        ~OneTimeEvent() =default;
        void add(const BaseEvent& event) override;
    
    };

    template<typename EventType>
    OneTimeEvent<EventType>::OneTimeEvent(const DateWrap& date, const std::string name):
        date(date), name(name) 
    {
        EventType* event = new EventType(date, name);
        events_list.insert(*event);
        pointers_vector.add(event);
    }

    template<typename EventType>
    void OneTimeEvent<EventType>::add(const BaseEvent& event) 
    {
        throw NotSupported();
    }
}

#endif /* ONE_TIME_EVENT_H */