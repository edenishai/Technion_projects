#ifndef CAR_ELEMENT_H
#define CAR_ELEMENT_H

#include "sale_element.h"
#include "model_element.h"

class CarElement {
public:

    SaleElement **carSales_;

    ModelElement **carModels_;

    CarElement(int typeID, int numOfModels);

    CarElement(int typeID);

    ~CarElement();

    int getTypeID() const
    { return typeID_; }

    int getNumOfModels() const
    { return numOfModels_; }

    bool operator>(const CarElement &other) const;

    bool operator<(const CarElement &other) const;

    bool operator==(const CarElement &other) const;
  
    SaleElement *getBestSeller();

    ModelElement *getModel(int i);

    void connectModelElement(ModelElement* m,int index);

    void connectSaleElement(SaleElement* m,int index);

    void clear();

    void flatDelete();


private:
    int typeID_;
    int numOfModels_;
    int best_seller_ = 0;


};

#endif /* CAR_ELEMENT_H */
