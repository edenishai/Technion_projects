//
// Created by ASUS on 11/06/2021.
//

#include "Sale_Element.h"
SaleElement::SaleElement(int typeID,int sales):typeID_(typeID),sales_(sales)
{

}

bool SaleElement::operator<(SaleElement &element)
{
    return this->sales_<element.sales_; //todo: NOT finished
}

bool SaleElement::operator==(SaleElement &element)
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
