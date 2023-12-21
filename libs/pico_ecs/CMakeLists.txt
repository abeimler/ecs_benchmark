cmake_minimum_required(VERSION 3.24)

# https://github.com/empyreanx/pico_headers
CPMAddPackage(
        NAME pico_headers
        VERSION 2.3
        GITHUB_REPOSITORY empyreanx/pico_headers
        # TODO: set current version, use master (no release version)
        GIT_TAG main
        DOWNLOAD_ONLY True
)
if(pico_headers_ADDED)
    add_library(pico_headers INTERFACE)
    target_include_directories(pico_headers SYSTEM INTERFACE ${pico_headers_SOURCE_DIR})

    project(pico_ecs LANGUAGES C)
    add_library(pico_ecs INTERFACE ${pico_headers_SOURCE_DIR}/pico_ecs.h)
    add_library(pico_headers::pico_ecs ALIAS pico_ecs)
    target_include_directories(pico_ecs INTERFACE "$<BUILD_INTERFACE:${pico_headers_SOURCE_DIR}>")

    target_compile_definitions(pico_ecs INTERFACE $<$<CONFIG:Release>:NDEBUG>)
endif()

