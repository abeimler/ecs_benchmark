cmake_minimum_required (VERSION 3.0)
project(Ginseng)

file(GLOB_RECURSE ginseng_SOURCES include/ginseng/*)
add_library(ginseng INTERFACE)
set_property(TARGET ginseng PROPERTY INTERFACE_SOURCES ${ginseng_SOURCES})
target_include_directories(ginseng INTERFACE include)

add_executable(test_ginseng EXCLUDE_FROM_ALL src/main.cpp src/test.cpp src/catch.hpp src/test_tags.cpp)
set_property(TARGET test_ginseng PROPERTY CXX_STANDARD 14)
target_link_libraries(test_ginseng ginseng)
