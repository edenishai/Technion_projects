//
// Created by ASUS on 11/06/2021.
//
#include "Agency.h"

void Agency::sellCar(int carType, int amount)
{

    CarElement car_to_find(carType);
    CarElement *car = this->cars_->find(&car_to_find);

    if (car != nullptr) { //if car was sold in past
        SaleElement sale_to_find(carType, car->getSales());

        //create new elements
        auto new_sale_element = new SaleElement(carType, car->getSales() + amount);
        auto new_car_element = new CarElement(carType, car->getSales() + amount);

        //update both trees
        this->sales_->remove(&sale_to_find);
        this->sales_->insert(new_sale_element);

        this->cars_->remove(&car_to_find);
        this->cars_->insert(new_car_element);

    } else { //first time sell
        auto new_sale_element = new SaleElement(carType, car->getSales() + amount);
        auto new_car_element = new CarElement(carType, car->getSales() + amount);

        this->sales_->insert(new_sale_element);
        this->cars_->insert(new_car_element);
    }
}