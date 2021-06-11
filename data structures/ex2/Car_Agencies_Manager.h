#ifndef CAR_AGENCIES_MANAGER_H
#define CAR_AGENCIES_MANAGER_H

#include "library2.h"
#include "Union_Find.h"
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
    };

private:
    UnionFind<Agency> *agencies_;

    void merge(CarElement *a, int na, CarElement *b, int nb, CarElement *c);
};

Car_Agencies_Manager::Car_Agencies_Manager()
{
    agencies_ = new UnionFind<Agency>;
}

StatusType Car_Agencies_Manager::AddAgency()
{
    //todo: add try catch for memory leaks
    auto na = new Agency();
    agencies_->makeSet(na);
    return SUCCESS;
}

StatusType Car_Agencies_Manager::SellCar(int agencyID, int typeID, int k)
{
    if (agencies_->findIdentifier(agencyID) == agencies_->NO_PARENT) {
        return FAILURE;
    }
    Agency &agency = agencies_->findElement(agencyID);
    agency.sellCar(typeID, k);
    return SUCCESS;

}

StatusType Car_Agencies_Manager::UniteAgencies(int agencyID1, int agencyID2)
{
    agencies_->Union(agencyID1, agencyID2, UniteAgenciesFunc());
    return FAILURE;
}

StatusType Car_Agencies_Manager::GetIthSoldType(int agencyID, int i, int *res)
{
    return FAILURE;
}

Car_Agencies_Manager::~Car_Agencies_Manager()
{
    delete agencies_;
}


//////////////////////////////  Unite class
Agency *Car_Agencies_Manager::UniteAgenciesFunc::operator()(Agency &a, Agency &b)
{
    //todo: unite the 2 trees
    return new Agency();
}
void Car_Agencies_Manager::merge(CarElement a[], int na, CarElement b[], int nb, CarElement c[])
{
    int ia, ib, ic;
    for (ia = ib = ic = 0; (ia < na) && (ib < nb); ic++) {
        if (a[ia] < b[ib]) {
            c[ic] = a[ia];
            ia++;
        } else {
            c[ic] = b[ib];
            ib++;
        }
    }
    for (; ia < na; ia++, ic++) c[ic] = a[ia];
    for (; ib < nb; ib++, ic++) c[ic] = b[ib];
}
#endif /* CAR_AGENCIES_MANAGER_H */