#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include "iterator.h"
#include <stdbool.h>
#include <iostream>
using std::ostream;

template<typename T>
class LinkedList {
    Node<T>* head;
protected:
    Iterator<T> iterator;
public:
    LinkedList();
    LinkedList(const LinkedList& list);
    ~LinkedList();
    int compareData(T const &data) const;
    void setIterator();
    const T& getFirst();
    const T& getNext();
    bool contains(T const &data);
    void insert(const T& data); //not to change const
    void remove(const T& data);
};

//to add null check in every func
template<typename T>
LinkedList<T>::LinkedList() {
    head = NULL;
    iterator = NULL;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    Iterator<T> src_iterator(list.head);
    head = new Node<T>(*(list.head));
    iterator = head;
    ++src_iterator;
    while(!src_iterator.isNull()) {
        Node<T> next(*src_iterator);
        iterator.setNext(&next);
        ++iterator;
        ++src_iterator;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while(head) {
        Node<T>* to_delete = head;
        head = head->getNext();
        delete to_delete;
    }
}

template<typename T>
int LinkedList<T>::compareData(T const &data) const {
    if(*iterator > data) {
        return 1;
    }
    else if(*iterator < data) {
        return -1;
    } 
    return 0;
}

template<typename T>
void LinkedList<T>::setIterator() {
    iterator = head;
}

template<typename T>
const T& LinkedList<T>::getFirst() {
    iterator = head;
    return *iterator;
}

template<typename T>
const T& LinkedList<T>::getNext() {
    ++iterator;
    return *iterator;
}

template<typename T>
bool LinkedList<T>::contains(T const &data) {
    iterator = head;
    while(!iterator.isNull()) {
        if(compareData(data) == 0) {
            return true;
        }
        ++iterator;
    }
    return false;
}

template<typename T>
void LinkedList<T>::insert(const T& data) {
    Node<T> temp(data);
    if(!head) {
        head = &temp;
        return;
    }
    iterator = head;
    if(compareData(data) > 0) {
        temp.setNext(head);
        head = &temp;
        return;
    }
    Iterator<T> back_iterator = iterator;
    ++iterator;
    while(!iterator.isNull()) {
        if(compareData(data) > 0) {
            temp.setNext(back_iterator.getNext());
            back_iterator.setNext(&temp);
            return;
        }
        ++back_iterator;
        ++iterator;
    }
    back_iterator.setNext(&temp);
}

template<typename T>
void LinkedList<T>::remove(const T& data) {
    iterator = head;
    if(compareData(data) == 0) {
        Node<T>* to_delete = head;
        head = head->getNext();
        delete to_delete;
        return;
    }
    Iterator<T> back_iterator = head;
    iterator = head;
    ++iterator;
    while(!iterator.isNull()) {
        if(compareData(data) == 0) {
            Node<T>* to_delete = back_iterator.getNext();
            back_iterator.setNext(iterator.getNext());
            delete to_delete;
            return;
        }
        ++back_iterator;
        ++iterator;
    }
}

template<typename T>
ostream& operator<<(ostream& os, LinkedList<T>& list) {
    os << list.getFirst();
    while(list.getNext()) {
        os << list.getNext();
    }
    return os;
}

#endif /* LINKED_LIST_H */