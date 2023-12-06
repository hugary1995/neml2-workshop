cmake_minimum_required(VERSION 3.14)

PROJECT(NEML2WORKSHOP)

option(BUILD_TESTING "" OFF)
option(NEML2_DOC "" OFF)
add_subdirectory(neml2)

# example 1
add_executable(ex01 examples/ex01.cxx)
target_link_libraries(ex01 neml2)
