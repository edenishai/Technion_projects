cmake_minimum_required(VERSION 3.17)
project(Data_Struct_1_HW_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DS1
        main.cpp
        library2.h
        library2.cpp
        CarAgenciesManager.h
        union_find.h
        car_type.h
        sold_type.h
        Rank_tree.h
        agency_type.h
        DynamicArray.h)
