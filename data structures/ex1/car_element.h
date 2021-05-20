#ifndef CAR_ELEMENT_H
#define CAR_ELEMENT_H

#include "sale_element.h"
#include "model_element.h"

class CarElement {
public:
    //to add compare and operators.
    CarElement(int typeID, int numOfModels);

    CarElement(int typeID) : typeID_(typeID)
    {}

    ~CarElement();

    void setCarSales(SaleElement *carSales)
    { carSales_ = carSales; }

    int getTypeID() const
    { return typeID_; }

    int getNumOfModels() const
    { return numOfModels_; }

    const SaleElement &getCarSales()
    { return *carSales_; }

    AVLNode<SaleElement> *getCarSalesParentNode()
    { return (carSales_)->getContainerNode(); }

    ModelElement **getCarModels()
    { return carModels_; }

    bool operator>(const CarElement &other) const;

    bool operator<(const CarElement &other) const;

    bool operator==(const CarElement &other) const;

private:
    int typeID_;
    int numOfModels_;
    SaleElement *carSales_;
    ModelElement **carModels_;  //operator ==
};

CarElement::CarElement(int typeID, int numOfModels) :
        typeID_(typeID), numOfModels_(numOfModels), carSales_(nullptr), carModels_(new ModelElement *[numOfModels])
{
    for (int i; i < numOfModels; i++) {
        carModels_[i] = nullptr;
    }
}

CarElement::~CarElement()
{
    delete carSales_; //???
    carSales_->getTypeID();
}

bool CarElement::operator==(const CarElement &other) const
{
    //todo: should we add check for car sales and cas models?
    if (this->typeID_ == other.typeID_
        && this->numOfModels_ == other.numOfModels_)
        return true;
    return false;
}

bool CarElement::operator>(const CarElement &other) const
{
    return this->typeID_ > other.typeID_;
}

bool CarElement::operator<(const CarElement &other) const
{
    return this->typeID_ < other.typeID_;
}

#endif /* CAR_ELEMENT_H */