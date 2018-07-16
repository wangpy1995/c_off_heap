#link_directories(${PROJECT_SOURCE_DIR}/bin)

add_executable(demo
        ../execution/vectorized/column_vector.c
        ../execution/filter/_SIMILAR.c
        ../execution/filter/base_filters.cc
        ../execution/filter/binary_filters.cc
        test.cc)

#target_link_libraries(demo c_off_heap)