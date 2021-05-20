#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
using namespace std;

template <class T>
class AVLNode {
public:
    AVLNode();
    AVLNode(const T& data): data_(data), left_(NULL), right_(NULL), height_(0) {}
    ~AVLNode() {}
    T& getData() { return data_ ;}
    AVLNode* getLeft() const { return left_; }
    AVLNode* getRight() const { return right_; }
    int getHeight() { return height_; }
    void setLeft(AVLNode* left) { left_ = left; }
    void setRight(AVLNode* right) { right_ = right; }
    void setHeight(int height) { height_ = height; }
    void print() const { cout << data_ << endl; }

private:
    T data_;
    AVLNode* left_;
    AVLNode* right_;
    int height_;
};

template <class T>
class AVLTree {
public:
    AVLTree(): root_(NULL) {}
    ~AVLTree();
    void insert(const T& data);
    void remove(const T& data);
    void clear();
    void display() const;
    T* find(const T& data) const;
    T* findMax() const;
    T* findMin() const;

private:
    AVLNode<T>* root_;

    AVLNode<T>* remove(const T& data, AVLNode<T>* node);
    AVLNode<T>* leftRotate(AVLNode<T>* root);
    AVLNode<T>* rightRotate(AVLNode<T>* root);
    AVLNode<T>* doubleLeftRotate(AVLNode<T>* root);
    AVLNode<T>* doubleRightRotate(AVLNode<T>* root);
    int balanceFactor(AVLNode<T>* root) const;
    void printInOrder(AVLNode<T>* root) const;
    AVLNode<T>* insertNode(const T& data, AVLNode<T>* node);
    void deepRemoveNode(AVLNode<T>* node);
    AVLNode<T>* findMin(AVLNode<T>* root) const;
    AVLNode<T>* findMax(AVLNode<T>* root) const;
    int max(int left, int right) const;
    int height(AVLNode<T>* node) const;
    T* find(AVLNode<T>* root, const T& data) const;
};

template <class T>
AVLTree<T>::~AVLTree() {
    if(root_) {
        deepRemoveNode(root_);
    }
}

template <class T>
void AVLTree<T>::insert(const T& data) {
    root_ = insertNode(data, root_);
}

template <class T>
void AVLTree<T>::remove(const T& data) {
    root_ = remove(data, root_);
}

template <class T>
void AVLTree<T>::clear() {
    if(root_) {
        deepRemoveNode(root_);
    }
    root_ = NULL;
}

template <class T>
void AVLTree<T>::display() const {
    printInOrder(root_);
}

template <class T>
void AVLTree<T>::deepRemoveNode(AVLNode<T>* node) {
    if(node) {
        deepRemoveNode(node->getLeft());
        deepRemoveNode(node->getRight());
        delete node;
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::insertNode(const T& data, AVLNode<T>* node) {
    if(node == NULL) {
        node = new AVLNode<T>(data);
        node->setHeight(0);
        node->setLeft(NULL);
        node->setRight(NULL);
    }
    else if(data < node->getData()) {
        node->setLeft(insertNode(data, node->getLeft()));
        if(height(node->getLeft()) - height(node->getRight()) == 2) {
            if(data < node->getLeft()->getData())
                node = rightRotate(node);
            else
                node = doubleRightRotate(node);
        }
    }
    else if(data > node->getData()) {
        node->setRight(insertNode(data, node->getRight()));
        if(height(node->getRight()) - height(node->getLeft()) == 2) {
            if(data > node->getRight()->getData())
                node = leftRotate(node);
            else
                node = doubleLeftRotate(node);
        }
    }
    node->setHeight(max(height(node->getLeft()), height(node->getRight()))+1);
    return node;
}

template <class T>
void AVLTree<T>::printInOrder(AVLNode<T>* root) const {
    if(root) {
        printInOrder(root->getLeft()); 
        root->print();
        printInOrder(root->getRight());
    }
}

template <class T>
T* AVLTree<T>::find(AVLNode<T>* root, const T& data) const {
    if(root) {
        if(root->getData() == data) {
            return root->getData();
        }
        else if(data < root->getData()) {
            return find(root->getLeft(), data);
        }
        else {
            return find(root->getRight(), data);
        }
    }
    return NULL;
}

template <class T>
T* AVLTree<T>::find(const T& data) const {
    return find(root_, data);
}

template <class T>
int AVLTree<T>::height(AVLNode<T>* node) const {
    return (node == NULL ? -1 : node->getHeight());
}

template <class T>
int AVLTree<T>::balanceFactor(AVLNode<T>* root) const {
    if(!root) {
        return 0;
    }
    return height(root->getLeft()) - height(root->getRight());
}

template <class T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* root) {
    AVLNode<T>* u = root->getRight();
    root->setRight(u->getLeft());
    u->setLeft(root);
    root->setHeight(max(height(root->getLeft()), height(root->getRight()))+1);
    u->setHeight(max(height(root->getRight()), root->getHeight())+1);
    return u;
}

template <class T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* root) {
    AVLNode<T>* u = root->getLeft();
    root->setLeft(u->getRight());
    u->setRight(root);
    root->setHeight(max(height(root->getLeft()), height(root->getRight()))+1);
    u->setHeight(max(height(u->getLeft()), root->getHeight())+1);
    return u;
}

