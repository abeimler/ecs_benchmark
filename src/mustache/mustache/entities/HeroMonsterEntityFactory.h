#ifndef ECS_BENCHMARKS_MUSTACHE_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_MUSTACHE_HEROMONSTERENTITYFACTORY_H_

/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::mustache::EntityManager, ::mustache::Entity, ecs::benchmarks::base::components::PositionComponent,
          ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
          ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  [[nodiscard]] static inline bool valid(EntityManager& entities, Entity entity) {
    return entities.isEntityValid(entity);
  }

  void addComponents(EntityManager& registry, Entity entity) override;

  [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent&
  getPositionComponent(EntityManager& registry, Entity entity) override {
    return *registry.getComponent<ecs::benchmarks::base::components::PositionComponent,
                                  ::mustache::FunctionSafety::kUnsafe>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent& getPlayerComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return *registry
                .getComponent<ecs::benchmarks::base::components::PlayerComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent& getHealthComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return *registry
                .getComponent<ecs::benchmarks::base::components::HealthComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent& getDamageComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return *registry
                .getComponent<ecs::benchmarks::base::components::DamageComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent& getSpriteComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return *registry
                .getComponent<ecs::benchmarks::base::components::SpriteComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponentConst(EntityManager& registry, Entity entity) override {
    return *registry
                .getComponent<ecs::benchmarks::base::components::PlayerComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
  }
};

} // namespace ecs::benchmarks::mustache::entities

#endif