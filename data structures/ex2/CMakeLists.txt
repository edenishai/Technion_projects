cmake_minimum_required(VERSION 3.17)
project(Data_Struct_1_HW_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DS1
        main2.cpp
        library2.h library2.cpp
        Car_Agencies_Manager.h Car_Agencies_Manager.cpp
        Union_Find.h
        Dynamic_Array.h
        Car_Element.h Car_Element.cpp
        Agency.h Agency.cpp
        Rank_Tree.h
        Sale_Element.cpp Sale_Element.h)
