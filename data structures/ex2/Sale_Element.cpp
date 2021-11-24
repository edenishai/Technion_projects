//
// Created by ASUS on 11/06/2021.
//

#include <iostream>
#include "Sale_Element.h"
SaleElement::SaleElement(int typeID,int sales):typeID_(typeID),sales_(sales)
{

}

bool SaleElement::operator<(const SaleElement &element) const
{
    if(this->sales_<element.sales_)
        return true;
    else if(this->sales_==element.sales_)
        if(this->typeID_<element.typeID_) {
            return true;
        }
    return false;
}

bool SaleElement::operator==(const SaleElement &element) const
{
    return (this->typeID_==element.typeID_) && (this->sales_==element.sales_);
}

int SaleElement::getSales()
{
    return sales_;
}

int SaleElement::getTypeId()
{
    return typeID_;
}

bool SaleElement::operator>(const SaleElement &element) const
{
    if(this->sales_>element.sales_)
        return true;
    else if(this->sales_==element.sales_)
        if(this->typeID_>element.typeID_) {
            return true;
        }
    return false;
}

void SaleElement::flatDelete()
{

}

SaleElement *SaleElement::clone()
{
    return new SaleElement(this->typeID_,this->sales_);
}

void SaleElement::print()
{
    std::cout<<" ("<<this->typeID_<<" , "<< this->sales_<<") ";
}