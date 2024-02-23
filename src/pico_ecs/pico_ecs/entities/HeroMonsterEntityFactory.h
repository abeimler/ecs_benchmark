#ifndef ECS_BENCHMARKS_PICO_ECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_PICO_ECS_HEROMONSTERENTITYFACTORY_H_

#include "EntityFactory.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <pico_ecs.h>

namespace ecs::benchmarks::pico_ecs::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          details::EntityManager, ecs_id_t, ecs::benchmarks::base::components::PositionComponent,
          ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
          ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  void addComponents(EntityManager& registry, Entity entity) override;

  [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent&
  getPositionComponent(EntityManager& registry, Entity entity_id) override {
    return *std::bit_cast<ecs::benchmarks::base::components::PositionComponent*>(
        ecs_get(registry.ecs.get(), entity_id, registry.PositionComponent));
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponent(EntityManager& registry, Entity entity_id) override {
    return *std::bit_cast<ecs::benchmarks::base::components::PlayerComponent*>(
        ecs_get(registry.ecs.get(), entity_id, registry.PlayerComponent));
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent&
  getHealthComponent(EntityManager& registry, Entity entity_id) override {
    return *std::bit_cast<ecs::benchmarks::base::components::HealthComponent*>(
        ecs_get(registry.ecs.get(), entity_id, registry.HealthComponent));
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent&
  getDamageComponent(EntityManager& registry, Entity entity_id) override {
    return *std::bit_cast<ecs::benchmarks::base::components::DamageComponent*>(
        ecs_get(registry.ecs.get(), entity_id, registry.DamageComponent));
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent&
  getSpriteComponent(EntityManager& registry, Entity entity_id) override {
    return *std::bit_cast<ecs::benchmarks::base::components::SpriteComponent*>(
        ecs_get(registry.ecs.get(), entity_id, registry.SpriteComponent));
  }
};

} // namespace ecs::benchmarks::pico_ecs::entities

#endif