cmake_minimum_required(VERSION 3.10)
project(c_off_heap)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_STANDARD 11)

#set(CMAKE_CXX_FLAGS_DEBUG "-mavx2 -Wall -D__AVX2__ -D__AVX__")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -mavx2 -D__AVX2__ -D__AVX__")

set(CMAKE_CXX_FLAGS "-mavx2 -Wall -D__AVX2__ -D__AVX__ -pthread -fstack-protector-all")

#set(CMAKE_C_FLAGS_DEBUG "-mavx2 -D__AVX2__ -D__AVX__")
#set(CMAKE_C_FLAGS_RELEASE "-O3 -mavx2 -D__AVX2__ -D__AVX__")

include_directories(
        ${PROJECT_SOURCE_DIR}/third_party
        ${PROJECT_SOURCE_DIR}/execution
        ${PROJECT_SOURCE_DIR}/execution/vectorized
        ${PROJECT_SOURCE_DIR}/execution/filter
        ${PROJECT_SOURCE_DIR}/execution/utils
        ${PROJECT_SOURCE_DIR}/execution/jni)

add_subdirectory(test)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(c_off_heap SHARED
        execution/row/row.h
        execution/vectorized/column_vector.c
        execution/filter/_SIMILAR.c
        execution/filter/filters.cc execution/jni/git_wpy_format_vector_OffHeapUtils.c)
