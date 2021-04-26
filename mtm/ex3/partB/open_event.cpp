#include "open_event.h"


namespace mtm{

    using std::string;

    const int MAX_ID=1234567890;
    const int MIN_ID=1;

    OpenEvent::OpenEvent(const DateWrap& date, const string name):
        BaseEvent(date, name) { }

    void OpenEvent::registerParticipant(int student_id) 
    {
        if(student_id < MIN_ID || student_id > MAX_ID) 
        {
            throw InvalidStudent();
        }
        if(members_list.contains(student_id)) 
        {
            throw AlreadyRegistered();
        }
        members_list.insert(student_id);
    }

    BaseEvent* OpenEvent::clone() const 
    {
        return new OpenEvent(*this);
    }

}