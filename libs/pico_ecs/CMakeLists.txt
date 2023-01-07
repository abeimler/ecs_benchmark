cmake_minimum_required(VERSION 3.24)

# add dependencies
#CPMAddPackage(
#        NAME pico_headers
#        VERSION 2.0.0
#        GITHUB_REPOSITORY empyreanx/pico_headers
#        # TODO: set current version, use master (no release version)
#        GIT_TAG main
#        DOWNLOAD_ONLY True
#)
#if(pico_headers_ADDED)
#    add_library(pico_headers INTERFACE)
#    target_include_directories(pico_headers SYSTEM INTERFACE ${pico_headers_SOURCE_DIR})
#endif()

# https://github.com/empyreanx/pico_headers
project(pico_ecs LANGUAGES C)

add_library(pico_ecs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/pico_ecs.h)
add_library(pico_headers::pico_ecs ALIAS pico_ecs)
target_include_directories(pico_ecs INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")