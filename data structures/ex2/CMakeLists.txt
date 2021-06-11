cmake_minimum_required(VERSION 3.17)
project(Data_Struct_1_HW_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(DS1
        main.cpp
        library2.h library2.cpp
        Car_Agencies_Manager.h
        Union_Find.h
        Car_Element.h Car_Element.cpp
        Rank_Tree.h
        Agency.h
        Dynamic_Array.h)
