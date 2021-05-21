#include "reset_car_element.h"

//to fix:the complexity should be O(numOfModels).
ResetCarElement::ResetCarElement(int typeID, int numOfModels) :
        typeID_(typeID), numOfModels_(numOfModels), resetModelsTree_()
{
    for (int i = 0; i < numOfModels; i++) {
        ModelElement *newModel = new ModelElement(typeID, i);
        resetModelsTree_.insert(*newModel);
    }
}

ResetCarElement::~ResetCarElement()
{
    resetModelsTree_.clear();
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

AVLTree<ModelElement> ResetCarElement::getModlesTree()
{
    return this->resetModelsTree_;
}

int ResetCarElement::getCurrentNumOfModels()
{
    return this->resetModelsTree_.currentSize();
}
