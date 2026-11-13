cmake_minimum_required(VERSION 3.30)
project(cristislecture C)

set(CMAKE_C_STANDARD 11)

add_executable(cristislecture main.c
        dynamicarray.h
        dynamicarray.c)
