#include "event_container.h"
#include <stdbool.h>
using mtm::EventContainer;

EventContainer::EventContainer():
    events_list() {
}

EventContainer::EventIterator EventContainer::begin() {
    return this->events_list.getFirst();
}




EventContainer::EventIterator::EventIterator():
    iterator(NULL) {
}

EventContainer::EventIterator::EventIterator(const EventIterator& event_iter) {
    this->iterator = event_iter.iterator;
}

EventIterator& EventContainer::EventIterator::operator=(const EventIterator& event_iter) {

}

/*
EventContainer::EventIterator EventIterator(const EventContainer::EventIterator& iterator):
    iterator(iterator) {
}



EventContainer::EventContainer():
    LinkedList<const BaseEvent&>() {
}



EventContainer::EventIterator EventContainer::end() {
}
*/