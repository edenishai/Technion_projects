#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stdbool.h>

template<typename T>
class Iterator {
    Node<T>* node_ptr;
public:
    Iterator();
    Iterator(const Iterator& iterator);
    ~Iterator();
    Iterator& operator=(const Iterator& iterator);
    T& operator*();
    T& operator++();
    bool isNull();
};

template<typename T>
Iterator<T>::Iterator():
    node_ptr(new Node<T>) {
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T>& iterator):
    node_ptr(new Node<T>(iterator.node_ptr->data)) {
}

template<typename T>
Iterator<T>::~Iterator() {
    delete node_ptr;
}

template<typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iterator) {
    Node<T>* temp = new Node<T>(iterator.node_ptr->data);
    delete node_ptr;
    node_ptr = temp;
    return *this;
}

template<typename T>
bool operator==(const Iterator<T>& iterator1, const Iterator<T>& iterator2) {
    if(*iterator1 == *iterator2) {
        return true;
    }
    return false;
}

template<typename T>
bool operator!=(const Iterator<T>& iterator1, const Iterator<T>& iterator2) {
    return !(iterator1 == iterator2);
}

template<typename T>
T& Iterator<T>::operator*() {
    return node_ptr->data;
}

template<typename T>
T& Iterator<T>::operator++() {
    node_ptr = node_ptr->next;
    return node_ptr->data;
}

template<typename T>
bool Iterator<T>::isNull() {
    if(node_ptr == NULL) {
        return true;
    }
    return false;
}

#endif /* ITERATOR_H */