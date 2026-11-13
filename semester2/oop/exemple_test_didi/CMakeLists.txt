cmake_minimum_required(VERSION 3.30)
project(exemple_test_didi)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(exemple_test_didi
    BMI.cpp
    BMI.h
    BP.cpp
    BP.h
    main.cpp
    MedicalAnalysis.cpp
    MedicalAnalysis.h
    Person.cpp
    Person.h
    Service.cpp
    Service.h
    UI.cpp
    UI.h)
