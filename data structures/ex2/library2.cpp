#include "library2.h"
#include <memory>
#include "CarAgenciesManager.h"

void *Init()
{
    CarAgenciesManager *DS = new CarAgenciesManager();
    return (void*)DS;
}

StatusType AddAgency(void *DS)
{
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((CarAgenciesManager *) DS)->AddAgency();
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k)
{
    if (!DS || agencyID < 0 || k <= 0) {
        return INVALID_INPUT;
    }
    return ((CarAgenciesManager *) DS)->SellCar(agencyID, typeID, k);
}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2)
{
    if (!DS || agencyID1 < 0 || agencyID2 < 0) {
        return INVALID_INPUT;
    }
    return ((CarAgenciesManager *) DS)->UniteAgencies(agencyID1, agencyID2);
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res)
{
    if (!DS || !res || agencyID < 0 || i < 0) {
        return INVALID_INPUT;
    }
    return ((CarAgenciesManager *) DS)->GetIthSoldType(agencyID, i, res);
}

void Quit(void** DS)
{
    CarAgenciesManager *toDelete = static_cast<CarAgenciesManager*>(*DS);
    delete toDelete;
    *DS = NULL;
}
