link_directories(${PROJECT_SOURCE_DIR}/bin)

add_executable(demo test.cc ArrowTest.cc ArrowTest.h)

target_link_libraries(demo c_off_heap arrow)