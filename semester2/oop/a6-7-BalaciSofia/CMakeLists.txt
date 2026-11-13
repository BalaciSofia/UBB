cmake_minimum_required(VERSION 3.30)
project(a6_7_BalaciSofia)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(a6_7_BalaciSofia
    main.cpp
    controller_admin.cpp
    controller_user.cpp
    domain.cpp
    repo.cpp
    ui.cpp
    controller_admin.h
    controller_user.h
    domain.h
    repo.h
    ui.h
        domain.cpp
)
