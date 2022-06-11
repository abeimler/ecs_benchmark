# add dependencies
CPMAddPackage(
        NAME EntityPlus
        VERSION 1.0
        GITHUB_REPOSITORY Yelnats321/EntityPlus
        # TODO: set current version, use master (release 1.0 is outdated)
        GIT_TAG master
        DOWNLOAD_ONLY True
)
if(EntityPlus_ADDED)
    add_library(EntityPlus INTERFACE)
    target_include_directories(EntityPlus SYSTEM INTERFACE "${EntityPlus_SOURCE_DIR}")
endif()

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-entityplus STATIC
        # NOTE: add source files here
        entityplus/systems/DataSystem.h
        entityplus/systems/DataSystem.cpp
        entityplus/systems/MoreComplexSystem.h
        entityplus/systems/MoreComplexSystem.cpp
        entityplus/systems/MovementSystem.h
        entityplus/systems/MovementSystem.cpp
        entityplus/entities/EntityFactory.h
        entityplus/entities/EntityFactory.cpp
        entityplus/EntityPlusApplication.h
        entityplus/EntityPlusApplication.cpp
        )
add_library(${CMAKE_PROJECT_NAME}::example::entityplus ALIAS ${CMAKE_PROJECT_NAME}-example-entityplus)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-entityplus
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entityplus PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entityplus PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-entityplus PUBLIC EntityPlus)