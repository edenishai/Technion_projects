#include "event_container.h"
#include <stdbool.h>
using mtm::EventContainer;

EventContainer::EventContainer():
    LinkedList<BaseEvent>() {
}

EventContainer::EventIterator EventContainer::begin() {
    setIterator();
    return iterator;
}

EventContainer::EventIterator EventContainer::end() {
    setIterator();
    while(!(iterator.isNull())) {
        ++iterator;
    }
    return iterator;
}
