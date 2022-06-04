# add dependencies
CPMAddPackage(
        NAME mustache
        VERSION 0.2
        GITHUB_REPOSITORY kirillochnev/mustache
        # TODO: set current version, use master (no release version)
        GIT_TAG master
        OPTIONS
        "MUSTACHE_USE_SANITIZER OFF"
        "MUSTACHE_WARNINGS_AS_ERROR OFF"
        "MUSTACHE_BUILD_SHARED OFF"
)

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-mustache STATIC
        # NOTE: add source files here
        mustache/systems/DataSystem.h
        mustache/systems/DataSystem.cpp
        mustache/systems/MoreComplexSystem.h
        mustache/systems/MoreComplexSystem.cpp
        mustache/systems/MovementSystem.h
        mustache/systems/MovementSystem.cpp
        mustache/entities/EntityFactory.h
        mustache/entities/EntityFactory.cpp
        mustache/MustacheApplication.h
        mustache/MustacheApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::mustache ALIAS ${CMAKE_PROJECT_NAME}-example-mustache)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-mustache
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-mustache PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-mustache PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-mustache PUBLIC mustache)