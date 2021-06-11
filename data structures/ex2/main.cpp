#include <iostream>
#include "Dynamic_Array.h"
#include "Agency.h"
#include "Union_Find.h"
#include "Rank_Tree.h"

#ifdef __cplusplus

class UniteIntFunc {
public:
    Agency* operator()(Agency& a, Agency& b)
    {
        return new Agency();
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

    int *a = tree.findByRank(3);
}

void test4()
{

}

void test5()
{

}

void test6()
{

}

void test7()
{

}

int main(int argc, const char **argv)
{
    test1();
    test2();
    test3();

    return 0;


}

#endif
