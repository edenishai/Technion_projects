#include "base_event.h"

namespace mtm{

    using std::string;

    const int MAX_ID=1234567890;
    const int MIN_ID=1;

    BaseEvent::BaseEvent(const DateWrap& date, const string name):
            date(date), name(name), members_list() {}

    BaseEvent::BaseEvent(const BaseEvent& event):
            date(event.date), name(event.name), members_list() 
    {
        Node<int>* iterator = event.members_list.getHead();
        while(iterator) 
        {
            members_list.insert(iterator->getData());
            iterator = iterator->getNext();
        }
    }

    void BaseEvent::unregisterParticipant(int student_id) 
    {
        if(student_id < MIN_ID || student_id > MAX_ID) 
        {
            throw InvalidStudent();
        }
        if(!members_list.contains(student_id)) 
        {
            throw NotRegistered();
        }
        members_list.remove(student_id);
    }

    ostream& BaseEvent::printShort(ostream& os) const
    {
        return os << name << " " << date << "\n";
    }

    ostream& BaseEvent::printLong(ostream& os) const
    {
        return os << name << " " << date << "\n" << members_list;
    }

    bool BaseEvent::operator>(const BaseEvent& event) const 
    {
        if(date > event.date) 
        {
            return true;
        }
        if(date == event.date) 
        {
            if(name.compare(event.name) > 0) 
            {
                return true;
            }
        }
        return false;
    }

    bool BaseEvent::operator<(const BaseEvent& event) const 
    {
        if(!operator>(event) && !operator==(event)) 
        {
            return true;
        }
        return false;
    }

    bool BaseEvent::operator==(const BaseEvent& event) const 
    {
        if(date == event.date && !name.compare(event.name)) 
        {
            return true;
        }
        return false;
    }
    
    /**
     * Returns the date of the event by reference. It's const for preventing any changes.
     */  
    const DateWrap& BaseEvent::getDate() const 
    {
        return date;
    }

    /**
     * Returns the name of the event.
     */ 
    const string BaseEvent::getName() const 
    {
        return name;
    }

}