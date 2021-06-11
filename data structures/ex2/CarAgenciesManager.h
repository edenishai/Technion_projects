#ifndef CAR_AGENCIES_MANAGER_H
#define CAR_AGENCIES_MANAGER_H

#include "library2.h"
#include "union_find.h"
#include "agency_type.h"

class CarAgenciesManager {
public:
    CarAgenciesManager();

    StatusType AddAgency();

    StatusType SellCar(int agencyID, int typeID, int k);

    StatusType UniteAgencies(int agencyID1, int agencyID2);

    StatusType GetIthSoldType(int agencyID, int i, int* res);

    ~CarAgenciesManager();

    class UniteAgencyFunc {
    public:
        AgencyType* operator()(AgencyType *, AgencyType *)
        {}
    };

private:
    UnionFind<AgencyType>* agencies_;

};

CarAgenciesManager::CarAgenciesManager()
{
    agencies_ = new UnionFind<AgencyType>;
}

StatusType CarAgenciesManager::AddAgency()
{
    //todo: add try catch for memory leaks
    auto na = new AgencyType();
    agencies_->makeSet(na);
    return SUCCESS;
}

StatusType CarAgenciesManager::SellCar(int agencyID, int typeID, int k)
{
    if(agencies_->findIdentifier(agencyID) == agencies_->NO_PARENT)
    {
        return FAILURE;
    }
    AgencyType& agency = agencies_->findElement(agencyID);
    agency.sellCar(typeID,k);
    return SUCCESS;

}

StatusType CarAgenciesManager::UniteAgencies(int agencyID1, int agencyID2)
{
    agencies_->Union(agencyID1,agencyID2,UniteAgencyFunc());
    return FAILURE;
}

StatusType CarAgenciesManager::GetIthSoldType(int agencyID, int i, int *res)
{
    return FAILURE;
}

CarAgenciesManager::~CarAgenciesManager()
{
    delete agencies_;
}

#endif /* CAR_AGENCIES_MANAGER_H */
