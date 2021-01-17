#ifndef RECURRING_EVENT_H
#define RECURRING_EVENT_H

#include "event_container.h"
using mtm::EventContainer;

namespace mtm {
    template<typename EventType>
    class RecurringEvent : public EventContainer {
        DateWrap first_date;
        string name;
    public:
        RecurringEvent(const DateWrap first_date, const string name, int num_occurrences, int interval_days);
        void add(const BaseEvent& event) override;
        class InvalidNumber : public Exception {};
        class InvalidInterval : public Exception {};
        class NotSupported : public Exception {};
    };

    template<typename EventType>
    RecurringEvent<EventType>::RecurringEvent(const DateWrap first_date, const string name,
                                                            int num_occurrences, int interval_days):
        EventContainer(), first_date(first_date), name(name), num_occurrences(num_occurrences),
                                                                                     interval_days(interval_days) {
        //to complete
                                                                                
    }

    template<typename EventType>
    void RecurringEvent<EventType>::add(const BaseEvent& event) {
        throw NotSupported();
    }
}

#endif /* RECURRING_EVENT_H */