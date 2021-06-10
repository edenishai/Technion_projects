#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <iostream>
#include "DynamicArray.h"
#include "agency_type.h"

template<class T>
class UnionFind {
public:
    UnionFind();

    void Makeset(T *element);

    int FindIdentifier(int identifier);

    T &FindElement(int identifier);

    void Union(int n1, int n2);

    void print();

private:
    const int DOESNT_EXIST = -1;
    const int NO_PARENT = -1;
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
void UnionFind<T>::Makeset(T *element)
{

    sizes.add(new int(0));
    parents.add(new int(NO_PARENT));
    elements_.add(element);
    elements_count++;
}


template<class T>
int UnionFind<T>::FindIdentifier(int identifier)
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
    while (to_return==-1 && this->parents[parent] != NO_PARENT) {
        parent = this->parents[parent];
    }
    to_return = parent;

    //Update Route:
    int temp;
    int index =  identifier;
    while (index!= -1 && this->parents[index] != NO_PARENT) {
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
T &UnionFind<T>::FindElement(int identifier)
{
    // if asking for invalid
    if (identifier >= this->elements_count) {
        return -1;
    }

    int parent = this->parents[identifier];
    while (this->parents[parent]) {
        parent = this->parents[parent];
    }
    if (this->elements_[this->parents[identifier]]) {
        return this->elements_[this->parents[identifier]];
    }
    return nullptr;
}

template<class T>
void UnionFind<T>::Union(int n1, int n2)
{
    int root1 = this->getRootParent(n1);
    int root2 = this->getRootParent(n2);

    int n1_size = this->sizes[root1];
    int n2_size = this->sizes[root2];

    if (n1_size >= n2_size) {
        this->parents[root2] = n1;
        this->sizes[root2] = 0;
        this->sizes[root1] += (n2_size + 1);
    } else {
        this->parents[root1] = n2;
        this->sizes[root1] = 0;
        this->sizes[root2] += (n1_size + 1);
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

#endif /* UNION_FIND_H */
