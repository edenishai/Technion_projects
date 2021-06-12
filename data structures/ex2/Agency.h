#ifndef AGENCY_TYPE_H
#define AGENCY_TYPE_H

//#include "../ex1/AVL_tree.h"
#include "Car_Element.h"
#include "Rank_tree.h"
#include "Sale_Element.h"

class Agency {
public:
    Agency();

    Agency(CarElement **cars, SaleElement **sales, int total_count);

    void sellCar(int carType, int amount);

    ~Agency();



    ///  vars
    RankTree<SaleElement> *sales_;

    RankTree<CarElement> *cars_;


};




#endif /* AGENCY_TYPE_H */
