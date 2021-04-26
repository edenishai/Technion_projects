#ifndef NODE_H
#define NODE_H

#include <iostream>

namespace mtm{

    template<typename T>
    class Node 
    {
    
        T data;
        Node<T>* next;
    
    public:
    
        Node(const T& data);
        Node(const Node& node = NULL);

        /**
         * Returns the data of the node
         */
        T getData() const;

        /**
         * Returns a pointer to the next node(the one which the pointer next refers to)
         */
        Node* getNext() const;

        /**
         * Updates the pointer next of the class
         */
        void setNext(Node* next);

        Node& operator=(const Node& node);
    
    };

    template<typename T>
    Node<T>::Node(const T& data):
        data(data), next(NULL) { }

    template<typename T>
    Node<T>::Node(const Node<T>& node):
        data(node.data), next(NULL) { }

    template<typename T>
    T Node<T>::getData() const 
    {
        return data;
    }

    template<typename T>
    Node<T>* Node<T>::getNext() const 
    {
        return next;
    }

    template<typename T>
    void Node<T>::setNext(Node<T>* next) 
    {
        this->next = next;
    }

    template<typename T>
    Node<T>& Node<T>::operator=(const Node<T>& node) 
    {
        T new_data(node.data);
        delete data;
        data = new_data;
        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Node<T>& node) 
    {
        return os << node.data << "\n";
    }

}

#endif /* NODE_H */