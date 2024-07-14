# https://github.com/skypjack/entt
cpmaddpackage(
  NAME
  EnTT
  VERSION
  3.13.2
  GITHUB_REPOSITORY
  skypjack/entt
  OPTIONS
  "ENTT_BUILD_TESTING OFF"
  "ENTT_BUILD_DOCS OFF")

set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-example-myecs"
add_library(
  ecs-benchmark-example-entt STATIC
  # NOTE: add source files here
  entt/components/StablePositionComponent.h
  entt/components/StableVelocityComponent.h
  entt/systems/DamageSystem.h
  entt/systems/DamageSystem.cpp
  entt/systems/DataSystem.h
  entt/systems/DataSystem.cpp
  entt/systems/HealthSystem.h
  entt/systems/HealthSystem.cpp
  entt/systems/MoreComplexSystem.h
  entt/systems/MoreComplexSystem.cpp
  entt/systems/MovementSystem.h
  entt/systems/MovementSystem.cpp
  entt/systems/RenderSystem.h
  entt/systems/RenderSystem.cpp
  entt/systems/SpriteSystem.h
  entt/systems/SpriteSystem.cpp
  entt/systems/stable/StableMovementSystem.cpp
  entt/systems/stable/StableMovementSystem.h
  entt/systems/runtime/RuntimeDamageSystem.h
  entt/systems/runtime/RuntimeDamageSystem.cpp
  entt/systems/runtime/RuntimeDataSystem.h
  entt/systems/runtime/RuntimeDataSystem.cpp
  entt/systems/runtime/RuntimeHealthSystem.h
  entt/systems/runtime/RuntimeHealthSystem.cpp
  entt/systems/runtime/RuntimeMoreComplexSystem.h
  entt/systems/runtime/RuntimeMoreComplexSystem.cpp
  entt/systems/runtime/RuntimeMovementSystem.h
  entt/systems/runtime/RuntimeMovementSystem.cpp
  entt/systems/stable/StableRuntimeMovementSystem.h
  entt/systems/stable/StableRuntimeMovementSystem.cpp
  entt/systems/stable/StableRuntimeMovementSystem.h
  entt/systems/stable/StableRuntimeMovementSystem.cpp
  entt/systems/group/GroupDamageSystem.h
  entt/systems/group/GroupDamageSystem.cpp
  entt/systems/group/GroupHealthSystem.h
  entt/systems/group/GroupHealthSystem.cpp
  entt/systems/group/GroupSpriteSystem.h
  entt/systems/group/GroupSpriteSystem.cpp
  entt/systems/group/GroupMoreComplexSystem.h
  entt/systems/group/GroupMoreComplexSystem.cpp
  entt/systems/group/GroupMovementSystem.h
  entt/systems/group/GroupMovementSystem.cpp
  entt/entities/EntityFactory.h
  entt/entities/EntityFactory.cpp
  entt/entities/HeroMonsterEntityFactory.h
  entt/entities/HeroMonsterEntityFactory.cpp
  entt/entities/StableEntityFactory.h
  entt/entities/StableEntityFactory.cpp
  entt/entities/StableHeroMonsterEntityFactory.h
  entt/entities/StableHeroMonsterEntityFactory.cpp
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
add_library(ecs-benchmark::example::entt ALIAS ecs-benchmark-example-entt)

target_include_directories(
  ecs-benchmark-example-entt
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-example-entt PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-example-entt PUBLIC ecs-benchmark-base)

# NOTE: add 3rd-party libs here
target_link_system_libraries(ecs-benchmark-example-entt PUBLIC EnTT)
