#include "reset_car_element.h"

//to fix:the complexity should be O(numOfModels).
ResetCarElement::ResetCarElement(int typeID, int numOfModels) :
        typeID_(typeID), numOfModels_(numOfModels), resetModelsTree_(new AVLTree<ModelElement>)
{
    if (numOfModels <= 0)
        return;

    ModelElement **arr = new ModelElement *[numOfModels];
    for (int i = 0; i < numOfModels; i++) {
        arr[i] = new ModelElement(typeID, i);
    }

    this->resetModelsTree_->buildOrdered(arr, numOfModels);
    delete[] arr;
    //checkTree();

}

ResetCarElement::ResetCarElement() :
        typeID_(0), numOfModels_(0), resetModelsTree_(nullptr)
{

}

/*
ResetCarElement::ResetCarElement(const ResetCarElement &other) :
        typeID_(other.typeID_), numOfModels_(other.numOfModels_),
        resetModelsTree_(new AVLTree<ModelElement>())
{
    this->typeID_ = other.typeID_;
    this->numOfModels_ = other.numOfModels_;
    ModelElement arr[other.resetModelsTree_->currentSize()];
    other.resetModelsTree_->getInOrder(arr, other.resetModelsTree_->currentSize());
    for (int i = 0; i < other.resetModelsTree_->currentSize(); i++) {
        this->resetModelsTree_->insert(arr[i].clone());
    }
}

ResetCarElement &ResetCarElement::operator=(const ResetCarElement &other)
{
    if (this == &other)
        return *this;

    delete this;

    this->typeID_ = other.typeID_;
    this->numOfModels_ = other.numOfModels_;
    ModelElement arr[other.resetModelsTree_->currentSize()];
    other.resetModelsTree_->getInOrder(arr, other.resetModelsTree_->currentSize());
    this->resetModelsTree_ = new AVLTree<ModelElement>();
    for (int i = 0; i < other.resetModelsTree_->currentSize(); i++) {
        this->resetModelsTree_->insert(arr[i].clone());
    }
    this->resetModelsTree_->current_size_ = numOfModels_;

    return *this;
}*/

ResetCarElement::~ResetCarElement()
{
    if (resetModelsTree_) {
        delete this->resetModelsTree_;
    }

}

bool ResetCarElement::operator==(const ResetCarElement &other) const
{
    if (this->typeID_ == other.typeID_)
        return true;
    return false;
}

bool ResetCarElement::operator>(const ResetCarElement &other) const
{
    return this->typeID_ > other.typeID_;
}

bool ResetCarElement::operator<(const ResetCarElement &other) const
{
    return this->typeID_ < other.typeID_;
}

int ResetCarElement::getCurrentNumOfModels()
{
    return this->resetModelsTree_->currentSize();
}

void ResetCarElement::checkTree()
{
    if (!this->resetModelsTree_->checkTree())
        cout << "***************reset SUB tree NOT OK";
}

void ResetCarElement::flatDelete()
{
    this->resetModelsTree_ = nullptr;
}
