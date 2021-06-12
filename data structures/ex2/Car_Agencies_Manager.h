#ifndef CAR_AGENCIES_MANAGER_H
#define CAR_AGENCIES_MANAGER_H

#include "library2.h"
#include "union_find.h"
#include "Agency.h"

class Car_Agencies_Manager {
public:
    Car_Agencies_Manager();

    StatusType AddAgency();

    StatusType SellCar(int agencyID, int typeID, int k);

    StatusType UniteAgencies(int agencyID1, int agencyID2);

    StatusType GetIthSoldType(int agencyID, int i, int *res);

    ~Car_Agencies_Manager();

    class UniteAgenciesFunc {
    public:
        Agency *operator()(Agency &a, Agency &b);

        void merge_cars(CarElement *a, int na, CarElement *b, int nb, CarElement *c);

        void merge_sales(SaleElement *a, int na, SaleElement *b, int nb, SaleElement *c);
    };

private:
    UnionFind<Agency> *agencies_;

};

#endif /* CAR_AGENCIES_MANAGER_H */
