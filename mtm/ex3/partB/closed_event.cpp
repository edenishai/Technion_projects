#include "closed_event.h"


namespace mtm
{

    using std::string;

    const int MAX_ID=1234567890;
    const int MIN_ID=1;

    ClosedEvent::ClosedEvent(const DateWrap& date, const string name):
        BaseEvent(date, name), invitees_list() {}

    void ClosedEvent::addInvitee(int student_id) 
    {
        if(student_id < MIN_ID || student_id > MAX_ID) 
        {
            throw InvalidStudent();
        }
        if(invitees_list.contains(student_id)) 
        {
            throw AlreadyInvited();
        }
        invitees_list.insert(student_id);
    }

    void ClosedEvent::registerParticipant(int student_id) 
    {
        if(student_id < MIN_ID || student_id > MAX_ID) 
        {
            throw InvalidStudent();
        }
        if(!(invitees_list.contains(student_id))) 
        {
            throw RegistrationBlocked();
        }
        if(members_list.contains(student_id)) 
        {
            throw AlreadyRegistered();
        }
        members_list.insert(student_id);
    }

    BaseEvent* ClosedEvent::clone() const 
    {
        return new ClosedEvent(*this);
    }

}