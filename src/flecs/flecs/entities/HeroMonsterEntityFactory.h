#ifndef ECS_BENCHMARKS_FLECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_FLECS_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include "flecs/custom_flecs.h"

namespace ecs::benchmarks::flecs::entities {

class HeroMonsterEntityFactory final : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<::flecs::world, ::flecs::entity,
                                                                                                  ecs::benchmarks::base::components::PlayerComponent,
                                                                                                  ecs::benchmarks::base::components::HealthComponent,
                                                                                                  ecs::benchmarks::base::components::DamageComponent> {
public:
  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  void addComponents(EntityManager& registry, Entity entity) override;

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponent(EntityManager& /*entities*/, Entity entity) override {
    return *entity.get_mut<ecs::benchmarks::base::components::PlayerComponent>();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent&
  getHealthComponent(EntityManager& /*entities*/, Entity entity) override {
    return *entity.get_mut<ecs::benchmarks::base::components::HealthComponent>();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent&
  getDamageComponent(EntityManager& /*entities*/, Entity entity) override {
    return *entity.get_mut<ecs::benchmarks::base::components::DamageComponent>();
  }
};

} // namespace ecs::benchmarks::entt::entities

#endif