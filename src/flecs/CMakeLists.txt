# add dependencies
CPMAddPackage(
        NAME flecs
        VERSION 2.4.8
        GITHUB_REPOSITORY SanderMertens/flecs
        # TODO: set current version, use master (release 1.1.2 is outdated)
        GIT_TAG master
        OPTIONS
        "FLECS_STATIC_LIBS ON"
        "FLECS_SHARED_LIBS OFF"
        "FLECS_DEVELOPER_WARNINGS OFF"
)

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-flecs STATIC
        # NOTE: add source files here
        flecs/systems/DataSystem.h
        flecs/systems/DataSystem.cpp
        flecs/systems/MoreComplexSystem.h
        flecs/systems/MoreComplexSystem.cpp
        flecs/systems/MovementSystem.h
        flecs/systems/MovementSystem.cpp
        flecs/entities/EntityFactory.h
        flecs/entities/EntityFactory.cpp
        flecs/FlecsApplication.h
        flecs/FlecsApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::flecs ALIAS ${CMAKE_PROJECT_NAME}-example-flecs)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-flecs
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-flecs PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-flecs PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-flecs PUBLIC flecs_static)