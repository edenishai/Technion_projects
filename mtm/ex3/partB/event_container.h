#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "base_event.h"
#include "linked_list.h"
using mtm::BaseEvent;

namespace mtm {
    class EventContainer {
    protected:
        LinkedList<BaseEvent&> events_list;
    public:
        class EventIterator {
        protected:
            Node<BaseEvent&>* iterator;
        public:
            EventIterator();
            EventIterator(Node<BaseEvent&>* node);
            EventIterator(const EventIterator& event_iter);
            ~EventIterator() = default;
            BaseEvent& operator*() const;
            EventIterator& operator=(const EventIterator& event_iter);
            EventIterator& operator++();
            bool operator==(const EventIterator& event_iter) const;
            bool operator!=(const EventIterator& event_iter) const;
            friend class EventContainer;
            //friend class Schedule;
        };

        EventContainer();
        virtual void add(const BaseEvent& event) = 0;

        EventIterator begin();
        EventIterator end();
        EventIterator getNext();
    };
}

#endif /* EVENT_CONTAINER_H */