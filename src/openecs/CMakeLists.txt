# add dependencies
CPMAddPackage(
        NAME OpenECS
        GITHUB_REPOSITORY Gronis/OpenEcs
        # TODO: set current version, use master (no release version)
        GIT_TAG master
        DOWNLOAD_ONLY True
)
if(OpenECS_ADDED)
    add_library(OpenECS INTERFACE)
    target_include_directories(OpenECS SYSTEM INTERFACE ${OpenECS_SOURCE_DIR}/include)
endif()

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-openecs STATIC
        # NOTE: add source files here
        openecs/systems/ComflabSystem.h
        openecs/systems/ComflabSystem.cpp
        openecs/systems/MoreComplexSystem.h
        openecs/systems/MoreComplexSystem.cpp
        openecs/systems/MovementSystem.h
        openecs/systems/MovementSystem.cpp
        openecs/entities/EntityFactory.h
        openecs/entities/EntityFactory.cpp
        openecs/OpenECSApplication.h
        openecs/OpenECSApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::openecs ALIAS ${CMAKE_PROJECT_NAME}-example-openecs)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-openecs
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-openecs PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-openecs PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-openecs PUBLIC OpenECS)