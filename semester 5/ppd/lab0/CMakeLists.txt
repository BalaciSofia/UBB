cmake_minimum_required(VERSION 3.30)
project(lab0)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab0 main.cpp
        FileManager.cpp
        FileManager.h
        RandomNumberGenerator.cpp
        RandomNumberGenerator.h)

# Link the MinGW runtime statically so lab0.exe runs from any terminal,
# without needing the MinGW bin folder in PATH
if (MINGW)
    target_link_options(lab0 PRIVATE -static)
endif ()
