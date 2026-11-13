cmake_minimum_required(VERSION 3.30)
project(practice_test2_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(practice_test2_1 main.cpp
        Building.cpp
        Building.h
        Block.cpp
        Block.h
        House.cpp
        House.h
        controller.cpp
        controller.h
        Ui.cpp
        Ui.h)
