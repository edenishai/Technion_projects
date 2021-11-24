#include "sale_element.h"

SaleElement::SaleElement(const SaleElement &element) :
    typeID_(element.typeID_), modelID_(element.modelID_), sales_(element.sales_)
{}

SaleElement::SaleElement(int typeID, int modelID, int sales) :
    typeID_(typeID), modelID_(modelID), sales_(sales)
{}

bool SaleElement::operator>(const SaleElement &other) const
{
    if (this->sales_ > other.sales_)
        return true;
    else if (this->sales_ == other.sales_) {
        if (this->typeID_ < other.typeID_)
            return true;
        else if (this->typeID_ == other.typeID_) {
            if (this->modelID_ < other.modelID_)
                return true;
        }
    }
    return false;
}

bool SaleElement::operator<(const SaleElement &other) const
{
    if (this->sales_ < other.sales_)
        return true;
    else if (this->sales_ == other.sales_) {
        if (this->typeID_ > other.typeID_)
            return true;
        else if (this->typeID_ == other.typeID_) {
            if (this->modelID_ > other.modelID_)
                return true;
        }
    }
    return false;
}

bool SaleElement::operator==(const SaleElement &other) const
{
    return this->typeID_ == other.typeID_
           && this->modelID_ == other.modelID_
           && this->sales_ == other.sales_;
}

int SaleElement::getModelId() const
{
    return this->modelID_;
}

void SaleElement::flatDelete()
{

}
