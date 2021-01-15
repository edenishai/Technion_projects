#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "base_event.h"
#include "date_wrap.h"
#include "linked_list.h"
#include "iterator.h"
using mtm::BaseEvent;

namespace mtm {
    class EventContainer : public List<BaseEvent> {
    public:
        EventContainer();
        ~EventContainer();
        virtual void add(const BaseEvent& event);

        typedef Iterator<BaseEvent> EventIterator;
        
        EventIterator begin();
        EventIterator end();
    };
}

#endif /* EVENT_CONTAINER_H */