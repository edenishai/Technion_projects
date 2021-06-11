#include "library2.h"
#include <memory>
#include "Car_Agencies_Manager.h"

void *Init()
{
    auto *DS = new Car_Agencies_Manager();
    return (void*)DS;
}

StatusType AddAgency(void *DS)
{
    if (!DS) {
        return INVALID_INPUT;
    }
    return ((Car_Agencies_Manager *) DS)->AddAgency();
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k)
{
    if (!DS || agencyID < 0 || k <= 0) {
        return INVALID_INPUT;
    }
    return ((Car_Agencies_Manager *) DS)->SellCar(agencyID, typeID, k);
}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2)
{
    if (!DS || agencyID1 < 0 || agencyID2 < 0) {
        return INVALID_INPUT;
    }
    return ((Car_Agencies_Manager *) DS)->UniteAgencies(agencyID1, agencyID2);
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res)
{
    if (!DS || !res || agencyID < 0 || i < 0) {
        return INVALID_INPUT;
    }
    return ((Car_Agencies_Manager *) DS)->GetIthSoldType(agencyID, i, res);
}

void Quit(void** DS)
{
    auto* toDelete = static_cast<Car_Agencies_Manager*>(*DS);
    delete toDelete;
    *DS = NULL;
}