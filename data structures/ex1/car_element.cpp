#include "car_element.h"

CarElement::CarElement(int typeID, int numOfModels) :
        typeID_(typeID), numOfModels_(numOfModels), carSales_(nullptr), carModels_(new ModelElement *[numOfModels])
{
    for (int i = 0; i < numOfModels; i++) {
        carModels_[i] = nullptr;
    }
}

CarElement::~CarElement()
{
    if (carModels_) {
        for (int i = 0; i < numOfModels_; i++)
            if (carModels_[i]) { delete carModels_[i]; }

        delete[] carModels_;
    }
}

bool CarElement::operator==(const CarElement &other) const
{
    if (this->typeID_ == other.typeID_)
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

SaleElement *CarElement::getBestSeller()
{
    return carSales_;
}

ModelElement *CarElement::getModel(int i)
{
    if (i > numOfModels_)
        return nullptr;
    return carModels_[i];
}

CarElement::CarElement(int typeID) : typeID_(typeID)
{
    carModels_ = nullptr;
}
