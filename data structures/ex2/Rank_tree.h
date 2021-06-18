#ifndef RANK_TREE_H
#define RANK_TREE_H

#include <iostream>
#include <cmath>

using namespace std;

template<class T>
class RTNode {
public:
    RTNode *parent_;
    RTNode *left_;
    RTNode *right_;
    int height_;
    int size_;

    RTNode():
            parent_(nullptr), left_(nullptr), right_(nullptr), height_(0), size_(1), data_(nullptr) {}

    explicit RTNode(T *data):
            parent_(nullptr), left_(nullptr), right_(nullptr), height_(0), size_(1), data_(data) {}

    ~RTNode() { delete data_; }

    T *getData() { return data_; }

private:
    T *data_;
};


template<class T>
class RankTree {
public:
    RankTree():
            root_(nullptr), max_(nullptr), min_(nullptr) {}

    ~RankTree() { clear(); }

    void insert(T *data);

    void remove(T *data);

    void clear();

    void buildOrdered(T **data_arr, int range);

    T *find(const T *data) const;

    T *findByRank(int i) const;

    T *findMax() const;

    T *findMin() const;

    T *getMax() const;

    T *getMin() const;

    int currentSize() const;

    void getInOrder(T *array, int size) const;
    
private:
    RTNode<T> *root_;
    RTNode<T> *max_;
    RTNode<T> *min_;

    RTNode<T> *LL_Rotate(RTNode<T> *node);

    RTNode<T> *RR_Rotate(RTNode<T> *node);

    RTNode<T> *LR_Rotate(RTNode<T> *node);

    RTNode<T> *RL_Rotate(RTNode<T> *node);

    RTNode<T> *insert_aux(T *data, RTNode<T> *node);

    RTNode<T> *remove_aux(T *data, RTNode<T> *node);

    void deepRemoveNode(RTNode<T> *node);

    RTNode<T> *buildOrdered_aux(T **data, int start, int end, int height);

    T *find_aux(RTNode<T> *root, const T *data) const;

    T *findByRank_aux(RTNode<T> *node, int range, int i) const;

    RTNode<T> *findMax_aux(RTNode<T> *node) const;

    RTNode<T> *findMin_aux(RTNode<T> *node) const;

    int balanceFactor(RTNode<T> *node) const;

    int height(RTNode<T> *node) const;

    void sizeUpdate(RTNode<T> *node);

    int size(RTNode<T> *node) const;

    void getInOrder(RTNode<T> *node, T *array, int size, int *index, bool read_flag) const;
};

template<class T>
void RankTree<T>::insert(T *data)
{
    if (find(data))
        return;
    root_ = insert_aux(data, root_);
    max_ = findMax_aux(root_);
    min_ = findMin_aux(root_);
}

template<class T>
void RankTree<T>::remove(T *data)
{
    if (find(data)) {
        root_ = remove_aux(data, root_);
        max_ = findMax_aux(root_);
        min_ = findMin_aux(root_);
    }
}

template<class T>
void RankTree<T>::clear()
{
    if (root_) {
        deepRemoveNode(root_);
    }
}

template<class T>
void RankTree<T>::buildOrdered(T **data, int range)
{
    root_ = buildOrdered_aux(data, 0, range - 1, log(range) / log(2));
    max_ = findMax_aux(root_);
    min_ = findMin_aux(root_);
}

template<class T>
T *RankTree<T>::find(const T *data) const
{
    T *d = find_aux(root_, data);
    return d;
}

template<class T>
T *RankTree<T>::findByRank(int i) const
{
    int size = currentSize();
    if (size < ++i) {
        return nullptr;
    }
    return findByRank_aux(root_, size, i);
}

template<class T>
T *RankTree<T>::findMax() const
{
    RTNode<T> *maxNode = findMax_aux(root_);
    return maxNode->getData();
}

template<class T>
T *RankTree<T>::findMin() const
{
    RTNode<T> *minNode = findMin_aux(root_);
    return minNode->getData();
}

template<class T>
T *RankTree<T>::getMax() const
{
    return max_->getData();
}

template<class T>
T *RankTree<T>::getMin() const
{
    return min_->getData();
}

template<class T>
int RankTree<T>::currentSize() const
{
    if (root_)
        return root_->size_;
    return 0;
}

template<class T>
void RankTree<T>::getInOrder(T *array, int size) const
{
    size = min(size, currentSize());
    int index = 0;
    getInOrder(min_, array, size, &index, true);
}

template<class T>
RTNode<T> *RankTree<T>::LL_Rotate(RTNode<T> *node)
{
    RTNode<T> *temp = node->left_;

    if (temp->right_)
        temp->right_->parent_ = node;
    temp->parent_ = node->parent_;
    node->parent_ = temp;
    node->left_ = temp->right_;
    temp->right_ = node;
    node->height_ = max(height(node->left_), height(node->right_)) + 1;
    temp->height_ = max(height(temp->left_), height(temp->right_)) + 1;
    sizeUpdate(node);
    sizeUpdate(temp);
    return temp;
}

