# add dependencies
CPMAddPackage(
        NAME ginseng
        VERSION 1.1
        GITHUB_REPOSITORY apples/ginseng
        # TODO: set current version, use master (release 1.1 is outdated)
        GIT_TAG master
)

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-ginseng STATIC
        # NOTE: add source files here
        ginseng/systems/ComflabSystem.h
        ginseng/systems/ComflabSystem.cpp
        ginseng/systems/MoreComplexSystem.h
        ginseng/systems/MoreComplexSystem.cpp
        ginseng/systems/MovementSystem.h
        ginseng/systems/MovementSystem.cpp
        ginseng/entities/EntityFactory.h
        ginseng/entities/EntityFactory.cpp
        ginseng/GinsengApplication.h
        ginseng/GinsengApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::ginseng ALIAS ${CMAKE_PROJECT_NAME}-example-ginseng)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-ginseng
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-ginseng PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-ginseng PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-ginseng PUBLIC ginseng)