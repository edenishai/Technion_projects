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
    int compareData(const T& data) const;
    void setIterator();
    T& getFirst() const;
    T& getNext() const;
    bool contains(const T& data) const;
    void insert(const T& data);
    void remove(const T& data);
};

//to add null check in every func
template<typename T>
LinkedList<T>::LinkedList() {
    head = NULL;
    iterator.node_ptr = NULL;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    Iterator<T> src_iterator(list.head);
    Node<T> node(src_iterator.node_ptr);
    head = &node;
    setIterator();
    ++src_iterator;
    while(!src_iterator.isNull()) {
        Node<T> node(src_iterator.node_ptr->data);
        iterator.node_ptr->next = &node;
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
int LinkedList<T>::compareData(const T& data) const {
    if(iterator->data > data) {
        return 1;
    }
    else if(iterator->data < data) {
        return -1;
    } 
    return 0;
}

template<typename T>
void LinkedList<T>::setIterator() {
    iterator.node_ptr = head;
}

template<typename T>
T& LinkedList<T>::getFirst() const {
    iterator = head;
    return iterator->data;
}

template<typename T>
T& LinkedList<T>::getNext() const {
    iterator = iterator->next;
    return iterator->data;
}

template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    iterator = head;
    while(iterator.isNull()) {
        if(compareData(data) == 0) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

template<typename T>    //fixed
void LinkedList<T>::insert(const T& data) {
    Node<T>* temp = new Node<T>(data);
    if(!head) {
        head = temp;
        head->next = NULL;
        return;
    }
    setIterator();
    if(compareData(data) > 0) {
        temp->next = head;
        head = temp;
        return;
    }
    Iterator<T> back_iterator = iterator;
    ++iterator;
    while(!iterator.isNull()) {
        if(compareData(data) > 0) {
            temp->next = iterator.node_ptr;
            back_iterator.node_ptr->next = temp;
            return;
        }
        ++back_iterator;
        ++iterator;
    }
    temp->next = NULL;
    back_iterator.node_ptr->next = temp;
}

template<typename T>
void LinkedList<T>::remove(const T& data) {
    iterator = head;
    if(compareData(data) == 0) {
        Node<T>* to_delete = head;
        head = head->next;
        to_delete->~Node();
        return;
    }
    Node<T>* back_iterator = head;
    iterator = iterator->next;
    while(iterator) {
        if(compareData(data) == 0) {
            Node<T>* to_delete = iterator;
            back_iterator->next = iterator->next;
            to_delete->~Node();
            return;
        }
        back_iterator = iterator;
        iterator = iterator->next;
    }
}

template<typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& list) {
    list.iterator = list.head;
    while(list.iterator) {
        os << list.iterator->data;
    }
    return os;
}

#endif /* LINKED_LIST_H */