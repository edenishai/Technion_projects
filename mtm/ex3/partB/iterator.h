#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stdbool.h>

template<typename T>
class Iterator {
    Node<T>* node_ptr;
public:
    Iterator(const Node<T>* node_ptr = NULL);
    Iterator(const Iterator& iterator);
    ~Iterator();
    Iterator& operator=(const Iterator& iterator);
    bool operator==(const Iterator<T>& iterator) const;
    T& operator*() const;
    T& operator++();
    bool isNull() const;
};

template<typename T>
Iterator<T>::Iterator(const Node<T>* node_ptr):
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
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iterator) {
    node_ptr = iterator.node_ptr;
    Node<T>* node = new Node<T>(iterator.node_ptr);
    delete node_ptr;
    node_ptr = &node;
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
T& Iterator<T>::operator*() const {
    return node_ptr->data;
}

template<typename T>
T& Iterator<T>::operator++() {
    node_ptr = node_ptr->next;
    return node_ptr->data;
}

template<typename T>
bool Iterator<T>::isNull() const {
    if(node_ptr == NULL) {
        return true;
    }
    return false;
}

#endif /* ITERATOR_H */