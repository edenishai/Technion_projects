#ifndef UNION_FIND_H
#define UNION_FIND_H

template <class T>
class UFNode {
public:

private:
    UFNode* _parent;
    int size_;
    T* data_;
};

template <class T>
class UnionFind {
public:

private:
    UFNode<T>** elements_;
};

#endif /* UNION_FIND_H */
