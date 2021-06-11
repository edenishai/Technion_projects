#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "DynamicArray.h"
#include "agency_type.h"

template<class T>
class UFNode {
public:

private:
    UFNode *parent_;
    int size_;
    T *data_;
};

template<class T>
class UnionFind {
public:
    UnionFind();

    void Makeset(T *element);

    int FindIdentifier(int identifier);

    T &FindElement(int identifier);

    void Union(int n1, int n2);


private:
    const int DOESNT_EXIST = -1;
    int elements_count;
    DynamicArray<T> elements_;
    DynamicArray<int> sizes;
    DynamicArray<int> parents;
};

template<class T>
UnionFind<T>::UnionFind()
{
}


template<class T>
void UnionFind<T>::Makeset(T *element)
{

    sizes.add(new int(0));
    parents.add(new int(DOESNT_EXIST));
    elements_.add(element);
    elements_count++;
}


template<class T>
int UnionFind<T>::FindIdentifier(int identifier)
{
    int parent = this->parents[identifier];
    while (this->parents[parent]) {
        parent = this->parents[parent];
    }
    return parent;
}

template<class T>
T &UnionFind<T>::FindElement(int identifier)
{
    int parent = this->parents[identifier];
    while (this->parents[parent]) {
        parent = this->parents[parent];
    }
    if(this->elements_[this->parents[identifier]])
    {
        return this->elements_[this->parents[identifier]];
    }
    return nullptr;
}

template<class T>
void UnionFind<T>::Union(int n1, int n2)
{
    if (this->sizes[n1] > this->sizes[n2]) {
        this->parents[n2] = n1;
        this->sizes[n1] = this->sizes[n1] + 1;
    } else {
        this->parents[n1] = n2;
        this->sizes[n2] = this->sizes[n2] + 1;
    }
}



#endif /* UNION_FIND_H */
