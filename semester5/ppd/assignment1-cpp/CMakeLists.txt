cmake_minimum_required(VERSION 3.30)
project(assignment1_cpp)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

# common/*.cpp (FileManager, RandomNumberGenerator) and the other .cpp files of each version
# are included from its main.cpp

# static allocation version
add_executable(assignment1_cpp static/main.cpp)
target_link_libraries(assignment1_cpp Threads::Threads)

# dynamic allocation version
add_executable(assignment1_cpp_dynamic dynamic/main.cpp)
target_link_libraries(assignment1_cpp_dynamic Threads::Threads)
