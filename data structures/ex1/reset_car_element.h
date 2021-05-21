#ifndef RESET_CAR_ELEMENT_H
#define RESET_CAR_ELEMENT_H

#include "AVL_tree.h"
#include "sale_element.h"
#include "model_element.h"

class ResetCarElement {
public:
    AVLTree<ModelElement> resetModelsTree_;

    ResetCarElement(int typeID, int numOfModels);

    ResetCarElement(int typeID): typeID_(typeID) 
    {}

    ~ResetCarElement();

    int getTypeID() const { return typeID_; }

    bool operator>(const ResetCarElement &other) const;

    bool operator<(const ResetCarElement &other) const;

    bool operator==(const ResetCarElement &other) const;

private:
    int typeID_;
    int numOfModels_;
    
};

//to fix:the complexity should be O(numOfModels).
ResetCarElement::ResetCarElement(int typeID, int numOfModels):
    typeID_(typeID), numOfModels_(numOfModels), resetModelsTree_() 
{
    for (int i = 0; i < numOfModels; i++) {
        ModelElement* newModel = new ModelElement(typeID, i);
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

#endif /* RESET_CAR_ELEMENT_H */
