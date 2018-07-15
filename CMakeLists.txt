cmake_minimum_required(VERSION 3.10)
project(c_off_heap C)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/vectorized)

add_subdirectory(test)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(c_off_heap SHARED vectorized/column_vector.c)
