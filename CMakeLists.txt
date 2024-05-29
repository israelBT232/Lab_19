cmake_minimum_required(VERSION 3.26)
project(untitled3 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled3 main.c
        generate.c
        generate.h
        libs/data/func/func.h
        libs/data/func/func.c)


add_subdirectory(libs)
