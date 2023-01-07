# add dependencies
CPMAddPackage(
        NAME flecs
        VERSION 3.1.3
        GITHUB_REPOSITORY SanderMertens/flecs
        OPTIONS
        "FLECS_STATIC_LIBS ON"
        "FLECS_SHARED_LIBS OFF"
        "FLECS_DEVELOPER_WARNINGS OFF"
)

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-example-myecs"
add_library(ecs-benchmark-example-flecs STATIC
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
add_library(ecs-benchmark::example::flecs ALIAS ecs-benchmark-example-flecs)

target_include_directories(
        ecs-benchmark-example-flecs
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-flecs PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-flecs PUBLIC ecs-benchmark-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-flecs PUBLIC flecs_static)