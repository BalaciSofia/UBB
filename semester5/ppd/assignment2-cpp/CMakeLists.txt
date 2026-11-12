cmake_minimum_required(VERSION 3.30)
project(assignment2_cpp)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

# the other .cpp files (FileManager, RandomNumberGenerator, Convolution, ...) are included from main.cpp

# dynamic allocation version (the only one required for lab 2)
add_executable(assignment2_cpp main.cpp)
target_link_libraries(assignment2_cpp Threads::Threads)
