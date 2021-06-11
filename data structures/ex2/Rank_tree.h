#ifndef RANK_TREE_H
#define RANK_TREE_H

#include <iostream>
#include <cmath>

using namespace std;

template <class T, class S>
class AVLNode {
public:
    AVLNode *parent_;
    AVLNode *left_;
    AVLNode *right_;
    int height_;
    int rank_;

    AVLNode() :
        parent_(nullptr), left_(nullptr), right_(nullptr), height_(0), rank_(1)
    {}

    explicit AVLNode(T data) :
        parent_(nullptr), left_(nullptr), right_(nullptr), height_(0), rank_(1), data_(data)
    {}

    ~AVLNode() = default;

    T *getData()
    { return data_; }

    void print() const
    { T a = data_; }


private:
    T key_;
    S data_;
};


template <class T, class S>
class RankTree {
public:
    RankTree() : root_(nullptr), currentSize_(0), min_(nullptr), max_(nullptr)
    {}

    ~RankTree();

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

    AVLNode<T, S> *root_;

    AVLNode<T, S> *max_;

    AVLNode<T, S> *min_;

    int currentSize_;

    void getInOrder(AVLNode<T, S> *root, T *array, int size, int *index) const;

    AVLNode<T, S> *remove_aux(T *data, AVLNode<T, S> *node);

    AVLNode<T, S> *LL_Rotate(AVLNode<T, S> *node);

    AVLNode<T, S> *RR_Rotate(AVLNode<T, S> *node);

    AVLNode<T, S> *LR_Rotate(AVLNode<T, S> *node);

    AVLNode<T, S> *RL_Rotate(AVLNode<T, S> *node);

    int balanceFactor(AVLNode<T, S> *node) const;

    void rankUpdate(AVLNode<T, S> *node);

    int rankOfChild(AVLNode<T, S> *child) const;

    void printInOrder(AVLNode<T, S> *root) const;

    AVLNode<T, S> *insert_aux(T *data, AVLNode<T, S> *node);

    void deepRemoveNode(AVLNode<T, S> *node);

    AVLNode<T, S> *findMin_aux(AVLNode<T, S> *node) const;

    AVLNode<T, S> *findMax_aux(AVLNode<T, S> *node) const;

    int height(AVLNode<T, S> *node) const;

    T *find_aux(AVLNode<T, S> *root, const T *data) const;

    AVLNode<T, S> *buildOrdered_aux(T **data, int start, int end, int height);

    bool checkTree_aux(AVLNode<T, S> *node, int h);
};

template<class T, class S>
RankTree<T, S>::~RankTree()
{
    this->clear();
}

template<class T, class S>
void RankTree<T, S>::insert(T *data)
{
    if (find(data))
        return;
    root_ = insert_aux(data, root_);
    ++currentSize_;
    this->max_ = findMax_aux(root_);
    this->min_ = findMin_aux(root_);

}

template<class T, class S>
void RankTree<T, S>::remove(T *data)
{
    if (find(data)) {
        --currentSize_;
        root_ = remove_aux(data, root_);
        max_ = findMax_aux(root_);
        min_ = findMin_aux(root_);
    }
}

template<class T, class S>
void RankTree<T, S>::clear()
{
    if (root_) {
        deepRemoveNode(root_);
    }
}

template<class T, class S>
void RankTree<T, S>::display() const
{
    printInOrder(root_);
}

template<class T, class S>
void RankTree<T, S>::deepRemoveNode(AVLNode<T, S> *node)
{
    if (node) {
        deepRemoveNode(node->left_);
        deepRemoveNode(node->right_);
        delete node;
    }
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::insert_aux(T *data, AVLNode<T, S> *node)
{
    // stop condition
    if (node == NULL) {
        node = new AVLNode<T, S>(data);
        node->height_ = 0;
        node->left_ = NULL;
        node->right_ = NULL;

    } else if (*data < *(node->getData())) {
        node->left_ = insert_aux(data, node->left_);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left_) == -1)
                node = LR_Rotate(node);
            else
                node = LL_Rotate(node);
        }
    } else if (*data > *(node->getData())) {
        node->right_ = insert_aux(data, node->right_);
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right_) == 1)
                node = RL_Rotate(node);
            else
                node = RR_Rotate(node);
        }
    }
    node->height_ = max(height_(node->left_), height_(node->right_)) + 1;
    return node;
}

