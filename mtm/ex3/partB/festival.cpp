#include "festival.h"
using mtm::Festival;

Festival::Festival(DateWrap date):
    EventContainer(), date(date) {
}

void Festival::add(const BaseEvent& event) {    //not to change const (test add)
    const DateWrap& event_date = event.getDate();
    if(event_date != date) {
        throw DateMismatch();
    }
    insert(event);  //not to change const
}