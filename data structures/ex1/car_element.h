#ifndef CAR_ELEMENT_H
#define CAR_ELEMENT_H

#include "sale_element.h"
#include "model_element.h"

class CarElement {
public:
    //to add compare and operators.
    CarElement(int typeID, int numOfModels);
    CarElement(int typeID): typeID_(typeID) {}
    ~CarElement();
    void setCarSales(SaleElement* carSales) { carSales_ = carSales; }
    int getTypeID() const { return typeID_; }
    int getNumOfModels() const { return numOfModels_; }
    const SaleElement& getCarSales() { return *carSales_; }
    ModelElement** getCarModels() { return carModels_; }

private:
    int typeID_;
    int numOfModels_;
    SaleElement* carSales_;
    ModelElement** carModels_;  //operator ==
};

CarElement::CarElement(int typeID, int numOfModels):
    typeID_(typeID), numOfModels_(numOfModels), carSales_(NULL), carModels_(new ModelElement*[numOfModels]) {
        for(int i; i < numOfModels; i++) {
            carModels_[i] = NULL;
        }
    }

CarElement::~CarElement() {
    delete carSales_; //???
    carSales_->getTypeID();
}

#endif /* CAR_ELEMENT_H */