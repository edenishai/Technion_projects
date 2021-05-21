#ifndef SALE_ELEMENT_H
#define SALE_ELEMENT_H

class SaleElement {
public:
    SaleElement(int typeID) : typeID_(typeID), modelID_(0), sales_(0)
    {}

    SaleElement(int typeID, int modelID, int sales);

    SaleElement(const SaleElement &element); 

    int getTypeID() const
    { return typeID_; }

    int getSales() const
    { return sales_; }

    bool operator>(const SaleElement &other) const;

    bool operator<(const SaleElement &other) const;

    bool operator==(const SaleElement &other) const;

    int getModelId() const;

private:
    int typeID_;
    int modelID_;
    int sales_;

};

#endif /* SALE_ELEMENT_H */
