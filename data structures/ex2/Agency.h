#ifndef AGENCY_TYPE_H
#define AGENCY_TYPE_H

//#include "../ex1/AVL_tree.h"
#include "Car_Element.h"
#include "Rank_Tree.h"
#include "Sale_Element.h"
class Agency {
public:
    Agency() =default;

    ~Agency()=default;

    void sellCar(int carType, int amount)
    {
        CarElement to_find(carType);
        CarElement* car = this->cars_->find(&to_find);
        SaleElement to_remove(carType,car->getSales());
        this->sales_->remove(&to_remove);
    }

private:
    RankTree<SaleElement,int>* sales_;
    RankTree<CarElement,int>* cars_;
};



#endif /* AGENCY_TYPE_H */