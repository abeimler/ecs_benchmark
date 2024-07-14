# https://github.com/Gronis/OpenEcs
cmake_minimum_required(VERSION 3.24)

project(OpenEcs
        VERSION 0.1.101
        HOMEPAGE_URL "https://github.com/Gronis/OpenEcs"
        LANGUAGES C CXX)

add_library(OpenEcs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/ecs.h)
target_include_directories(OpenEcs INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")
