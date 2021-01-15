#include "event_container.h"
#include <stdbool.h>
using mtm::EventContainer;

EventContainer::EventIterator EventContainer::begin() {
    setIterator();
    return iterator;
}

EventContainer::EventIterator EventContainer::end() {
    setIterator();
    while(!iterator.isNull()) {
        ++iterator;
    }
    return iterator;
}

void EventContainer::add(const BaseEvent& event) {
    this->insert(event);
}