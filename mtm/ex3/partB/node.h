#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::ostream;

template<typename T>
class Node {
    T data;
    Node<T>* next;
public:
    Node(const T& data);
    Node(const Node& node);
    ~Node() = default;
    Node* getNext();
    Node& operator=(const Node& node);
    //friend ostream& operator<<(ostream& os, const Node& node);
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
Node<T>* Node<T>::getNext() {
    return next;
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
