cmake_minimum_required(VERSION 3.25)
project(c_strings C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(c_strings
        main.c
        strings_r.c
        strings_r.h)
