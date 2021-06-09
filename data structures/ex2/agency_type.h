#ifndef AGENCY_TYPE_H
#define AGENCY_TYPE_H

#include "../ex1/AVL_tree.h"
#include "car_type.h"

class AgencyType {
public:
    AgencyType();

    ~AgencyType();

private:
    AVLTree<CarType>* cars_;
    RankAVL<T, S>* sales_;
};

#endif /* AGENCY_TYPE_H */
