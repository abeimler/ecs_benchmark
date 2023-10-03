# https://github.com/apples/ginseng add dependencies
cpmaddpackage(
  NAME
  ginseng
  VERSION
  1.1
  GITHUB_REPOSITORY
  apples/ginseng
  # TODO: set current version, use master (release 1.1 is outdated)
  GIT_TAG
  master)

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(
  ecs-benchmark-example-ginseng STATIC
  # NOTE: add source files here
  ginseng/systems/DataSystem.h
  ginseng/systems/DataSystem.cpp
  ginseng/systems/MoreComplexSystem.h
  ginseng/systems/MoreComplexSystem.cpp
  ginseng/systems/MovementSystem.h
  ginseng/systems/MovementSystem.cpp
  ginseng/entities/EntityFactory.h
  ginseng/entities/EntityFactory.cpp
  ginseng/entities/HeroMonsterEntityFactory.h
  ginseng/entities/HeroMonsterEntityFactory.cpp
  ginseng/GinsengApplication.h
  ginseng/GinsengApplication.cpp)
add_library(ecs-benchmark::example::ginseng ALIAS ecs-benchmark-example-ginseng)

target_include_directories(
  ecs-benchmark-example-ginseng
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-ginseng PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-ginseng PUBLIC ecs-benchmark-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-ginseng PUBLIC ginseng)
