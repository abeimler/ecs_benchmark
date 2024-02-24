set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(
  ecs-benchmark-example-pico-ecs STATIC
  # NOTE: add source files here
  pico_ecs/systems/DamageSystem.h
  pico_ecs/systems/DamageSystem.cpp
  pico_ecs/systems/DataSystem.h
  pico_ecs/systems/DataSystem.cpp
  pico_ecs/systems/HealthSystem.h
  pico_ecs/systems/HealthSystem.cpp
  pico_ecs/systems/MoreComplexSystem.h
  pico_ecs/systems/MoreComplexSystem.cpp
  pico_ecs/systems/MovementSystem.h
  pico_ecs/systems/MovementSystem.cpp
  pico_ecs/systems/RenderSystem.h
  pico_ecs/systems/RenderSystem.cpp
  pico_ecs/systems/SpriteSystem.h
  pico_ecs/systems/SpriteSystem.cpp
  pico_ecs/entities/EntityFactory.h
  pico_ecs/entities/EntityFactory.cpp
  pico_ecs/entities/HeroMonsterEntityFactory.h
  pico_ecs/entities/HeroMonsterEntityFactory.cpp
  pico_ecs/PicoEcsApplication.h
  pico_ecs/PicoEcsApplication.cpp
  pico_ecs/pico_ecs.cpp)
add_library(ecs-benchmark::example::pico_ecs ALIAS ecs-benchmark-example-pico-ecs)

target_include_directories(
  ecs-benchmark-example-pico-ecs
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-pico-ecs PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-pico-ecs PUBLIC ecs-benchmark-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-pico-ecs PUBLIC pico_ecs)
target_compile_definitions(ecs-benchmark-example-pico-ecs PUBLIC ECS_USE_FLOAT)
