cmake_minimum_required(VERSION 3.30)
project(assignment4)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment4
        ExtendedTest.cpp
        App.cpp
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
