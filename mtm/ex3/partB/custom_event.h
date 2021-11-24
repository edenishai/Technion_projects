#ifndef CUSTOM_EVENT_H
#define CUSTOM_EVENT_H

#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include "base_event.h"
#include <cstring>


namespace mtm {

    const int MAX_ID=1234567890;
    const int MIN_ID=1;

    template<typename CanRegister>
    class CustomEvent : public BaseEvent 
    {

        CanRegister cr;
    
    public:
    
        CustomEvent(const DateWrap& date, const std::string name, CanRegister cr);
        ~CustomEvent() override=default;
        void registerParticipant(int student_id) override;
        BaseEvent* clone() const override;
    
    };

    template<typename CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const DateWrap& date, const std::string name, CanRegister cr):
        BaseEvent(date, name), cr(cr) { }

    template<typename CanRegister>
    void CustomEvent<CanRegister>::registerParticipant(int student_id) 
    {
        if(student_id < MIN_ID || student_id > MAX_ID) 
        {
            throw InvalidStudent();
        }
        if(members_list.contains(student_id)) 
        {
            throw AlreadyRegistered();
        }
        if(!cr(student_id)) 
        {
            throw RegistrationBlocked();
        }
        members_list.insert(student_id);
    }

    template<typename CanRegister>
    BaseEvent* CustomEvent<CanRegister>::clone() const 
    {
        return new CustomEvent(*this);
    }
}

#endif /* CUSTOM_EVENT_H */