# add dependencies
CPMAddPackage(
        NAME entityx
        VERSION 1.1.2
        GITHUB_REPOSITORY alecthomas/entityx
        # TODO: set current version, use master (release 1.1.2 is outdated)
        GIT_TAG master
        OPTIONS
        "ENTITYX_DT_TYPE float"
        "ENTITYX_MAX_COMPONENTS 64"
        "ENTITYX_BUILD_SHARED OFF"
        "ENTITYX_RUN_BENCHMARKS OFF"
        "ENTITYX_BUILD_TESTING OFF"
)
target_compile_options(entityx PUBLIC $<$<C_COMPILER_ID:Clang,GNU>:-Wno-deprecated-declarations -Wno-ambiguous-reversed-operator>)
target_compile_options(entityx PUBLIC $<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-deprecated-declarations -Wno-ambiguous-reversed-operator>)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-example-myecs"
add_library(ecs-benchmark-example-entityx STATIC
        # NOTE: add source files here
        entityx/systems/DataSystem.h
        entityx/systems/DataSystem.cpp
        entityx/systems/MoreComplexSystem.h
        entityx/systems/MoreComplexSystem.cpp
        entityx/systems/MovementSystem.h
        entityx/systems/MovementSystem.cpp
        entityx/entities/EntityFactory.h
        entityx/entities/EntityFactory.cpp
        entityx/EntityXApplication.h
        entityx/EntityXApplication.cpp)
add_library(ecs-benchmark::example::entityx ALIAS ecs-benchmark-example-entityx)

target_include_directories(
        ecs-benchmark-example-entityx
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-entityx PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-entityx PUBLIC ecs-benchmark-base)

target_compile_definitions(ecs-benchmark-example-entityx PUBLIC ENTITYX_MAJOR_VERSION=${ENTITYX_MAJOR_VERSION})
target_compile_definitions(ecs-benchmark-example-entityx PUBLIC ENTITYX_MINOR_VERSION=${ENTITYX_MINOR_VERSION})
target_compile_definitions(ecs-benchmark-example-entityx PUBLIC ENTITYX_PATCH_VERSION=${ENTITYX_PATCH_VERSION})

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-entityx PUBLIC entityx)
if (entityx_ADDED)
    target_include_directories(ecs-benchmark-example-entityx SYSTEM PUBLIC ${entityx_SOURCE_DIR})
endif ()

target_compile_options(ecs-benchmark-example-entityx INTERFACE $<$<CXX_COMPILER_ID:Clang,GNU>:-Wno-deprecated-declarations -Wno-ambiguous-reversed-operator>)
