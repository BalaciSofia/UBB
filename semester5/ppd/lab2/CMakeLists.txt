cmake_minimum_required(VERSION 3.30)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

# each file has its own main(), so each one is its own executable
add_executable(lab2 main.cpp)
add_executable(lab2_static static.cpp)
add_executable(lab2_vector stlVector.cpp)

find_package(Threads REQUIRED)
target_link_libraries(lab2 Threads::Threads)
target_link_libraries(lab2_static Threads::Threads)
target_link_libraries(lab2_vector Threads::Threads)
