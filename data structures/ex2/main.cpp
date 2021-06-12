#include <iostream>
#include "Dynamic_Array.h"
#include "Agency.h"
#include "Union_Find.h"
#include "Rank_Tree.h"
#include "Car_Agencies_Manager.h"
#ifdef __cplusplus

class UniteIntFunc {
public:
    Agency* operator()(Agency& a, Agency& b)
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
    void merge_cars(CarElement *a, int na, CarElement *b, int nb, CarElement *c){
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
    void merge_sales(SaleElement *a, int na, SaleElement *b, int nb, SaleElement *c){
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

};
void test1()
{
    auto dar = new DynamicArray<Agency>();
    dar->add(new Agency());
    dar->add(new Agency());
    delete dar;
}

void test2()
{
    auto u = new UnionFind<Agency>();

    //Agency *na = nullptr;
    for (int i = 0; i < 5; ++i) {
        //na = new Agency();
        u->makeSet(new Agency());
        //na = nullptr;
        u->printElements();
    }


    std::cout << "part 1: unite 0,1\n";
    u->Union(0, 1, UniteIntFunc());
    u->print();

    std::cout << "part 2: unite 2,3\n";
    u->Union(2, 3, UniteIntFunc());
    u->print();

    std::cout << "part 3: unite 3,4\n";
    u->Union(3, 4, UniteIntFunc());
    u->print();

    std::cout << "part 4: unite 1,2\n";
    u->Union(1, 2, UniteIntFunc());
    u->print();

    std::cout << "part 5: \n";
    std::cout << "the root parent is: " << u->findIdentifier(1) << "\n";
    u->print();
    u->printElements();

    delete u;
    std::cout << "\n end!";
}

void test3()
{
    RankTree<int> tree;
    tree.insert(new int(7));
    tree.insert(new int(1));
    tree.insert(new int(3));
    tree.insert(new int(2));
    tree.insert(new int(4));
    tree.insert(new int(5));
    tree.insert(new int(6));

    int b[5];
    tree.getInOrder(b, 5);

    int *a = tree.findByRank(3);
}

void test4()
{
    //checking leaks for adding cars
    std::cout<<"           Test 4:\n";
    Car_Agencies_Manager am;
    am.AddAgency(); // agency 0
    am.AddAgency(); // agency 1
    am.AddAgency(); // agency 2
    std::cout<<"           -selling cars first time:\n";
    am.SellCar(0,0,1);
    am.SellCar(0,1,2);
    am.SellCar(0,2,3);
    am.SellCar(2,2,6);
    std::cout<<"           -selling cars second time:\n";
    am.SellCar(0,1,2);
    am.SellCar(0,2,33);
    am.SellCar(2,2,64);
    std::cout<<"           no prints so far? ok:)\n";
}

void test5()
{
    //checking leaks for adding cars
    std::cout<<"           Test 4:\n";
    Car_Agencies_Manager am;
    am.AddAgency(); // agency 0
    am.AddAgency(); // agency 1
    std::cout<<"           -selling cars ad agency 0,1 first time:\n";
    am.SellCar(0,0,1);
    am.SellCar(0,1,2);
    am.SellCar(0,2,3);
    am.SellCar(1,2,6);
    std::cout<<"           -selling cars second time at agency 0:\n";
    am.SellCar(0,1,2);
    am.SellCar(0,2,33);

    am.UniteAgencies(0,1);
    std::cout<<"           no prints so far? ok:)\n";

}

void test6()
{

}

void test7()
{

}

int main(int argc, const char **argv)
{
    test1(); //dynamic array
    test2(); //union find
    test3(); //rank tree leaks
    test4(); //leaks at selling cars - (only leaks)
    test5();
    return 0;


}

#endif