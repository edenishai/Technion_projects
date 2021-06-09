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

private:
    UnionFind<AgencyType>* agencies_;

};

#endif /* CAR_AGENCIES_MANAGER_H */
