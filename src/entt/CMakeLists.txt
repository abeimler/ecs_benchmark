# add dependencies
cpmaddpackage("gh:skypjack/entt@3.10.1")

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-entt STATIC
        # NOTE: add source files here
        entt/systems/ComflabSystem.h
        entt/systems/ComflabSystem.cpp
        entt/systems/MoreComplexSystem.h
        entt/systems/MoreComplexSystem.cpp
        entt/systems/MovementSystem.h
        entt/systems/MovementSystem.cpp
        entt/entities/EntityFactory.h
        entt/entities/EntityFactory.cpp
        entt/EnttApplication.h
        entt/EnttApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::entt ALIAS ${CMAKE_PROJECT_NAME}-example-entt)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-entt
        INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entt PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entt PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-entt PUBLIC EnTT)