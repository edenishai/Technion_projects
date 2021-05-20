#ifndef RESET_CAR_ELEMENT_H
#define RESET_CAR_ELEMENT_H

#include "AVL_tree.h"
#include "sale_element.h"
#include "model_element.h"

class ResetCarElement {
public:
    //to add compare and operators.
    ResetCarElement(int typeID, int numOfModels);
    ResetCarElement(int typeID): typeID_(typeID) {}
    ~ResetCarElement();
    int getTypeID() const { return typeID_; }

private:
    int typeID_;
    int numOfModels_;
    AVLTree<ModelElement> resetModelsTree_;
};

//to fix:the complexity should be O(numOfModels).
ResetCarElement::ResetCarElement(int typeID, int numOfModels):
    typeID_(typeID), numOfModels_(numOfModels), resetModelsTree_() {
        for(int i = 0; i < numOfModels; i++) {
            ModelElement* newModel = new ModelElement(typeID, i);
            resetModelsTree_.insert(*newModel);
        }
}

ResetCarElement::~ResetCarElement() {
    resetModelsTree_.clear();
}

#endif /* RESET_CAR_ELEMENT_H */