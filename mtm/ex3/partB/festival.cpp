#include "festival.h"

namespace mtm
{

    Festival::Festival(const DateWrap& date):
        EventContainer(), date(date) { }

    void Festival::add(const BaseEvent& event) 
    {
        const DateWrap& event_date = event.getDate();
        if(event_date != date) 
        {
            throw DateMismatch();
        }
        BaseEvent* copy = event.clone();
        pointers_vector.add(copy);
        this->events_list.insert(*copy);
    }

}