template <class T>
AVLNode<T>* AVLTree<T>::doubleLeftRotate(AVLNode<T>* root) {
    root->setRight(rightRotate(root->getRight()));
    return leftRotate(root);
}

template <class T>
AVLNode<T>* AVLTree<T>::doubleRightRotate(AVLNode<T>* root) {
    root->setLeft(leftRotate(root->getLeft())); 
    return rightRotate(root);
}

template <class T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* root) const {
    if(root == NULL)
        return NULL;
    else if(root->getLeft() == NULL)
        return root;
    else
        return findMin(root->getLeft());
}

template <class T>
AVLNode<T>* AVLTree<T>::findMax(AVLNode<T>* root) const {
    if(root == NULL)
        return NULL;
    else if(root->right == NULL)
        return root;
    else
        return findMax(root->right);
}

template <class T>
AVLNode<T>* AVLTree<T>::remove(const T& data, AVLNode<T>* node) {
    AVLNode<T>* temp;

    if(node == NULL)
        return NULL;
    else if(data < node->getData())
        node->setLeft(remove(data, node->getLeft()));
    else if(data > node->getData())
        node->setRight(remove(data, node->getRight()));
    else if(node->getLeft() && node->getRight()) {
        temp = findMin(node->getRight());
        node->getData() = temp->getData();
        node->setRight(remove(node->getData(), node->getRight()));
    }
    else {
        temp = node;
        if(node->getLeft() == NULL)
            node = node->getRight();
        else if(node->getRight() == NULL)
            node = node->getLeft();
        delete temp;
    }
    if(node == NULL)
        return node;

    node->setHeight(max(height(node->getLeft()), height(node->getRight()))+1);

    if(height(node->getLeft()) - height(node->getRight()) == 2) {
        if(height(node->getLeft()->getLeft()) - height(node->getLeft()->getRight()) == 1)
            return leftRotate(node);
        else
            return doubleLeftRotate(node);   
    }
    else if(height(node->getRight()) - height(node->getLeft()) == 2) {
        if(height(node->getRight()->getRight()) - height(node->getRight()->getLeft()) == 1)
            return rightRotate(node);
        else
            return doubleRightRotate(node);  
    }
    return node;
}

template <class T>
int AVLTree<T>::max(int left, int right) const {
    return (left >= right) ? left : right;
}

template <class T>
T* AVLTree<T>::findMax() const {
    AVLNode<T>* maxNode = findMax(root_);
    return maxNode->getData();
}

template <class T>
T* AVLTree<T>::findMin() const {
    AVLNode<T>* minNode = findMin(root_);
    return minNode->getData();
}

#endif /* AVL_TREE_H */

/*
template <class T>
AVLNode<T>* AVLTree<T>::remove(const T& data, AVLNode<T>* node) {
    AVLNode<T>* temp;

    if(node == NULL)
        return NULL;
    else if(data < node->getData())
        node->setLeft(remove(data, node->getLeft()));
    else if(data > node->getData())
        node->setRight(remove(data, node->getRight()));
    else if(node->getLeft() && node->getRight()) {
        temp = findMin(node->getRight());
        node->getData() = temp->getData();
        node->setRight(remove(node->getData(), node->getRight()));
    }
    else {
        temp = node;
        if(node->getLeft() == NULL)
            node = node->getRight();
        else if(node->getRight() == NULL)
            node = node->getLeft();
        delete temp;
    }
    if(node == NULL)
        return node;

    node->setHeight(max(height(node->getLeft()), height(node->getRight()))+1);

    if(height(node->getLeft()) - height(node->getRight()) == 2) {
        if(height(node->getLeft()->getLeft()) - height(node->getLeft()->getRight()) == 1)
            return leftRotate(node);
        else
            return doubleLeftRotate(node);   
    }
    else if(height(node->getRight()) - height(node->getLeft()) == 2) {
        if(height(node->getRight()->getRight()) - height(node->getRight()->getLeft()) == 1)
            return rightRotate(node);
        else
            return doubleRightRotate(node);  
    }
    return node;
}

*/