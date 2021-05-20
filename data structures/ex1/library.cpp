#include "library.h"
#include "CarDealershipManager.h"

void *Init() {
    CarDealershipManager *DS = new CarDealershipManager();
    return (void*)DS;
}

StatusType AddCarType(void *DS, int typeID, int numOfModels) {
    if(!DS || numOfModels <= 0 || typeID <= 0) {
        return INVALID_INPUT;
    }
    return ((CarDealershipManager*)DS)->AddCarType(typeID, numOfModels);
}

StatusType RemoveCarType(void *DS, int typeID) {
    if(!DS || typeID <= 0) {
        return INVALID_INPUT;
    }
    return ((CarDealershipManager*)DS)->RemoveCarType(typeID);
}

StatusType SellCar(void *DS, int typeID, int modelID) {
    if(!DS || typeID <= 0 || modelID < 0) {
        return INVALID_INPUT;
    }
    return ((CarDealershipManager*)DS)->SellCar(typeID, modelID);
}

