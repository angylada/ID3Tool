cmake_minimum_required(VERSION 3.16)
project(c_test C)

set(CMAKE_C_STANDARD 99)

add_executable(c_test main.c fileReader.h fileReader.c hexOps.h hexOps.c)