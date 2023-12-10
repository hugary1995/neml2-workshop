cmake_minimum_required(VERSION 3.14)

PROJECT(NEML2WORKSHOP)

# c++ 17 support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "" OFF)
option(NEML2_DOC "" OFF)
add_subdirectory(neml2)

option(DEVEL "Development mode: Build the examples folder instead of the playground folder")

if(DEVEL)
  message(STATUS "Development mode: building examples from the examples folder")
  set(FOLDER "${NEML2WORKSHOP_SOURCE_DIR}/examples")
else()
  message(STATUS "Workshop mode: building examples from the playground folder")
  set(FOLDER "${NEML2WORKSHOP_SOURCE_DIR}/playground")
endif()

macro(add_workshop_example ex_name)
  add_executable(${ex_name} "${FOLDER}/${ex_name}.cxx")
  target_include_directories(${ex_name} PUBLIC examples)
  target_link_libraries(${ex_name} workshop)
  set_target_properties(${ex_name} PROPERTIES OUTPUT_NAME "${ex_name}-${CMAKE_BUILD_TYPE}")
endmacro()

# workshop utils
add_library(
  workshop
  SHARED
  "${FOLDER}/workshop.cxx"
  "${FOLDER}/FlyingBall.cxx"
  "${FOLDER}/ParametrizedFlyingBall.cxx"
  "${FOLDER}/BallLauncher.cxx"
  "${FOLDER}/CustomIsotropicHardening.cxx"
  "${FOLDER}/ArrheniusLaw.cxx"
)
target_include_directories(workshop PUBLIC examples)
target_link_libraries(workshop PUBLIC neml2)
target_compile_definitions(workshop PUBLIC ROOT_DIR="${FOLDER}")

# register examples
add_workshop_example(ex01)
add_workshop_example(ex02)
add_workshop_example(ex03)
add_workshop_example(ex04)
add_workshop_example(ex05)
add_workshop_example(ex06)
add_workshop_example(ex07)
add_workshop_example(ex08)
add_workshop_example(ex09)
add_workshop_example(ex10)
add_workshop_example(ex11)
add_workshop_example(ex12)
add_workshop_example(ex13)
add_workshop_example(ex14)
add_workshop_example(ex15)
add_workshop_example(ex16)
add_workshop_example(ex17)
add_workshop_example(ex18)
add_workshop_example(ex19)
