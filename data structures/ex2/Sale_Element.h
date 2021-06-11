//
// Created by ASUS on 11/06/2021.
//

#ifndef DATA_STRUCT_1_HW_1_SALE_ELEMENT_H
#define DATA_STRUCT_1_HW_1_SALE_ELEMENT_H


class SaleElement {
public:

    explicit SaleElement(int typeID,int sales = 0);

    bool operator<(SaleElement& element);

    bool operator==(SaleElement& element);

    int getSales();

    int getTypeId();

    ~SaleElement() = default;

private:
    int typeID_;
    int sales_;
};


#endif //DATA_STRUCT_1_HW_1_SALE_ELEMENT_H