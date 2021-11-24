#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cmath>

using namespace std;

template<class T>
class AVLNode {
public:
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode() :
            left(nullptr), right(nullptr), height(0), data_(nullptr)
    {}

    explicit AVLNode(T *data) : data_(data), left(nullptr), right(nullptr), height(0)
    {}

    ~AVLNode()
    {
        delete data_;
    }

    T *getData()
    { return data_; }

    void print() const
    { T a = data_; }


private:
    T *data_;

};


template<class T>
class AVLTree {
public:
    AVLTree() : root_(nullptr), current_size_(0), last_left_(nullptr), last_right_(nullptr)
    {}

    ~AVLTree();

    void insert(T *data);

    void buildOrdered(T **data_arr, int range);

    void remove(T *data);

    void clear();

    void display() const;

    T *find(const T *data) const;

    T *findMax() const;

    T *findMin() const;

    int currentSize() const;

    T *getMostRight();

    int getInOrder(T *array, int size) const;

    bool checkTree();


private:

    AVLNode<T> *root_;

    int current_size_;

    AVLNode<T> *last_right_;

    AVLNode<T> *last_left_;

    void getInOrder(AVLNode<T> *root, T *array, int size, int *index) const;

    AVLNode<T> *remove_aux(T *data, AVLNode<T> *node);

    AVLNode<T> *LL_Rotate(AVLNode<T> *node);

    AVLNode<T> *RR_Rotate(AVLNode<T> *node);

    AVLNode<T> *LR_Rotate(AVLNode<T> *node);

    AVLNode<T> *RL_Rotate(AVLNode<T> *node);


    int balanceFactor(AVLNode<T> *node) const;

//todo: used for debugging
    void printInOrder(AVLNode<T> *root) const;

    AVLNode<T> *insert_aux(T *data, AVLNode<T> *node);

    void deepRemoveNode(AVLNode<T> *node);

    AVLNode<T> *findMin_aux(AVLNode<T> *node) const;

    AVLNode<T> *findMax_aux(AVLNode<T> *node) const;

    int height(AVLNode<T> *node) const;

    T *find_aux(AVLNode<T> *root, const T *data) const;

    AVLNode<T> *buildOrdered_aux(T **data, int start, int end, int height);

    bool checkTree_aux(AVLNode<T> *node, int h);
};

template<class T>
AVLTree<T>::~AVLTree()
{
    this->clear();
}

template<class T>
void AVLTree<T>::insert(T *data)
{
    if (find(data))
        return;
    root_ = insert_aux(data, root_);
    ++current_size_;
    this->last_right_ = findMax_aux(root_);
    this->last_left_ = findMin_aux(root_);

}

template<class T>
void AVLTree<T>::remove(T *data)
{
    if (find(data)) {
        --current_size_;
        root_ = remove_aux(data, root_);
        last_right_ = findMax_aux(root_);
        last_left_ = findMin_aux(root_);
    }
}

template<class T>
void AVLTree<T>::clear()
{
    //if (!checkTree()) {
    //    cout << "NOOO!\n";
    //}
    if (root_) {
        deepRemoveNode(root_);
    }
}

template<class T>
void AVLTree<T>::display() const
{
    printInOrder(root_);
}

template<class T>
void AVLTree<T>::deepRemoveNode(AVLNode<T> *node)
{
    if (node) {
        deepRemoveNode(node->left);
        deepRemoveNode(node->right);
        delete node;
    }
}

template<class T>
AVLNode<T> *AVLTree<T>::insert_aux(T *data, AVLNode<T> *node)
{
    // stop condition
    if (node == NULL) {
        node = new AVLNode<T>(data);
        node->height = 0;
        node->left = NULL;
        node->right = NULL;

    } else if (*data < *(node->getData())) {
        node->left = insert_aux(data, node->left);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left) == -1)
                node = LR_Rotate(node);
            else
                node = LL_Rotate(node);
        }
    } else if (*data > *(node->getData())) {
        node->right = insert_aux(data, node->right);
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right) == 1)
                node = RL_Rotate(node);
            else
                node = RR_Rotate(node);
        }
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

template<class T>
void AVLTree<T>::printInOrder(AVLNode<T> *root) const
{
    if (root) {
        printInOrder(root->left);
        root->print();
        printInOrder(root->right);
    }
}

template<class T>
T *AVLTree<T>::find_aux(AVLNode<T> *root, const T *data) const
{
    if (root) {
        if (*(root->getData()) == *data) {
            return root->getData();
        } else if (*data < *(root->getData())) {
            return find_aux(root->left, data);
        } else {
            return find_aux(root->right, data);
        }
    }
    return nullptr;
}

template<class T>
T *AVLTree<T>::find(const T *data) const
{
    T *d = find_aux(root_, data);
    return d;
}

template<class T>
int AVLTree<T>::height(AVLNode<T> *node) const
{
    return (node == NULL ? -1 : node->height);
}

