cmake_minimum_required(VERSION 3.10)
project(c_off_heap C)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Og -mavx2 -D__AVX2__ -D__AVX__")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O3 -mavx2 -D__AVX2__ -D__AVX__")

include_directories(${PROJECT_SOURCE_DIR}/vectorized ${PROJECT_SOURCE_DIR}/execution ${PROJECT_SOURCE_DIR}/execution/filter)

add_subdirectory(test)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(c_off_heap STATIC
        vectorized/column_vector.c
        execution/filter/_SIMILAR.c
        execution/filter/_START_WITH.c
        execution/filter/_ENDS_WITH.c
        execution/filter/_CONTAINS.c
        execution/filter/_EQ.cc
        execution/filter/_GE.cc
        execution/filter/_GT.cc
        execution/filter/_IN_SET.cc
        execution/filter/_LT.cc
        execution/filter/_LE.cc)
