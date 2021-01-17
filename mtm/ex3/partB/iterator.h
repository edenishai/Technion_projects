#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stdbool.h>

template<typename T>
class Iterator {
    Node<T>* node_ptr;
public:
    Iterator(Node<T>* node_ptr = NULL);
    Iterator(const Iterator& iterator);
    ~Iterator();
    Iterator& operator=(Node<T>* node_ptr);
    bool operator==(const Iterator<T>& iterator) const;
    T& operator*() const;
    T& operator++();
    void setNext(Node<T>* next);
    Node<T>* getNext();
    bool isNull() const;
};

template<typename T>
Iterator<T>::Iterator(Node<T>* node_ptr):
    node_ptr(node_ptr) {
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T>& iterator):
    node_ptr(iterator.node_ptr) {
}

template<typename T>
Iterator<T>::~Iterator() {
    delete node_ptr;
}

template<typename T>
Iterator<T>& Iterator<T>::operator=(Node<T>* node_ptr) {
    this->node_ptr = node_ptr;
    return *this;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& iterator) const {
    if(this == &iterator) {
        return true;
    }
    return false;
}

template<typename T>
bool operator!=(const Iterator<T>& iterator1, const Iterator<T>& iterator2) {
    return !(iterator1 == iterator2);
}

template<typename T>
T& Iterator<T>::operator*() const { //not to change const (test *iterator)
    return node_ptr->getData();
}

template<typename T>
T& Iterator<T>::operator++() {
    node_ptr = node_ptr->getNext();
    return node_ptr->getData();
}

template<typename T>
void Iterator<T>::setNext(Node<T>* next) {
    node_ptr->setNext(next);
}

template<typename T>
Node<T>* Iterator<T>::getNext() {
    return node_ptr->getNext();
}

template<typename T>
bool Iterator<T>::isNull() const {
    if(node_ptr == NULL) {
        return true;
    }
    return false;
}

#endif /* ITERATOR_H */