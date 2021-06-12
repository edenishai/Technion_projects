//
// Created by ASUS on 11/06/2021.
//
#include "Car_Agencies_Manager.h"

Car_Agencies_Manager::Car_Agencies_Manager()
{
    agencies_ = new UnionFind<Agency>;
}

StatusType Car_Agencies_Manager::AddAgency()
{
    //todo: add try catch for memory leaks
    auto na = new Agency();
    agencies_->makeSet(na);
    return SUCCESS;
}

StatusType Car_Agencies_Manager::SellCar(int agencyID, int typeID, int k)
{
    if (agencies_->findIdentifier(agencyID) == agencies_->NO_PARENT) {
        return FAILURE;
    }
    Agency *agency = &(agencies_->findElement(agencyID));
    agency->sellCar(typeID, k);
    return SUCCESS;

}

StatusType Car_Agencies_Manager::UniteAgencies(int agencyID1, int agencyID2)
{
    if (agencies_->findIdentifier(agencyID1) == agencies_->DOESNT_EXIST || 
        agencies_->findIdentifier(agencyID2) == agencies_->DOESNT_EXIST) {
            return FAILURE;
    }
    agencies_->Union(agencyID1, agencyID2, UniteAgenciesFunc());
    return SUCCESS;
}

StatusType Car_Agencies_Manager::GetIthSoldType(int agencyID, int i, int *res)
{
    if (agencies_->findIdentifier(agencyID) == agencies_->DOESNT_EXIST)
        return FAILURE;
    Agency &agency = agencies_->findElement(agencyID);
    auto *res_element = agency.sales_->findByRank(i);
    if (res_element == nullptr)
        return FAILURE;
    *res = res_element->getTypeId();
    return SUCCESS;
}

Car_Agencies_Manager::~Car_Agencies_Manager()
{
    delete agencies_;
}


//////////////////////////////  Unite class
Agency *Car_Agencies_Manager::UniteAgenciesFunc::operator()(Agency &a, Agency &b)
{
    int total_amount = a.cars_->currentSize() + b.cars_->currentSize();

    // Unite sales into one array
    SaleElement a_sales[a.sales_->currentSize()];
    a.sales_->getInOrder(a_sales, a.sales_->currentSize());
    SaleElement b_sales[b.sales_->currentSize()];
    b.sales_->getInOrder(b_sales, b.sales_->currentSize());

    SaleElement total_sales[a.sales_->currentSize() + b.sales_->currentSize()];
    this->merge_sales(a_sales, a.sales_->currentSize(), b_sales, b.sales_->currentSize(), total_sales);
    //   copy elements
    SaleElement* total_sales_copies[a.sales_->currentSize() + b.sales_->currentSize()];
    for (int i = 0; i < total_amount; ++i) {
        total_sales_copies[i] = total_sales[i].clone();
    }


    // Unite cars into one array
    CarElement a_cars[a.cars_->currentSize()];
    a.cars_->getInOrder(a_cars, a.cars_->currentSize());
    CarElement b_cars[b.cars_->currentSize()];
    b.cars_->getInOrder(b_cars, b.cars_->currentSize());

    CarElement total_cars[a.cars_->currentSize() + b.cars_->currentSize()];
    this->merge_cars(a_cars, a.cars_->currentSize(), b_cars, b.cars_->currentSize(), total_cars);

    //   copy elements
    CarElement* total_cars_copies[a.cars_->currentSize() + b.cars_->currentSize()];
    for (int i = 0; i < total_amount; ++i) {
        total_cars_copies[i] = total_cars[i].clone();
    }

    auto to_return = new Agency(total_cars_copies, total_sales_copies, total_amount);
    return to_return;
}

void Car_Agencies_Manager::UniteAgenciesFunc::merge_cars(CarElement *a, int na, CarElement *b, int nb, CarElement *c)
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

void Car_Agencies_Manager::UniteAgenciesFunc::merge_sales(SaleElement *a, int na, SaleElement *b, int nb, SaleElement
*c)
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
