#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include "linked_list.h"
#include <string>
#include <iostream>
#include <cstdbool>

namespace mtm 
{

    class BaseEvent 
    {

        DateWrap date;
        std::string name;

    protected:

        LinkedList<int> members_list;

    public:

        BaseEvent(const DateWrap& date, const std::string name);
        BaseEvent(const BaseEvent& event);
        virtual ~BaseEvent() = default;
        BaseEvent& operator=(const BaseEvent& event) = default;
        virtual void registerParticipant(int student_id)=0;
        void unregisterParticipant(int student_id);
        std::ostream& printShort(ostream& os) const;
        std::ostream& printLong(ostream& os) const;
        virtual BaseEvent* clone() const = 0;
        bool operator>(const BaseEvent& event) const;
        bool operator<(const BaseEvent& event) const;
        bool operator==(const BaseEvent& event) const;
                
        /**
         * Returns the date of the event by reference. It's const for preventing any changes.
         */        
        const DateWrap& getDate() const;

        /**
         * Returns the name of the event.
         */ 
        const std::string getName() const;

    };

}

#endif /* BASE_EVENT_H */