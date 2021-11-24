#ifndef EVENT_CONTAINER_H
#define EVENT_CONTAINER_H

#include "base_event.h"
#include "linked_list.h"
#include "ptr_vector.h"

namespace mtm 
{

    class EventContainer 
    {

    protected:

        LinkedList<BaseEvent&> events_list;
        PtrVector pointers_vector;
    
    public:

        class EventIterator 
        {
        
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
        
        };

        EventContainer();
        ~EventContainer();
        virtual void add(const BaseEvent& event) = 0;
        EventIterator begin() const;
        EventIterator end();
    
    };

}

#endif /* EVENT_CONTAINER_H */