template<class T, class S>
void RankTree<T, S>::printInOrder(AVLNode<T, S> *root) const
{
    if (root) {
        printInOrder(root->left_);
        root->print();
        printInOrder(root->right_);
    }
}

template<class T, class S>
T *RankTree<T, S>::find_aux(AVLNode<T, S> *root, const T *data) const
{
    if (root) {
        if (*(root->getData()) == *data) {
            return root->getData();
        } else if (*data < *(root->getData())) {
            return find_aux(root->left_, data);
        } else {
            return find_aux(root->right_, data);
        }
    }
    return nullptr;
}

template<class T, class S>
T *RankTree<T, S>::find(const T *data) const
{
    T *d = find_aux(root_, data);
    return d;
}

template<class T, class S>
int RankTree<T, S>::height(AVLNode<T, S> *node) const
{
    return (node == NULL ? -1 : node->height_);
}

template<class T, class S>
int RankTree<T, S>::balanceFactor(AVLNode<T, S> *node) const
{
    if (!node) {
        return 0;
    }
    return height_(node->left_) - height_(node->right_);
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::LL_Rotate(AVLNode<T, S> *node)
{
    AVLNode<T, S> *temp = node->left_;
    temp->parent_ = node->parent_;
    node->left_ = temp->right_;
    if (node->parent_->right_ == node){
        node->parent_->right_ = temp;
    }
    else{
        assert(node->parent_->left_ == node);
        node->parent_->left_ = temp;
    }
    node->parent_ = temp;
    if(temp->right_ != nullptr){
        temp->right_->parent_ = node;
    }
    temp->right_ = node;
    node->height_ = max(height(node->left_), height(node->right_)) + 1;
    temp->height_ = max(height(temp->left_), height(temp->right_)) + 1;
    rankUpdate(node);
    rankUpdate(temp);
    return temp;
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::RR_Rotate(AVLNode<T, S> *node)
{
    AVLNode<T, S> *temp = node->right_;
    temp->parent_ = node->parent_;
    node->right_ = temp->left_;
    if (node->parent_->right_ == node){
        node->parent_->right_ = temp;
    }
    else{
        assert(node->parent_->left_ == node);
        node->parent_->left_ = temp;
    }
    node->parent_ = temp;
    if(temp->left_ != nullptr){
        temp->left_->parent_ = node;
    }
    temp->left_ = node;
    node->height_ = max(height(node->left_), height(node->right_)) + 1;
    temp->height_ = max(height(temp->left_), height(temp->right_)) + 1;
    rankUpdate(node);
    rankUpdate(temp);
    return temp;
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::RL_Rotate(AVLNode<T, S> *node)
{
    node->right_ = LL_Rotate(node->right_);
    return RR_Rotate(node);
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::LR_Rotate(AVLNode<T, S> *node)
{
    node->left_ = RR_Rotate(node->left_);
    return LL_Rotate(node);
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::findMin_aux(AVLNode<T, S> *node) const
{
    if (node == NULL)
        return NULL;
    else if (node->left_ == NULL)
        return node;
    else
        return findMin_aux(node->left_);
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::findMax_aux(AVLNode<T, S> *node) const
{
    if (node == NULL)
        return NULL;
    else if (node->right_ == NULL)
        return node;
    else
        return findMax_aux(node->right_);
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::remove_aux(T *data, AVLNode<T, S> *node)
{
    AVLNode<T, S> *temp;

    if (node == NULL)
        return NULL;
    else if (*data < *(node->getData()))
        node->left_ = remove_aux(data, node->left_);
    else if (*data > *(node->getData()))
        node->right_ = remove_aux(data, node->right_);
        //after finding
        //if 2 sons
    else if (node->left_ && node->right_) {
        temp = findMin_aux(node->right_);
        *(node->getData()) = *(temp->getData());
        (*(temp->getData())).flatDelete();
        node->right_ = remove_aux(node->getData(), node->right_);
    }
        //if one son or less
    else {
        temp = node;
        if (node->left_ == NULL)
            node = node->right_;
        else if (node->right_ == NULL)
            node = node->left_;
        delete temp;
    }
    if (node == NULL)
        return node;

    node->height_ = max(height(node->left_), height(node->right_)) + 1;

    //balancing
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left_) == -1)
            return LR_Rotate(node);
        else
            return LL_Rotate(node);
    } else if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right_) == 1)
            return RL_Rotate(node);
        else
            return RR_Rotate(node);
    }
    return node;
}

template<class T, class S>
T *RankTree<T, S>::findMax() const
{
    AVLNode<T, S> *maxNode = findMax_aux(root_);
    return maxNode->getData();
}

template<class T, class S>
T *RankTree<T, S>::findMin() const
{
    AVLNode<T, S> *minNode = findMin_aux(root_);
    return minNode->getData();
}

template<class T, class S>
int RankTree<T, S>::currentSize() const
{
    return currentSize_;
}

template<class T, class S>
T *RankTree<T, S>::getMostRight()
{
    return this->max_->getData();
}

template<class T, class S>
void RankTree<T, S>::rankUpdate(AVLNode<T, S> *node)
{
    node->rank_ = 1 + rankOfChild(node->left_) + rankOfChild(node->right_);
}

template<class T, class S>
int RankTree<T, S>::rankOfChild(AVLNode<T, S> *child) const
{
    if (child == NULL)
    {
        return 0;
    }
    else
    {
        return child->rank_;
    }
}

template<class T, class S>
int RankTree<T, S>::getInOrder(T *array, int size) const
{
    size = min(size, this->currentSize_);
    int index = 0;
    getInOrder(root_, array, size, &index);
    return size;
}

template<class T, class S>
void RankTree<T, S>::getInOrder(AVLNode<T, S> *root, T *array, int size, int *index) const
{
    if (root == nullptr || *index == size)
        return;
    getInOrder(root->left_, array, size, index);
    array[*index] = *(root->getData());
    (*index)++;
    getInOrder(root->right_, array, size, index);
}

template<class T, class S>
void RankTree<T, S>::buildOrdered(T **data, int range)
{
    int height_ = log(range) / log(2);
    this->root_ = buildOrdered_aux(data, 0, range - 1, height_);
    this->currentSize_ = range;
}

template<class T, class S>
AVLNode<T, S> *RankTree<T, S>::buildOrdered_aux(T **data, int start, int end, int height)
{
    if (start > end) { return nullptr; }

    int middle = (start + end) / 2;
    T *new_data = data[middle];
    AVLNode<T, S> *root = new AVLNode<T, S>(new_data);
    root->height_ = height;

    root->left_ = buildOrdered_aux(data, start, middle - 1, height - 1);
    root->right_ = buildOrdered_aux(data, middle + 1, end, height - 1);

    return root;
}

template<class T, class S>
bool RankTree<T, S>::checkTree()
{
    if (this->currentSize_ == 0) {
        return root_ == nullptr;
    }
    int height_ = log(currentSize_) / log(2);
    return checkTree_aux(root_, height_);
}

template<class T, class S>
bool RankTree<T, S>::checkTree_aux(AVLNode<T, S> *node, int h)
{
    if (node == nullptr) {
        return true;
    }
    if (h == 0) {
        if (node->right_) return false;
        if (node->left_) return false;
        return true;
    }
    //h>0
    return checkTree_aux(node->right_, h - 1) && checkTree_aux(node->left_, h - 1);

}


#endif /* RANK_TREE_H */
