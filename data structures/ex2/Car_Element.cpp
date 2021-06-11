//
// Created by ASUS on 11/06/2021.
//
#include "Car_Element.h"

CarElement::CarElement(int typeID,int sales): typeID_(typeID), sales_(sales)
{}

bool CarElement::operator<(CarElement &element)
{
    return this->typeID_<element.typeID_;
}

bool CarElement::operator==(CarElement &element)
{
    return this->typeID_==element.typeID_;
}
int CarElement::getSales()
{
    return sales_;
}

int CarElement::getTypeId()
{
    return typeID_;
}