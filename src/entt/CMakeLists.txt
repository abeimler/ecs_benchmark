# add dependencies
CPMAddPackage(
        NAME EnTT
        VERSION 3.11.1
        GITHUB_REPOSITORY skypjack/entt
        OPTIONS
        "ENTT_BUILD_TESTING OFF"
        "ENTT_BUILD_DOCS OFF"
)

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(${CMAKE_PROJECT_NAME}-example-entt STATIC
        # NOTE: add source files here
        entt/components/StablePositionComponent.h
        entt/systems/DataSystem.h
        entt/systems/DataSystem.cpp
        entt/systems/MoreComplexSystem.h
        entt/systems/MoreComplexSystem.cpp
        entt/systems/MovementSystem.h
        entt/systems/StableMovementSystem.cpp
        entt/systems/StableMovementSystem.h
        entt/systems/MovementSystem.cpp
        entt/systems/RuntimeDataSystem.h
        entt/systems/RuntimeDataSystem.cpp
        entt/systems/RuntimeMoreComplexSystem.h
        entt/systems/RuntimeMoreComplexSystem.cpp
        entt/systems/RuntimeMovementSystem.h
        entt/systems/RuntimeMovementSystem.cpp
        entt/systems/StableRuntimeMovementSystem.h
        entt/systems/StableRuntimeMovementSystem.cpp
        entt/systems/StableRuntimeMovementSystem.h
        entt/systems/StableRuntimeMovementSystem.cpp
        entt/systems/GroupMoreComplexSystem.h
        entt/systems/GroupMoreComplexSystem.cpp
        entt/systems/GroupMovementSystem.h
        entt/systems/GroupMovementSystem.cpp
        entt/entities/EntityFactory.h
        entt/entities/EntityFactory.cpp
        entt/entities/StableEntityFactory.h
        entt/entities/StableEntityFactory.cpp
        entt/EnttApplication.h
        entt/EnttApplication.cpp
        entt/EnttGroupApplication.h
        entt/EnttGroupApplication.cpp
        entt/EnttRuntimeApplication.h
        entt/EnttRuntimeApplication.cpp
        entt/StableEnttApplication.h
        entt/StableEnttApplication.cpp
        entt/StableEnttRuntimeApplication.h
        entt/StableEnttRuntimeApplication.cpp
        entt/entt.h)
add_library(${CMAKE_PROJECT_NAME}::example::entt ALIAS ${CMAKE_PROJECT_NAME}-example-entt)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-entt
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entt PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-entt PUBLIC ${CMAKE_PROJECT_NAME}-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(${CMAKE_PROJECT_NAME}-example-entt PUBLIC EnTT)