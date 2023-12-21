# https://github.com/kirillochnev/mustache
cpmaddpackage(
  NAME
  mustache
  VERSION
  0.2
  GITHUB_REPOSITORY
  kirillochnev/mustache
  # TODO: set current version, use master (no release version)
  GIT_TAG
  master
  OPTIONS
  "MUSTACHE_CXX_STD cxx_std_20"
  "MUSTACHE_USE_SANITIZER OFF"
  "MUSTACHE_WARNINGS_AS_ERROR OFF"
  "MUSTACHE_BUILD_SHARED OFF")

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(
  ecs-benchmark-example-mustache STATIC
  # NOTE: add source files here
  mustache/systems/DataSystem.h
  mustache/systems/DataSystem.cpp
  mustache/systems/MoreComplexSystem.h
  mustache/systems/MoreComplexSystem.cpp
  mustache/systems/MovementSystem.h
  mustache/systems/MovementSystem.cpp
  mustache/entities/EntityFactory.h
  mustache/entities/EntityFactory.cpp
  mustache/entities/HeroMonsterEntityFactory.h
  mustache/entities/HeroMonsterEntityFactory.cpp
  mustache/MustacheApplication.h
  mustache/MustacheApplication.cpp)
add_library(ecs-benchmark::example::mustache ALIAS ecs-benchmark-example-mustache)

target_include_directories(
  ecs-benchmark-example-mustache
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-mustache PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-mustache PUBLIC ecs-benchmark-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-mustache PUBLIC mustache)
