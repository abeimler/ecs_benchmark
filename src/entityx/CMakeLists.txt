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


set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-entityx STATIC
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
add_library(${CMAKE_PROJECT_NAME}::example::entityx ALIAS ${CMAKE_PROJECT_NAME}-example-entityx)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-entityx
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entityx PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entityx PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-entityx PUBLIC entityx)
if (entityx_ADDED)
    target_include_directories(${CMAKE_PROJECT_NAME}-example-entityx SYSTEM PUBLIC ${entityx_SOURCE_DIR})
endif ()
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${CMAKE_PROJECT_NAME}-example-entityx PRIVATE -Wno-deprecated-declarations -Wno-ambiguous-reversed-operator)
endif ()