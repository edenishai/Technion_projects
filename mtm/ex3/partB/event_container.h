#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "base_event.h"
#include "linked_list.h"
using mtm::BaseEvent;

namespace mtm {
    class EventContainer {
    protected:
        LinkedList<const BaseEvent&> events_list;
    public:
        class EventIterator {
        protected:
            BaseEvent* iterator;
        public:
            EventIterator();
            EventIterator(const EventIterator& event_iter);
            ~EventIterator() = default; //?
            BaseEvent& operator->();
            EventIterator& operator=(const EventIterator& event_iter);
            EventIterator& operator++();
            friend bool operator==(const EventIterator& event_iter1, const EventIterator& event_iter2);
            friend bool operator!=(const EventIterator& event_iter1, const EventIterator& event_iter2);
            //friend class Schedule;
        };

        EventContainer();
        virtual void add(const BaseEvent& event) = 0;
        
        EventIterator begin();
        EventIterator end();
    };
}

#endif /* EVENT_CONTAINER_H */