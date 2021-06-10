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
    AgencyType* c = new AgencyType();
    u->Makeset(c);
    c = nullptr;

    AgencyType* d = new AgencyType();
    u->Makeset(d);
    d = nullptr;

    delete u;

    return 0 ;









}

#endif
