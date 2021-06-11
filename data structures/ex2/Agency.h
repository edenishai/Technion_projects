#ifndef AGENCY_TYPE_H
#define AGENCY_TYPE_H

#include "../ex1/AVL_tree.h"
#include "Rank_Tree.h"
#include "car_type.h"
#include "sold_type.h"

class AgencyType {
public:
    AgencyType() =default;

    ~AgencyType()=default;

    void sellCar(int carType, int amount)
    {
        //todo: complete
    }
    AVLTree<CarType>* cars_;
    RankTree<SoldType>* sales_;
};



#endif /* AGENCY_TYPE_H */
