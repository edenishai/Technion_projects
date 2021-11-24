#include "CarDealershipManager.h"

CarDealershipManager::CarDealershipManager() :
        resetCarsTree_(new AVLTree<ResetCarElement>), carsTree_(new AVLTree<CarElement>),
        modelsTree_(new AVLTree<ModelElement>), salesTree_(new AVLTree<SaleElement>),upper_bound(0)
{}

//toDo: null check
StatusType CarDealershipManager::AddCarType(int typeID, int numOfModels)
{
    if (numOfModels <= 0 || typeID <= 0)
        return INVALID_INPUT;
    auto *carElement = new CarElement(typeID, numOfModels);

    if (carsTree_->find(carElement) != nullptr) {
        delete carElement;
        return FAILURE;
    }
    /*
     * SaleElement *saleElement = new SaleElement(typeID);
     salesTree_->insert(saleElement);

     carElement->carSales_ = saleElement;*/
    carsTree_->insert(carElement);

    auto *reset_elem = new ResetCarElement(typeID, numOfModels);
    resetCarsTree_->insert(reset_elem);
    upper_bound+=numOfModels;
    return SUCCESS;
}

StatusType CarDealershipManager::RemoveCarType(int typeID)
{
    if (typeID <= 0)
        return INVALID_INPUT;
    CarElement to_find = CarElement(typeID);
    CarElement *toDelete = carsTree_->find(&to_find);
    if (!toDelete)
        return FAILURE;

    ResetCarElement to_remove(typeID);
    resetCarsTree_->remove(&to_remove);

    for (int i = 0; i < toDelete->getNumOfModels(); ++i) {
        if (toDelete->carSales_[i])
            salesTree_->remove(toDelete->carSales_[i]);
    }
    for (int i = 0; i < toDelete->getNumOfModels(); i++) {
        if (toDelete->carModels_[i])
            modelsTree_->remove(toDelete->carModels_[i]);
    }
    toDelete->clear();
    carsTree_->remove(toDelete);
    return SUCCESS;
}

StatusType CarDealershipManager::SellCar(int typeID, int modelID)
{
    if (typeID <= 0 || modelID < 0)
        return INVALID_INPUT;

    //find car element
    CarElement to_find = CarElement(typeID);
    CarElement *carType = carsTree_->find(&to_find);

    if (!carType || carType->getNumOfModels() <= modelID) //if dealership doesn't offer this car
        return FAILURE;

    //check if car- model was sold in the past:
    ResetCarElement to_find_1 = ResetCarElement(typeID, modelID);
    ResetCarElement *resetCarType = resetCarsTree_->find(&to_find_1);

    if (resetCarType) { //if car has unsold models
        ModelElement to_find_2 = ModelElement(typeID, modelID);
        ModelElement *resetModelType = resetCarType->resetModelsTree_->find(&to_find_2);
        if (resetModelType) { // if this models was never sold

            // add to the tree of sold models
            auto *newModel = new ModelElement(typeID, modelID, SELL_POINTS);
            modelsTree_->insert(newModel);
            carType->connectModelElement(newModel, modelID);

            //update sales tree
            auto *newSaleElement = new SaleElement(typeID, modelID, SELL_POINTS);
            salesTree_->insert(newSaleElement);
            carType->connectSaleElement(newSaleElement, modelID);

            //update unsold cars tree
            auto to_remove_2 = ModelElement(typeID, modelID);
            resetCarType->resetModelsTree_->remove(&to_remove_2);
            if (resetCarType->resetModelsTree_->currentSize() == 0)
                resetCarsTree_->remove(resetCarType);

            return SUCCESS;
        }
    }
    //if not looking at first time sell

    //update model tree:
    auto *newModel = new ModelElement
            (typeID, modelID, carType->carModels_[modelID]->getGrade() + SELL_POINTS);
    //  by removing old model
    modelsTree_->remove((carType->carModels_[modelID]));
    //  and inset new one
    carType->connectModelElement(newModel, modelID);
    modelsTree_->insert(newModel);

    //update sales tree:
    int new_sales_amount = carType->carSales_[modelID]->getSales();
    new_sales_amount++;
    auto *newSaleElement = new SaleElement(typeID, modelID, new_sales_amount);
    if (*newSaleElement > *(carType->carSales_[modelID])) {
        salesTree_->remove((carType->carSales_[modelID]));
        salesTree_->insert(newSaleElement);
        carType->connectSaleElement(newSaleElement, modelID);
    }
    return SUCCESS;
}

