cmake_minimum_required(VERSION 3.30)
project(MyFixedCapBiMap CXX)

set(CMAKE_C_STANDARD 11)

add_executable(MyFixedCapBiMap
        App.cpp
        ExtendedTest.cpp
        FixedCapBiMap.cpp
        FixedCapBiMapIterator.cpp
        ShortTest.cpp
   )
