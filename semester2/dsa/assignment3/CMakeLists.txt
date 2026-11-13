cmake_minimum_required(VERSION 3.30)
project(assignment3)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment3
        ExtendedTest.cpp
        App.cpp
        ExtendedTest.h
        IndexedList.cpp
        IndexedList.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h)
