#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include "iterator.h"
#include <stdbool.h>
#include <ostream>
using std::ostream;

template<typename T>
class List {
    Node<T>* head;
protected:
    Iterator<T> iterator;
public:
    List();
    ~List() = default;
    List(const List& list);
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
List<T>::List():
    head(NULL),
    iterator(NULL) {
}

template<typename T>
List<T>::List(const List<T>& list) {
    list.setIterator();
    Node<T>* node(*(list.iterator));
    head = node;
    setIterator();
    ++(list.iterator);
    ++iterator;
    while(!list.iterator.isNull()) {
        Node<T> node(*(list.iterator));
        iterator->next = node;
        ++iterator;
        ++(list.iterator);
    }
}

template<typename T>
int List<T>::compareData(const T& data) const {
    if(iterator->data > data) {
        return 1;
    }
    else if(iterator->data < data) {
        return -1;
    } 
    return 0;
}

template<typename T>
void List<T>::setIterator() {
    iterator.node_ptr = head;
}

template<typename T>
T& List<T>::getFirst() const {
    iterator = head;
    return iterator->data;
}

template<typename T>
T& List<T>::getNext() const {
    iterator = iterator->next;
    return iterator->data;
}

template<typename T>
bool List<T>::contains(const T& data) const {
    iterator = head;
    while(iterator) {   // operator??
        if(compareData(data) == 0) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

template<typename T>
void List<T>::insert(const T& data) {
    Node<T> new_node(data);
    if(head == NULL) {   // operator??
        head = &new_node;
        return;
    }
    iterator = head;
    if(compareData(data) > 0) {
        new_node.next = head;
        head = &new_node;
        return;
    }
    Node<T>* back_iterator = head;
    iterator = iterator->next;
    while(iterator) {
        if(compareData(data) > 0) {
            new_node.next = iterator;
            back_iterator->next = new_node;
            return;
        }
        back_iterator = iterator;
        iterator = iterator->next;
    }
    back_iterator->next = new_node;
}

template<typename T>
void List<T>::remove(const T& data) {
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
ostream& operator<<(ostream& os, const List<T>& list) {
    list.iterator = list.head;
    while(list.iterator) {
        os << list.iterator->data;
    }
    return os;
}

#endif /* LINKED_LIST_H */