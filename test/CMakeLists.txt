link_directories(${PROJECT_SOURCE_DIR}/bin)

add_executable(demo test.c)

target_link_libraries(demo c_off_heap)