cmake_minimum_required(VERSION 3.30)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab5 main.cpp FA.cpp SymbolTable.cpp Scanner.cpp)

# lets main.cpp find tokens.txt, fa/ and tests/ in this folder
target_compile_definitions(lab5 PRIVATE PROJECT_DIR="${CMAKE_SOURCE_DIR}")
