/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2021                                          */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <iostream>
#include "DynamicArray.h"
#include "agency_type.h"
#include "union_find.h"

#ifdef __cplusplus


int main(int argc, const char**argv) {
    DynamicArray<AgencyType>* dar = new DynamicArray<AgencyType>();
    AgencyType* a = new AgencyType();
    dar->add(a);
    a = nullptr;
    AgencyType* b = new AgencyType();
    dar->add(b);
    b = nullptr;
    delete dar;
    ///////////////////////////////////////// good so far

    UnionFind<AgencyType>* u = new UnionFind<AgencyType>();

    AgencyType* na = nullptr;
    for (int i = 0; i < 10; ++i) {
        na = new AgencyType();
        u->Makeset(na);
        na = nullptr;
    }


    std::cout << "part 1: \n";
    u->Union(0,1);
    u->print();

    std::cout << "part 2: \n";
    u->Union(2,3);
    u->print();

    std::cout << "part 3: \n";
    u->Union(3,4);
    u->print();

    std::cout << "part 4: \n";
    u->Union(1,2);
    u->print();

    std::cout << "part 5: \n";
    std::cout<< "the root parent is: " << u->FindIdentifier(1)<<"\n";
    u->print();

    delete u;
    std::cout << "\n end!";
    return 0 ;









}

#endif