template<class T>
RTNode<T> *RankTree<T>::RR_Rotate(RTNode<T> *node)
{
    RTNode<T> *temp = node->right_;
    
    if (temp->left_)
        temp->left_->parent_ = node;
    temp->parent_ = node->parent_;
    node->parent_ = temp;
    node->right_ = temp->left_;
    temp->left_ = node;
    node->height_ = max(height(node->left_), height(node->right_)) + 1;
    temp->height_ = max(height(temp->left_), height(temp->right_)) + 1;
    sizeUpdate(node);
    sizeUpdate(temp);
    return temp;
}

template<class T>
RTNode<T> *RankTree<T>::LR_Rotate(RTNode<T> *node)
{
    node->left_ = RR_Rotate(node->left_);
    return LL_Rotate(node);
}

template<class T>
RTNode<T> *RankTree<T>::RL_Rotate(RTNode<T> *node)
{
    node->right_ = LL_Rotate(node->right_);
    return RR_Rotate(node);
}

template<class T>
RTNode<T> *RankTree<T>::insert_aux(T *data, RTNode<T> *node)
{
    // stop condition
    if (node == nullptr)
        node = new RTNode<T>(data);

    else if (*data < *(node->getData())) {
        node->left_ = insert_aux(data, node->left_);
        node->left_->parent_ = node;
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left_) == -1)
                node = LR_Rotate(node);
            else
                node = LL_Rotate(node);
        }
    } else if (*data > *(node->getData())) {
        node->right_ = insert_aux(data, node->right_);
        node->right_->parent_ = node;
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right_) == 1)
                node = RL_Rotate(node);
            else
                node = RR_Rotate(node);
        }
    }
    node->height_ = max(height(node->left_), height(node->right_)) + 1;
    sizeUpdate(node);

    return node;
}

template<class T>
RTNode<T> *RankTree<T>::remove_aux(T *data, RTNode<T> *node)
{
    RTNode<T> *temp;

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
        if (node)
            node->parent_ = temp->parent_;
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
    sizeUpdate(node);
    return node;
}

template<class T>
void RankTree<T>::deepRemoveNode(RTNode<T> *node)
{
    if (node) {
        deepRemoveNode(node->left_);
        deepRemoveNode(node->right_);
        delete node;
    }
}

template<class T>
RTNode<T> *RankTree<T>::buildOrdered_aux(T **data, int start, int end, int height)
{
    if (start > end)
        return nullptr;

    int middle = (start + end) / 2;
    T *new_data = data[middle];
    RTNode<T> *node = new RTNode<T>(new_data);
    node->height_ = height;
    
    node->left_ = buildOrdered_aux(data, start, middle - 1, height - 1);
    if (node->left_)
        node->left_->parent_ = node;
    node->right_ = buildOrdered_aux(data, middle + 1, end, height - 1);
    if (node->right_)
        node->right_->parent_ = node;

    sizeUpdate(node);
    return node;
}

template<class T>
T *RankTree<T>::find_aux(RTNode<T> *root, const T *data) const
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

template<class T>
T *RankTree<T>::findByRank_aux(RTNode<T> *node, int range, int i) const {
    if (!node)
        return nullptr;
    int leftSize = size(node->left_);
    int rightSize = size(node->right_);
    if (i <= leftSize)
        return findByRank_aux(node->left_, leftSize, i);
    else if (i >= range-rightSize+1)
        return findByRank_aux(node->right_, rightSize, i-(range-rightSize));
    else
        return node->getData();
}

template<class T>
RTNode<T> *RankTree<T>::findMax_aux(RTNode<T> *node) const
{
    if (node == NULL)
        return NULL;
    else if (node->right_ == NULL)
        return node;
    else
        return findMax_aux(node->right_);
}

template<class T>
RTNode<T> *RankTree<T>::findMin_aux(RTNode<T> *node) const
{
    if (node == NULL)
        return NULL;
    else if (node->left_ == NULL)
        return node;
    else
        return findMin_aux(node->left_);
}

template<class T>
int RankTree<T>::balanceFactor(RTNode<T> *node) const
{
    if (!node) {
        return 0;
    }
    return height(node->left_) - height(node->right_);
}

template<class T>
int RankTree<T>::height(RTNode<T> *node) const
{
    return (node == NULL ? -1 : node->height_);
}

template<class T>
void RankTree<T>::sizeUpdate(RTNode<T> *node)
{
    node->size_ = 1 + size(node->left_) + size(node->right_);
}

template<class T>
int RankTree<T>::size(RTNode<T> *node) const
{
    if (node == nullptr)
        return 0;

    return node->size_;
}

template<class T>
void RankTree<T>::getInOrder(RTNode<T> *node, T *array, int size, int *index, bool read_flag) const
{
    if (!node || *index == size)
        return;

    if (read_flag) {
        array[*index] = *(node->getData());
        (*index)++;
    }
    if (node->right_ && read_flag) {
        getInOrder(findMin_aux(node->right_), array, size, index, true);
        return;
    }
    if (*index == size) 
        return;

    if (node->parent_ && node->parent_->left_ == node)
        getInOrder(node->parent_, array, size, index, true);
    else if (node->parent_ && node->parent_->right_ == node)
        getInOrder(node->parent_, array, size, index, false);
}

#endif /* RANK_TREE_H */