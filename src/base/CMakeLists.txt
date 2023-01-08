set(INCLUDE_DIR "include") # must be relative paths
add_library(
  ecs-benchmark-base
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/base/components/DataComponent.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/components/VelocityComponent.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/components/PositionComponent.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/DataSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/MoreComplexSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/MovementSystem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/systems/System.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/Application.h
  ${CMAKE_CURRENT_SOURCE_DIR}/base/entities/EntityFactory.h)
add_library(ecs-benchmark::base ALIAS ecs-benchmark-base)

target_include_directories(
  ecs-benchmark-base
  INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
            "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-base INTERFACE project_warnings project_options)

find_package(gsl-lite CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
target_link_system_libraries(ecs-benchmark-base INTERFACE gsl::gsl-lite gsl::gsl-lite-v1)
target_link_system_libraries(ecs-benchmark-base INTERFACE fmt::fmt-header-only)