StatusType CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
{
    if (typeID <= 0 || modelID < 0 || t < 0)
        return INVALID_INPUT;

    CarElement *tmp = new CarElement(typeID);
    CarElement *car = this->carsTree_->find(&(*tmp));
    delete tmp;
    if (car == nullptr)
        return FAILURE;

    ModelElement *model_old = car->getModel(modelID);
    if (model_old == nullptr) {
        return FAILURE;
    }

    //out with the old
    ModelElement *model_new = model_old->clone();
    modelsTree_->remove(model_old);
    //in with the new :)
    model_new->reciveComplaint(t);
    modelsTree_->insert(model_new);
    car->connectModelElement(model_new, modelID);
    return SUCCESS;
}

StatusType CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID)
{
    if (typeID < 0)
        return INVALID_INPUT;

    if (typeID > 0) {
        auto to_find_0 = CarElement(typeID);
        CarElement *car_element = this->carsTree_->find(&to_find_0);

        if (!car_element)
            return FAILURE;

        SaleElement *best_seller_model = car_element->getBestSeller();
        if (best_seller_model == nullptr)
            *modelID = 0;
        else
            *modelID = best_seller_model->getModelId();
    } else {
        if(this->carsTree_->currentSize() == 0)
        {
            return FAILURE;
        }
        if (this->salesTree_->currentSize() == 0) {
            *modelID = 0;
        } else {
            SaleElement *best_seller_model = this->salesTree_->getMostRight();
            *modelID = best_seller_model->getModelId();
        }
    }
    return SUCCESS;
}

StatusType CarDealershipManager::GetWorstModels(int numOfModels, int *types_target, int *models_target)
{
    if (numOfModels <= 0) {
        return INVALID_INPUT;
    }
    if(numOfModels > upper_bound)
    {
        return FAILURE;
    }
    ModelElement models_source[numOfModels];
    int models_count = modelsTree_->getInOrder(models_source, min(numOfModels, modelsTree_->currentSize()));

    ResetCarElement reset_cars[numOfModels];
    this->resetCarsTree_->getInOrder(reset_cars, numOfModels);

    ModelElement reset_models_source[numOfModels];
    int reset_models_count = 0;
    for (int i = 0; reset_models_count <= numOfModels && i < carsTree_->currentSize() && i < numOfModels; ++i) {
        ModelElement *ptr = reset_models_source + reset_models_count;
        reset_models_count += reset_cars[i].resetModelsTree_->getInOrder(ptr, numOfModels);
    }

    for (int i = 0; i < numOfModels; i++) {
        reset_cars[i].resetModelsTree_ = nullptr;
    }

    int totalNumOfModels = models_count + reset_models_count;

    if (totalNumOfModels < numOfModels)

        return FAILURE;

    reset_models_count = std::min(reset_models_count, numOfModels);
    ModelElement all_models_source[std::min(models_count + reset_models_count, numOfModels)];

    merge(models_source, models_count, reset_models_source, reset_models_count, all_models_source);

    for (auto j = 0; j < numOfModels; j++) {
        types_target[j] = all_models_source[j].getTypeId();
        models_target[j] = all_models_source[j].getModel();
    }
    return SUCCESS;
}

CarDealershipManager::~CarDealershipManager()
{
    //cout << "in dtor \n";
    delete resetCarsTree_;
    delete carsTree_;
    delete modelsTree_;
    delete salesTree_;
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
    if (!this->carsTree_->checkTree())
        cout << "carsTree NOT OK - ";
    if (!this->modelsTree_->checkTree())
        cout << "carsTree NOT OK - ";
    if (!this->salesTree_->checkTree())
        cout << "carsTree NOT OK - ";
    if (!this->carsTree_->checkTree())
        cout << "carsTree NOT OK - ";
}

