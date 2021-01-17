#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::ostream;

template<typename T>
class Node {
    T& data;    //not to change to not const or to pointer
    Node<T>* next;
public:
    Node(const T& data);    //not to change to not const
    Node(const Node& node);
    ~Node() = default;
    Node* getNext() const;
    void setNext(Node* next);
    T& getData();   //not to change to const (related to *iterator)
    Node& operator=(const Node& node);
};

template<typename T>
Node<T>::Node(const T& data):
    data(data), next(NULL) {
}

template<typename T>
Node<T>::Node(const Node<T>& node):
    data(node.data), next(NULL) {
}

template<typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template<typename T>
void Node<T>::setNext(Node<T>* next) {
    this->next = next;
}

template<typename T>
T& Node<T>::getData() {
    return data;
}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& node) {
    T new_data(node.data);
    delete data;
    data = new_data;
    return *this;
}

template<typename T>
ostream& operator<<(ostream& os, const Node<T>& node) {
    return os << node.data << "\n";
}

#endif /* NODE_H */
