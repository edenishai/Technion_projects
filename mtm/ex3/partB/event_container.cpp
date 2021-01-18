#include "event_container.h"
#include <stdbool.h>
using mtm::EventContainer;


EventContainer::EventContainer():
    events_list() {
}

EventContainer::EventIterator EventContainer::begin() {
    EventIterator event_iter;
    event_iter.iterator = this->events_list.getHead();
    return event_iter;
}

EventContainer::EventIterator EventContainer::end() {
    EventIterator event_iter;
    while(event_iter.iterator) {
        ++event_iter;
    }
    return event_iter;
}

EventContainer::EventIterator EventContainer::getNext() {
    EventIterator event_iter;
    ++event_iter;
    return event_iter;
}

/**************************************************************/

EventContainer::EventIterator::EventIterator():
    iterator(NULL) {
}

EventContainer::EventIterator::EventIterator(const EventIterator& event_iter) {
    this->iterator = event_iter.iterator;
}

EventContainer::EventIterator::EventIterator(Node<BaseEvent&>* node):
    iterator(node) {
}

BaseEvent& EventContainer::EventIterator::operator*() const {
    return iterator->getData();
}

EventContainer::EventIterator& EventContainer::EventIterator::operator=(const EventIterator& event_iter) {
    this->iterator = event_iter.iterator;
    return *this;
}

EventContainer::EventIterator& EventContainer::EventIterator::operator++() {
    iterator = iterator->getNext();
    return *this;

}

bool EventContainer::EventIterator::operator==(const EventIterator& event_iter) const {
    if(iterator->getData() == event_iter.iterator->getData()) {
        return true;
    }
    return false;
}

bool EventContainer::EventIterator::operator!=(const EventIterator& event_iter) const {
    return !(*this == event_iter);
}