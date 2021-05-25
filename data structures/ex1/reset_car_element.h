#ifndef RESET_CAR_ELEMENT_H
#define RESET_CAR_ELEMENT_H

#include "AVL_tree.h"
#include "sale_element.h"
#include "model_element.h"

class ResetCarElement {
public:
    AVLTree<ModelElement>* resetModelsTree_;

    ResetCarElement(int typeID, int numOfModels = 0);

    ResetCarElement();

   // ResetCarElement(const ResetCarElement& other);

    ~ResetCarElement();

    int getTypeID() const
    { return typeID_; }

    bool operator>(const ResetCarElement &other) const;

    bool operator<(const ResetCarElement &other) const;

    bool operator==(const ResetCarElement &other) const;

   // ResetCarElement& operator=(const ResetCarElement& other);

    void flatDelete();

    int getCurrentNumOfModels();

    void checkTree();

private:
    int typeID_;
    int numOfModels_;

};

#endif /* RESET_CAR_ELEMENT_H */
