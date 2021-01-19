#include "festival.h"
using mtm::Festival;

using mtm::DateMismatch;

Festival::Festival(DateWrap date):
    EventContainer(), date(date) {
}

void Festival::add(const BaseEvent& event) {
    const DateWrap& event_date = event.getDate();
    if(event_date != date) {
        throw DateMismatch();
    }
    BaseEvent* copy = event.clone();
    *copy = event;
    this->events_list.insert(*copy);
}