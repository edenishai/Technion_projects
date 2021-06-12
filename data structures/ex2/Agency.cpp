//
// Created by ASUS on 11/06/2021.
//
#include "Agency.h"

Agency::Agency()
{
    this->cars_= new RankTree<CarElement>;
    this->sales_= new RankTree<SaleElement>;

}

Agency::Agency(CarElement **cars, SaleElement **sales, int total_count)
{
    this->cars_= new RankTree<CarElement>;
    this->cars_->buildOrdered(cars,total_count);

    this->sales_= new RankTree<SaleElement>;
    this->sales_->buildOrdered(sales,total_count);
}

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
        auto new_sale_element = new SaleElement(carType,  amount);
        auto new_car_element = new CarElement(carType, amount);

        this->sales_->insert(new_sale_element);
        this->cars_->insert(new_car_element);
    }
}

Agency::~Agency()
{
    delete cars_;
    delete sales_;
}


