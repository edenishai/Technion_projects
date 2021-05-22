#include "CarDealershipManager.h"

CarDealershipManager::CarDealershipManager() :
        resetCarsTree_(), carsTree_(), modelsTree_(), salesTree_()
{}

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

    checkTrees();
    return SUCCESS;
}

StatusType CarDealershipManager::RemoveCarType(int typeID)
{
    if (typeID <= 0)
        return INVALID_INPUT;
    CarElement *toDelete = carsTree_.find(CarElement(typeID));
    cout<<"";
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
    checkTrees();
    return SUCCESS;
}

StatusType CarDealershipManager::SellCar(int typeID, int modelID)
{
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;
    CarElement *carType = carsTree_.find(CarElement(typeID));
    if (!carType)
        return FAILURE;
    ResetCarElement *resetCarType = resetCarsTree_.find(ResetCarElement(typeID, modelID));
    ModelElement *resetModelType = NULL;
    if (resetCarType) {
        resetModelType = resetCarType->resetModelsTree_.find(ModelElement(typeID, modelID));
        if (resetModelType) {
            ModelElement *newModel = new ModelElement(typeID, modelID, SELL_POINTS);
            carType->carModels_[modelID] = newModel;
            modelsTree_.insert(*newModel);
            SaleElement *saleElement = new SaleElement(typeID, modelID, SELL_POINTS);
            if (*saleElement > *(carType->carSales_)) {
                salesTree_.remove(*(carType->carSales_));
                carType->carSales_ = saleElement;
                salesTree_.insert(*saleElement);
            }
            resetCarType->resetModelsTree_.remove(*resetModelType);
            if (resetCarType->resetModelsTree_.currentSize() == 0)
                resetCarsTree_.remove(*resetCarType);
        }
    } else if (!resetCarType || !resetModelType) {
        ModelElement *newModel = new ModelElement(typeID, modelID,
                                                  carType->carModels_[modelID]->getGrade() + SELL_POINTS);
        modelsTree_.remove(*(carType->carModels_[modelID]));
        carType->carModels_[modelID] = newModel;
        modelsTree_.insert(*newModel);

        SaleElement *saleElement = new SaleElement(typeID, modelID, carType->carSales_->getSales() + SELL_POINTS);
        if (*saleElement > *(carType->carSales_)) {
            salesTree_.remove(*(carType->carSales_));
            carType->carSales_ = saleElement;
            salesTree_.insert(*saleElement);
        }
    }
    checkTrees();
    return SUCCESS;
}

//toDo
StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
{
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;

    CarElement *car = this->carsTree_.find(CarElement(typeID));
    if (car == nullptr)
        return FAILURE;

    ModelElement *model_old = car->getModel(modelID);
    if (model_old == nullptr)
        return FAILURE;

    //out with the old
    ModelElement *model_new = model_old->clone();
    modelsTree_.remove(*model_old);
    //in with the new :)
    model_new->reciveComplaint(t);
    modelsTree_.insert(*model_new);
    checkTrees();

    return SUCCESS;
}

//toDo
StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID)
{
    if (typeID < 0)
        return INVALID_INPUT;

    if (typeID > 0) {
        CarElement *car_element = this->carsTree_.find(CarElement(typeID));
        SaleElement *best_seller_model = car_element->carSales_;

        *modelID = best_seller_model->getModelId();
    } else {
        SaleElement &best_seller_model = this->salesTree_.getMostRight();
        *modelID = best_seller_model.getModelId();
    }
    checkTrees();
    return SUCCESS;
}

StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types_target, int *models_target)
{
    if (numOfModels <= 0) {
        return INVALID_INPUT;
    }
    ModelElement models_source[numOfModels];
    int models = modelsTree_.getInOrder(models_source, numOfModels);

    ResetCarElement reset_cars[numOfModels];
    ModelElement reset_models_source[numOfModels];
    int cars = resetCarsTree_.getInOrder(reset_cars, numOfModels);
    int reset_models, i;
    for (reset_models = i = 0;
         reset_models <= numOfModels && i < resetCarsTree_.currentSize() && i < numOfModels; ++i) {
        reset_models += reset_cars[i].resetModelsTree_.getInOrder(reset_models_source + reset_models, numOfModels);
    }

    reset_models = std::min(reset_models, numOfModels);
    ModelElement all_models_source[std::min(models + reset_models, numOfModels)];
    merge(models_source, models, reset_models_source, reset_models, all_models_source);

    for (int i = 0; i < numOfModels && i < std::min(models + reset_models, numOfModels); i++) {
        types_target[i] = all_models_source[i].getTypeId();
        models_target[i] = all_models_source[i].getModel();
    }
    checkTrees();
    return SUCCESS;
}

CarDealershipManager::~CarDealershipManager()
{

}

void CarDealershipManager::merge(ModelElement a[], int na, ModelElement b[], int nb, ModelElement c[])
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

void CarDealershipManager::checkTrees()
{
    if(!this->carsTree_.checkTree())
        cout<<"-------------------carsTree NOT OK - " ;
    if(!this->modelsTree_.checkTree())
        cout<<"-------------------modelsTree_ NOT OK - " ;
    if(!this->salesTree_.checkTree())
        cout<<"-------------------salesTree_ NOT OK - " ;
    if(!this->resetCarsTree_.checkTree())
        cout<<"-------------------resetCarsTree_ NOT OK - " ;
}
