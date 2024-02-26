#ifndef ECS_BENCHMARKS_FLECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_FLECS_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include "flecs/custom_flecs.h"

namespace ecs::benchmarks::flecs::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::flecs::world, ::flecs::entity, ecs::benchmarks::base::components::PositionComponent,
          ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
          ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  Entity createRandom(EntityManager& entities) override;
  Entity createHero(EntityManager& entities) override;
  Entity createMonster(EntityManager& entities) override;

  void addComponents(EntityManager& entities, Entity entity) override;

  template <class C>
  [[nodiscard]] static inline auto getComponentCount(EntityManager& entities) {
    return entities.count<C>();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent&
  getPositionComponent(EntityManager& /*entities*/, Entity entity) override {
    return *entity.get_mut<ecs::benchmarks::base::components::PositionComponent>();
  }

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

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent&
  getSpriteComponent(EntityManager& /*entities*/, Entity entity) override {
    return *entity.get_mut<ecs::benchmarks::base::components::SpriteComponent>();
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponentConst(EntityManager& /*entities*/, Entity entity) override {
    return *entity.get<ecs::benchmarks::base::components::PlayerComponent>();
  }
};

} // namespace ecs::benchmarks::flecs::entities

#endif