#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <stdbool.h>
#include <iostream>
using std::ostream;

template<typename T>
class LinkedList {
    Node<T>* head;
public:
    LinkedList();
    LinkedList(const LinkedList& list);
    int compareData(const T& data1, const T& data2) const;
    T getFirst() const;
    T getNext() const;
    Node<T>* getHead() const;
    bool contains(const T& data) const;
    void insert(const T& data);
    void remove(const T& data);
};

template<typename T>
LinkedList<T>::LinkedList() {
    head = NULL;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    Node<T>* src_iterator = list.head;
    if(!src_iterator) {
        return;
    }
    head = new Node<T>(*(list.head));
    Node<T>* iterator = head;
    src_iterator = src_iterator->getNext();
    while(src_iterator) {
        iterator->setNext(new Node<T>(*src_iterator));
        iterator = iterator->getNext();
        src_iterator = src_iterator->getNext();
    }
}

template<typename T>
int LinkedList<T>::compareData(const T& data1, const T& data2) const {
    if(data1 > data2) {
        return 1;
    }
    else if(data1 < data2) {
        return -1;
    } 
    return 0;
}

template<typename T>
T LinkedList<T>::getFirst() const {
    return head->getData();
}

template<typename T>
T LinkedList<T>::getNext() const {
    Node<T>* temp = head->getNext();
    return temp->getData();
}

template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    Node<T>* iterator = head;
    while(iterator) {
        if(compareData(iterator->getData(), data) == 0) {
            return true;
        }
        iterator = iterator->getNext();
    }
    return false;
}

template<typename T>
Node<T>* LinkedList<T>::getHead() const {
    return head;
}

template<typename T>
void LinkedList<T>::insert(const T& data) {
    Node<T>* temp = new Node<T>(data);
    if(!head) {
        head = temp;
        return;
    }
    Node<T>* iterator = head;
    if(compareData(iterator->getData(), data) > 0) {
        temp->setNext(head);
        head = temp;
        return;
    }
    Node<T>* back_iterator = iterator;
    iterator = iterator->getNext();
    while(iterator) {
        if(compareData(iterator->getData(), data) > 0) {
            temp->setNext(back_iterator->getNext());
            back_iterator->setNext(temp);
            return;
        }
        back_iterator = iterator;
        iterator = iterator->getNext();
    }
    back_iterator->setNext(temp);
}

template<typename T>
void LinkedList<T>::remove(const T& data) {
    Node<T>* iterator = head;
    if(compareData(iterator->getData(), data) == 0) {
        Node<T>* to_delete = head;
        head = head->getNext();
        delete to_delete;
        return;
    }
    Node<T>* back_iterator = iterator;
    iterator = iterator->getNext();
    while(!iterator) {
        if(compareData(iterator->getData(), data) == 0) {
            Node<T>* to_delete = back_iterator->getNext();
            back_iterator->setNext(iterator->getNext());
            delete to_delete;
            return;
        }
        back_iterator = iterator;
        iterator = iterator->getNext();
    }
}

template<typename T>
ostream& operator<<(ostream& os, LinkedList<T>& list) {
    Node<T>* iterator = list.getHead();
    while(iterator) {
        os << iterator->getData();
        os << "\n";
        iterator = iterator->getNext();
    }
    return os;
}

#endif /* LINKED_LIST_H */