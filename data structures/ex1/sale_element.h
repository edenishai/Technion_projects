#ifndef SALE_ELEMENT_H
#define SALE_ELEMENT_H

class SaleElement {
public:
    SaleElement(int typeID): typeID_(typeID), modelID_(0), maxSales_(0) {}
    SaleElement(const SaleElement& element);
    int getTypeID() const { return typeID_; }

private:
    int typeID_;
    int modelID_;
    int maxSales_;
};

SaleElement::SaleElement(const SaleElement& element):
    typeID_(element.typeID_), modelID_(element.modelID_), maxSales_(element.maxSales_) {}

#endif /* SALE_ELEMENT_H */