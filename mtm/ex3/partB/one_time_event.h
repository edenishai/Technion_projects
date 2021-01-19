#ifndef ONE_TIME_EVENT_H
#define ONE_TIME_EVENT_H

#include "event_container.h"
using mtm::EventContainer;

namespace mtm {
    template<typename EventType>
    class OneTimeEvent : public EventContainer {

    };
}

#endif /* ONE_TIME_EVENT_H */