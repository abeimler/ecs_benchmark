# add dependencies
CPMAddPackage(
        NAME EntitasPP
        VERSION 1.1.0
        GITHUB_REPOSITORY abeimler/Entitas-Cpp # Some Bugfixes, Original from https://github.com/JuDelCo/Entitas-Cpp
        GIT_TAG master
        DOWNLOAD_ONLY
)
if (EntitasPP_ADDED)
    file(GLOB_RECURSE ENTITAS_SRC ${EntitasPP_SOURCE_DIR}/EntitasPP/*.cpp)
    add_library(EntitasPP STATIC ${ENTITAS_SRC})
    target_include_directories(EntitasPP PUBLIC $<BUILD_INTERFACE:${EntitasPP_SOURCE_DIR}>)
endif()


set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-entitaspp STATIC
        # NOTE: add source files here
        EntitasPP/components/DataComponent.h
        EntitasPP/components/DirectionComponent.h
        EntitasPP/components/PositionComponent.h
        EntitasPP/systems/DataSystem.h
        EntitasPP/systems/DataSystem.cpp
        EntitasPP/systems/MoreComplexSystem.h
        EntitasPP/systems/MoreComplexSystem.cpp
        EntitasPP/systems/MovementSystem.h
        EntitasPP/systems/MovementSystem.cpp
        EntitasPP/entities/EntityFactory.h
        EntitasPP/entities/EntityFactory.cpp
        EntitasPP/EntitasPPApplication.h
        EntitasPP/EntitasPPApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::entitaspp ALIAS ${CMAKE_PROJECT_NAME}-example-entitaspp)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-entitaspp
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entitaspp PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entitaspp PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-entitaspp PUBLIC EntitasPP)