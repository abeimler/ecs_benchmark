# https://github.com/richardbiely/gaia-ecs
cpmaddpackage(
  NAME
  gaia
  VERSION
  0.8.5
  GITHUB_REPOSITORY
  richardbiely/gaia-ecs
  # TODO: set current version, use main for build fixes
  GIT_TAG
  main
  OPTIONS
  "GAIA_BUILD_UNITTEST OFF"
  "GAIA_BUILD_BENCHMARK OFF"
  "GAIA_BUILD_EXAMPLES OFF"
  "GAIA_MAKE_SINGLE_HEADER OFF"
  DOWNLOAD_ONLY
  True)
# @FIXME: can not found <gaia.h> header ... use single-header download
if(gaia_ADDED)
  add_library(gaia INTERFACE ${gaia_SOURCE_DIR}/include/gaia.h)
  add_library(gaia-ecs ALIAS gaia)
  target_include_directories(gaia INTERFACE "$<BUILD_INTERFACE:${gaia_SOURCE_DIR}/include>")
  target_compile_features(gaia INTERFACE cxx_std_17)
endif()

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-example-myecs"
add_library(
  ecs-benchmark-example-gaia-ecs STATIC
  # NOTE: add source files here
  gaia-ecs/systems/DataSystem.h
  gaia-ecs/systems/DataSystem.cpp
  gaia-ecs/systems/MoreComplexSystem.h
  gaia-ecs/systems/MoreComplexSystem.cpp
  gaia-ecs/systems/soa/SoAMoreComplexSystem.h
  gaia-ecs/systems/soa/SoAMoreComplexSystem.cpp
  gaia-ecs/systems/MovementSystem.h
  gaia-ecs/systems/MovementSystem.cpp
  gaia-ecs/systems/soa/SoAMovementSystem.h
  gaia-ecs/systems/soa/SoAMovementSystem.cpp
  gaia-ecs/systems/soa/SoARenderSystem.h
  gaia-ecs/systems/soa/SoARenderSystem.cpp
  gaia-ecs/systems/DamageSystem.h
  gaia-ecs/systems/DamageSystem.cpp
  gaia-ecs/systems/HealthSystem.h
  gaia-ecs/systems/HealthSystem.cpp
  gaia-ecs/systems/RenderSystem.h
  gaia-ecs/systems/RenderSystem.cpp
  gaia-ecs/systems/SpriteSystem.h
  gaia-ecs/systems/SpriteSystem.cpp
  gaia-ecs/entities/EntityFactory.h
  gaia-ecs/entities/EntityFactory.cpp
  gaia-ecs/entities/SoAEntityFactory.h
  gaia-ecs/entities/SoAEntityFactory.cpp
  gaia-ecs/entities/HeroMonsterEntityFactory.h
  gaia-ecs/entities/HeroMonsterEntityFactory.cpp
  gaia-ecs/entities/SoAHeroMonsterEntityFactory.h
  gaia-ecs/entities/SoAHeroMonsterEntityFactory.cpp
  gaia-ecs/GaiaEcsApplication.h
  gaia-ecs/GaiaEcsApplication.cpp
  gaia-ecs/SoAGaiaEcsApplication.h
  gaia-ecs/SoAGaiaEcsApplication.cpp)
add_library(ecs-benchmark::example::gaia-ecs ALIAS ecs-benchmark-example-gaia-ecs)

target_include_directories(
  ecs-benchmark-example-gaia-ecs
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-gaia-ecs PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-gaia-ecs PUBLIC ecs-benchmark-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-gaia-ecs PUBLIC gaia)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ecs-benchmark-example-gaia-ecs PRIVATE Threads::Threads)
