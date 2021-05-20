#ifndef SALE_ELEMENT_H
#define SALE_ELEMENT_H

#include "AVL_tree.h"

class SaleElement {
public:
    SaleElement(int typeID) : typeID_(typeID), modelID_(0), maxSales_(0)
    {}

    SaleElement(const SaleElement &element);

    int getTypeID() const
    { return typeID_; }

    AVLNode<SaleElement> *getContainerNode() const
    { return containerNode_; }

    bool operator>(const SaleElement &other) const;

    bool operator<(const SaleElement &other) const;

    bool operator==(const SaleElement &other) const;


private:
    int typeID_;
    int modelID_;
    int maxSales_;
    AVLNode<SaleElement> *containerNode_;

};

SaleElement::SaleElement(const SaleElement &element) :
        typeID_(element.typeID_), modelID_(element.modelID_), maxSales_(element.maxSales_)
//,containerNode_(element.containerNode_)
{}

bool SaleElement::operator>(const SaleElement &other) const
{
    if (this->maxSales_ > other.maxSales_) { return true; }
    else if (this->maxSales_ == other.maxSales_ && this->typeID_ > other.typeID_) {
        return true;
    }
    return false;
}

bool SaleElement::operator<(const SaleElement &other) const
{
    if (this->maxSales_ < other.maxSales_) { return true; }
    else if (this->maxSales_ == other.maxSales_ && this->typeID_ < other.typeID_) {
        return true;
    }
    return false;
}

bool SaleElement::operator==(const SaleElement &other) const
{
    return this->typeID_ == other.typeID_
           && this->modelID_ == other.modelID_
           && this->maxSales_ == other.maxSales_;
}

#endif /* SALE_ELEMENT_H */