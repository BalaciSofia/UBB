cmake_minimum_required(VERSION 3.30)
project(t1_BalaciSofia_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1_BalaciSofia_1
    main.cpp
        domain.cpp
        domain.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        ui.cpp
        ui.h)
