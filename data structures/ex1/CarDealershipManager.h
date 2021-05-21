#ifndef CAR_DEALERSHIP_MANAGER_H
#define CAR_DEALERSHIP_MANAGER_H

#include "AVL_tree.h"
#include "car_element.h"
#include "reset_car_element.h"
#include "sale_element.h"
#include "model_element.h"
#include "library.h"

const int SELL_POINTS = 10;
const int COMPLAINT_POINTS = 100;

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

};

CarDealershipManager::CarDealershipManager():
    resetCarsTree_(), carsTree_(), modelsTree_(), salesTree_() {}

//toDo: null check
StatusType CarDealershipManager::AddCarType(int typeID, int numOfModels)
{
    if (numOfModels <= 0 || typeID <= 0)
        return INVALID_INPUT;
    CarElement *carElement = new CarElement(typeID, numOfModels);
    if (carsTree_.find(*carElement) != NULL) {
        delete carElement;
        return FAILURE;
    }
    SaleElement *saleElement = new SaleElement(typeID);
    salesTree_.insert(*saleElement);
    carElement->carSales_ = saleElement;
    carsTree_.insert(*carElement);
    resetCarsTree_.insert(*(new ResetCarElement(typeID, numOfModels)));

    return SUCCESS;
}

StatusType CarDealershipManager::RemoveCarType(int typeID)
{
    if (typeID <= 0)
        return INVALID_INPUT;
    CarElement *toDelete = carsTree_.find(CarElement(typeID));
    if (!toDelete)
        return FAILURE;
    resetCarsTree_.remove(ResetCarElement(typeID));
    salesTree_.remove(*(toDelete->carSales_));
    ModelElement **carModels = toDelete->carModels_;
    for (int i = 0; i < toDelete->getNumOfModels(); i++) {
        if (carModels[i])
            modelsTree_.remove(*(carModels[i]));
    }
    carsTree_.remove(*toDelete);
    
    return SUCCESS;
}

StatusType CarDealershipManager::SellCar(int typeID, int modelID) 
{
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;
    CarElement* carType = carsTree_.find(CarElement(typeID));
    if (!carType)
        return FAILURE;
    ResetCarElement* resetCarType = resetCarsTree_.find(ResetCarElement(typeID, modelID));
    ModelElement* resetModelType = NULL;
    if (resetCarType) {
        resetModelType = resetCarType->resetModelsTree_.find(ModelElement(typeID, modelID));
        if (resetModelType) {
            ModelElement* newModel = new ModelElement(typeID, modelID, SELL_POINTS);
            carType->carModels_[modelID] = newModel;
            modelsTree_.insert(*newModel);
            SaleElement* saleElement = new SaleElement(typeID, modelID, SELL_POINTS);
            if (*saleElement > *(carType->carSales_)) {
                salesTree_.remove(*(carType->carSales_));
                carType->carSales_ = saleElement;
                salesTree_.insert(*saleElement);
            }
        }
    }
    else if (!resetCarType || !resetModelType) {
        ModelElement* newModel = new ModelElement(typeID, modelID, carType->carModels_[modelID]->getGrade()+SELL_POINTS);
        modelsTree_.remove(*(carType->carModels_[modelID]));
        carType->carModels_[modelID] = newModel;
        modelsTree_.insert(*newModel);

        SaleElement* saleElement = new SaleElement(typeID, modelID, carType->carSales_->getSales()+SELL_POINTS);
        if (*saleElement > *(carType->carSales_)) {
            salesTree_.remove(*(carType->carSales_));
            carType->carSales_ = saleElement;
            salesTree_.insert(*saleElement);
        }
    }
    return SUCCESS;
}

//toDo
StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
{
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;
    //...
    return SUCCESS;
}

//toDo
StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID)
{
    if (typeID < 0)
        return INVALID_INPUT;

    if (typeID > 0) {
        CarElement* car_element = this->carsTree_.find(CarElement(typeID));
        SaleElement *best_seller_model = car_element->carSales_;
        *modelID = best_seller_model->getModelId();
    } else
    {
        CarElement &car_element = this->carsTree_.getMostRight();
        SaleElement *best_seller_model = car_element.carSales_;
        *modelID = best_seller_model->getModelId();
    }
    return SUCCESS;
}

//TODO:ADD check we have enough elements in total + check memory fail
StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types_target, int *models_target)
{
    if (numOfModels <= 0) {
        return INVALID_INPUT;
    }
    //read from models
    ModelElement models_source[numOfModels];
    this->modelsTree_.inorderNObjects(models_source, numOfModels);
    int index = 0;
    for (int i = 0; i < numOfModels && index < numOfModels; i++) {
        if (models_source[i].getGrade() < 0) {
            types_target[index] = models_source[i].getTypeId();
            models_target[index] = models_source[i].getModel();
            index++;
        } else
            break;
    }

    //read from reset
    ResetCarElement cars_source[numOfModels];
    this->resetCarsTree_.inorderNObjects(cars_source, numOfModels);
    for (int i = 0; i < numOfModels && index < numOfModels; i++) {
        //read from subtree
        int sub_model_amount = cars_source[i].getCurrentNumOfModels();
        AVLTree<ModelElement> sub_models = cars_source[i].getModlesTree();
        ModelElement sub_models_source[numOfModels];
        sub_models.inorderNObjects(sub_models_source, numOfModels);
        for (int i = 0; i < sub_model_amount && index < numOfModels; i++) {
            types_target[index] = sub_models_source[i].getTypeId();
            models_target[index] = sub_models_source[i].getModel();
            index++;
        }
    }

    //reread from models
    for (int i = index; i < numOfModels && index < numOfModels; i++) {
        types_target[index] = models_source[i].getTypeId();
        models_target[index] = models_source[i].getModel();
        index++;
    }
    return SUCCESS;
}

CarDealershipManager::~CarDealershipManager()
{
    this->resetCarsTree_.clear();
    this->carsTree_.clear();
    this->modelsTree_.clear();
    this->salesTree_.clear();
}


#endif /* CAR_DEALERSHIP_MANAGER_H */