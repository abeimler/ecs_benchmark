set(INCLUDE_DIR "include") # must be relative paths
add_library(${CMAKE_PROJECT_NAME}-base INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/base/components/DataComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/components/DirectionComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/components/PositionComponent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/DataSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/MoreComplexSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/MovementSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/System.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/base/entities/EntityFactory.h
        )
add_library(${CMAKE_PROJECT_NAME}::base ALIAS ${CMAKE_PROJECT_NAME}-base)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-base
        INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-base INTERFACE project_warnings project_options)
