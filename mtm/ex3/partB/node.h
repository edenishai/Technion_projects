#ifndef NODE_H
#define NODE_H

#include <ostream>
using std::ostream;

template<typename T>
class Node {
    T data;
    Node<T>* next;
public:
    Node(T& data = NULL);
    Node(const Node& node);
    ~Node();
    friend ostream& operator<<(ostream& os, const Node<T>& node);
};

template<typename T>
Node<T>::Node(T& data):
    data(data), next(new Node<T>) {
}

template<typename T>
Node<T>::Node(const Node<T>& node):
    data(node.data), next(new Node<T>(node.next->data)) {
}

template<typename T>
Node<T>::~Node() {
    delete next;
}

template<typename T>
ostream& operator<<(ostream& os, const Node<T>& node) {
    return os << node.data << "\n";
}

#endif /* NODE_H */