#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "base_event.h"
#include "linked_list.h"
using mtm::BaseEvent;

namespace mtm {
    class EventContainer : public LinkedList<BaseEvent> {
    public:
        EventContainer();
        virtual void add(const BaseEvent& event) = 0;

        typedef Iterator<BaseEvent> EventIterator;
        
        EventIterator begin();
        EventIterator end();
    };
}

#endif /* EVENT_CONTAINER_H */