#ifndef ECS_BENCHMARKS_MUSTACHE_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_MUSTACHE_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/entities/HeroMonsterEntityFactory.h"
/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::mustache::EntityManager, ::mustache::Entity, ecs::benchmarks::base::components::PlayerComponent,
          ecs::benchmarks::base::components::HealthComponent, ecs::benchmarks::base::components::DamageComponent> {
public:
  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  void addComponents(EntityManager& registry, Entity entity) override;

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
};

} // namespace ecs::benchmarks::mustache::entities

#endif