#include "festival.h"

using mtm::Festival;

Festival::Festival(DateWrap date):
    EventContainer(), date(date) {
}

void Festival::add(const BaseEvent& event) {
    const DateWrap& event_date = event.getDate();
    if(event_date != date) {
        throw DateMismatch();
    }
    BaseEvent* copy = event.clone();
    this->events_list.insert(*copy);
}
