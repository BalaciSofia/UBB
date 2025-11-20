cmake_minimum_required(VERSION 3.30)
project(practice_test1_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(practice_test1_1 main.cpp
        dynamicarray.h
        repo.cpp
        repo.h
        domain.cpp
        domain.h
        service.cpp
        service.h
        ui.cpp
        ui.h)
