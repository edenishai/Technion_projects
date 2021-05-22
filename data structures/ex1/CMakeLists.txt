cmake_minimum_required(VERSION 3.17)
project(Data_Struct_1_HW_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Data_Struct_1_HW_1
        main.cpp
        AVL_tree.h
        car_element.h
        car_element.cpp
        CarDealershipManager.h
        CarDealershipManager.cpp
        model_element.h
        model_element.cpp
        library.cpp
        library.h
        reset_car_element.h
        reset_car_element.cpp
        sale_element.h
        sale_element.cpp)
