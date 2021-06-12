//
// Created by ASUS on 11/06/2021.
//
#include <iostream>
#include "Car_Element.h"

CarElement::CarElement(int typeID, int sales) : typeID_(typeID), sales_(sales)
{}

bool CarElement::operator<(const CarElement &element) const
{
    return this->typeID_ < element.typeID_;
}

bool CarElement::operator>(const CarElement &element) const
{
    return this->typeID_ > element.typeID_;
}

bool CarElement::operator==(const CarElement &element) const
{
    return this->typeID_ == element.typeID_;
}

int CarElement::getSales()
{
    return sales_;
}

int CarElement::getTypeId()
{
    return typeID_;
}

void CarElement::flatDelete()
{

}

CarElement *CarElement::clone()
{
    return new CarElement(this->typeID_, this->sales_);
}

void CarElement::print()
{
    std::cout << " (" << this->typeID_ << " , " << this->sales_ << ") ";
}