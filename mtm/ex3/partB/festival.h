#ifndef FESTIVAL_H
#define FESTIVAL_H

#include "event_container.h"
#include "open_event.h"
#include "closed_event.h"
using mtm::EventContainer;

namespace mtm {
    class Festival : public EventContainer {
        DateWrap date;
    public:
        Festival(const DateWrap date);
        void add(const BaseEvent& event) override;

        class DateMismatch : public Exception {};
    };
}

#endif /* FESTIVAL_H */