template<class T>
int AVLTree<T>::balanceFactor(AVLNode<T> *node) const
{
    if (!node) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

template<class T>
AVLNode<T> *AVLTree<T>::LL_Rotate(AVLNode<T> *node)
{
    AVLNode<T> *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

template<class T>
AVLNode<T> *AVLTree<T>::RR_Rotate(AVLNode<T> *node)
{
    AVLNode<T> *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

template<class T>
AVLNode<T> *AVLTree<T>::RL_Rotate(AVLNode<T> *node)
{
    node->right = LL_Rotate(node->right);
    return RR_Rotate(node);
}

template<class T>
AVLNode<T> *AVLTree<T>::LR_Rotate(AVLNode<T> *node)
{
    node->left = RR_Rotate(node->left);
    return LL_Rotate(node);
}

template<class T>
AVLNode<T> *AVLTree<T>::findMin_aux(AVLNode<T> *node) const
{
    if (node == NULL)
        return NULL;
    else if (node->left == NULL)
        return node;
    else
        return findMin_aux(node->left);
}

template<class T>
AVLNode<T> *AVLTree<T>::findMax_aux(AVLNode<T> *node) const
{
    if (node == NULL)
        return NULL;
    else if (node->right == NULL)
        return node;
    else
        return findMax_aux(node->right);
}

template<class T>
AVLNode<T> *AVLTree<T>::remove_aux(T *data, AVLNode<T> *node)
{
    AVLNode<T> *temp;

    if (node == NULL)
        return NULL;
    else if (*data < *(node->getData()))
        node->left = remove_aux(data, node->left);
    else if (*data > *(node->getData()))
        node->right = remove_aux(data, node->right);
        //after finding
        //if 2 sons
    else if (node->left && node->right) {
        temp = findMin_aux(node->right);
        *(node->getData()) = *(temp->getData());
        (*(temp->getData())).flatDelete();
        node->right = remove_aux(node->getData(), node->right);
    }
        //if one son or less
    else {
        temp = node;
        if (node->left == NULL)
            node = node->right;
        else if (node->right == NULL)
            node = node->left;
        delete temp;
    }
    if (node == NULL)
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;

    //balancing
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) == -1)
            return LR_Rotate(node);
        else
            return LL_Rotate(node);
    } else if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) == 1)
            return RL_Rotate(node);
        else
            return RR_Rotate(node);
    }
    return node;
}

template<class T>
T *AVLTree<T>::findMax() const
{
    AVLNode<T> *maxNode = findMax_aux(root_);
    return maxNode->getData();
}

template<class T>
T *AVLTree<T>::findMin() const
{
    AVLNode<T> *minNode = findMin_aux(root_);
    return minNode->getData();
}

template<class T>
int AVLTree<T>::currentSize() const
{
    return current_size_;
}

template<class T>
T *AVLTree<T>::getMostRight()
{
    return this->last_right_->getData();
}

template<class T>
int AVLTree<T>::getInOrder(T *array, int size) const
{
    size = min(size, this->current_size_);
    int index = 0;
    getInOrder(root_, array, size, &index);
    return size;
}

template<class T>
void AVLTree<T>::getInOrder(AVLNode<T> *root, T *array, int size, int *index) const
{
    if (root == nullptr || *index == size)
        return;
    getInOrder(root->left, array, size, index);
    array[*index] = *(root->getData());
    (*index)++;
    getInOrder(root->right, array, size, index);
}

template<class T>
void AVLTree<T>::buildOrdered(T **data, int range)
{
    int height = log(range) / log(2);
    this->root_ = buildOrdered_aux(data, 0, range - 1, height);
    this->current_size_ = range;
}

template<class T>
AVLNode<T> *AVLTree<T>::buildOrdered_aux(T **data, int start, int end, int height)
{
    if (start > end) { return nullptr; }

    int middle = (start + end) / 2;
    T *new_data = data[middle];
    AVLNode<T> *root = new AVLNode<T>(new_data);
    root->height = height;

    root->left = buildOrdered_aux(data, start, middle - 1, height - 1);
    root->right = buildOrdered_aux(data, middle + 1, end, height - 1);

    return root;
}

template<class T>
bool AVLTree<T>::checkTree()
{
    if (this->current_size_ == 0) {
        return root_ == nullptr;
    }
    int height = log(current_size_) / log(2);
    return checkTree_aux(root_, height);
}

template<class T>
bool AVLTree<T>::checkTree_aux(AVLNode<T> *node, int h)
{
    if (node == nullptr) {
        return true;
    }
    if (h == 0) {
        if (node->right) return false;
        if (node->left) return false;
        return true;
    }
    //h>0
    return checkTree_aux(node->right, h - 1) && checkTree_aux(node->left, h - 1);

}


#endif /* AVL_TREE_H */
