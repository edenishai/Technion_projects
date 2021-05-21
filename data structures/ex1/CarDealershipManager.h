#ifndef CAR_DEALERSHIP_MANAGER_H
#define CAR_DEALERSHIP_MANAGER_H

#include "AVL_tree.h"
#include "car_element.h"
#include "reset_car_element.h"
#include "sale_element.h"
#include "model_element.h"
#include "library.h"

class CarDealershipManager {
public:
    CarDealershipManager();

    StatusType AddCarType(int typeID, int numOfModels);

    StatusType RemoveCarType(int typeID);

    StatusType SellCar(int typeID, int modelID);

    StatusType MakeComplaint(int typeID, int modelID, int t);

    StatusType GetBestSellerModelByType(int typeID, int *modelID);

    StatusType GetWorstModels(int numOfModels, int *types, int *models);

    ~CarDealershipManager();

private:
    AVLTree<ResetCarElement> resetCarsTree_;
    AVLTree<CarElement> carsTree_;
    AVLTree<ModelElement> modelsTree_;
    AVLTree<SaleElement> salesTree_;

    void merge(int a[], int na, int b[], int nb, int c[]);
};

#endif /* CAR_DEALERSHIP_MANAGER_H */
