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
    Agency &agency = agencies_->findElement(agencyID);
    agency.sellCar(typeID, k);
    return SUCCESS;

}

StatusType Car_Agencies_Manager::UniteAgencies(int agencyID1, int agencyID2)
{
    agencies_->Union(agencyID1, agencyID2, UniteAgenciesFunc());
    return FAILURE;
}

StatusType Car_Agencies_Manager::GetIthSoldType(int agencyID, int i, int *res)
{
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
    // unite sales into one array
   /** SaleElement a_sales[a.sales_->currentSize()];
    a.sales_->getInOrder(a_sales, a.sales_->currentSize());
    SaleElement b_sales[b.sales_->currentSize()];
    b.sales_->getInOrder(b_sales, b.sales_->currentSize());*/

    // unite cars into one array
    /**CarElement a_cars[a.cars_->currentSize()];
    a.cars_->getInOrder(a_cars, a.cars_->currentSize());
    CarElement b_cars[b.cars_->currentSize()];
    b.cars_->getInOrder(b_cars, b.cars_->currentSize());*/

    return new Agency();
}
void Car_Agencies_Manager::UniteAgenciesFunc::merge(CarElement a[], int na, CarElement b[], int nb, CarElement c[])
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