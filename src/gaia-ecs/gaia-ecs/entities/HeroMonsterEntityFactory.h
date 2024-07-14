#ifndef ECS_BENCHMARKS_GAIA_ECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_GAIA_ECS_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
        ::gaia::ecs::World, ::gaia::ecs::Entity, ecs::benchmarks::base::components::PositionComponent,
        ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
        ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  // using EntityManager = ::gaia::ecs::World;
  // using Entity = ::gaia::ecs::Entity;
  
  Entity createRandom(EntityManager& entities) override;
  Entity createHero(EntityManager& entities) override;
  Entity createMonster(EntityManager& entities) override;

  [[nodiscard]] static inline bool valid(EntityManager& entities, Entity entity) { return entities.valid(entity); }

  void addComponents(EntityManager& entities, Entity entity) override;

  template <class C>
  [[nodiscard]] static inline auto getComponentCount(EntityManager& entities) {
    auto query = entities.query().all<C>();
    return query.count();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent&
  getPositionComponent(EntityManager& entities, Entity entity) override {
    return entities.set<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponent(EntityManager& entities, Entity entity) override {
    return entities.set<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent&
  getHealthComponent(EntityManager& entities, Entity entity) override {
    return entities.set<ecs::benchmarks::base::components::HealthComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent&
  getDamageComponent(EntityManager& entities, Entity entity) override {
    return entities.set<ecs::benchmarks::base::components::DamageComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent&
  getSpriteComponent(EntityManager& entities, Entity entity) override {
    return entities.set<ecs::benchmarks::base::components::SpriteComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponentConst(EntityManager& entities, Entity entity) override {
    return entities.get<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }
};

} // namespace ecs::benchmarks::gaia_ecs::entities

#endif