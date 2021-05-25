#ifndef SALE_ELEMENT_H
#define SALE_ELEMENT_H

class SaleElement {
public:
    SaleElement(int typeID = 0, int modelID = 0, int sales = 0);

    SaleElement(const SaleElement &element); 

    int getTypeID() const
    { return typeID_; }

    int getSales() const
    { return sales_; }

    bool operator>(const SaleElement &other) const;

    bool operator<(const SaleElement &other) const;

    bool operator==(const SaleElement &other) const;

    int getModelId() const;

    void flatDelete();


private:
    int typeID_;
    int modelID_;
    int sales_;

};

#endif /* SALE_ELEMENT_H */
