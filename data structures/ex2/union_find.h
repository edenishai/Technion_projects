#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <iostream>
#include "Dynamic_Array.h"
#include "Agency.h"

template<class T>
class UnionFind {
public:
    UnionFind();

    void makeSet(T *element);

    int findIdentifier(int identifier);

    T &findElement(int identifier);

    template<class Unite>
    void Union(int n1, int n2, Unite unite);

    void print();

    void printElements();


    const int DOESNT_EXIST = -1;

    const int NO_PARENT = -1;


private:
    int elements_count;
    DynamicArray<T> elements_;
    DynamicArray<int> sizes;
    DynamicArray<int> parents;

    int getRootParent(int identifier);

};

template<class T>
UnionFind<T>::UnionFind()
{
    elements_count = 0;
}

template<class T>
void UnionFind<T>::makeSet(T *element)
{

    sizes.add(new int(0));
    parents.add(new int(NO_PARENT));
    elements_.add(element);
    elements_count++;
}


template<class T>
int UnionFind<T>::findIdentifier(int identifier)
{
    // if invalid request
    if (identifier >= this->elements_count) {
        return DOESNT_EXIST;
    }
    //Find Parent:
    int parent = this->parents[identifier];
    int to_return = -1;
    if (parent == NO_PARENT) {    // if already root
        to_return = identifier;
    }
    while (to_return == -1 && this->parents[parent] != NO_PARENT) {
        parent = this->parents[parent];
    }
    to_return = parent;

    //Update Route:
    int temp;
    int index = identifier;
    while (index != -1 && this->parents[index] != NO_PARENT) {
        temp = this->parents[index];
        this->parents[index] = to_return;
        index = temp;
    }

    // Done
    return to_return;
}

template<class T>
int UnionFind<T>::getRootParent(int identifier)
{
    // if invalid request
    if (identifier >= this->elements_count) {
        return DOESNT_EXIST;
    }
    //Find Parent:
    int parent = this->parents[identifier];
    if (parent == NO_PARENT) {    // if already root
        return identifier;
    }
    while (this->parents[parent] != NO_PARENT) {
        parent = this->parents[parent];
    }

    return parent;
}

template<class T>
T &UnionFind<T>::findElement(int identifier)
{
    //Find Parent:
    int parent = this->parents[identifier];
    int to_return_index = -1;
    if (parent == NO_PARENT) {    // if already root
        to_return_index = identifier;
    }
    while (to_return_index == -1 && this->parents[parent] != NO_PARENT) {
        parent = this->parents[parent];
    }
    to_return_index = parent;
    T &to_return = this->elements_[parent];

    //Update Route:
    int temp;
    int index = identifier;
    while (index != -1 && this->parents[index] != NO_PARENT) {
        temp = this->parents[index];
        this->parents[index] = to_return_index;
        index = temp;
    }

    // Done
    return to_return;
}

template<class T>
template<class Unite>
void UnionFind<T>::Union(int n1, int n2, Unite unite)
{
    if (n1 == n2) {
        return;
    }

    int root1 = this->getRootParent(n1);
    int root2 = this->getRootParent(n2);

    int n1_size = this->sizes[root1];
    int n2_size = this->sizes[root2];

    T &element1 = this->elements_[root1];
    T &element2 = this->elements_[root2];

    T *new_element = unite(element1, element2);//todo: add unite


    if (n1_size >= n2_size) {
        this->parents[root2] = n1; //make n1 new root
        this->sizes[root2] = 0; // zero old root size
        this->sizes[root1] += (n2_size + 1); //update new root size
        this->elements_.replaceAt(root1,new_element);//update root contains united element
    } else {
        this->parents[root1] = n2; //make n2 new root
        this->sizes[root1] = 0;// zero old root size
        this->sizes[root2] += (n1_size + 1);//update new root size
        this->elements_.replaceAt(root2,new_element);//update root contains united element
    }
}

template<class T>
void UnionFind<T>::print()
{
    for (int i = 0; i < elements_count; ++i) {
        std::cout << "   " << sizes[i];
    }
    std::cout << "\n";
    for (int k = 0; k < elements_count; ++k) {
        if (parents[k] >= 0)
            std::cout << "   " << parents[k];
        else
            std::cout << "  " << parents[k];

    }
    std::cout << "\n";
    for (int j = 0; j < elements_count; ++j) {
        std::cout << "   " << j;
    }
    std::cout << "\n";
}

template<class T>
void UnionFind<T>::printElements()
{
    for (int i = 0; i < elements_count; ++i) {
        std::cout << "  " << &elements_[i];
    }
    std::cout << "\n";
    for (int j = 0; j < elements_count; ++j) {
        std::cout << "            " << j;
    }
    std::cout << "\n";
}

#endif /* UNION_FIND_H */
