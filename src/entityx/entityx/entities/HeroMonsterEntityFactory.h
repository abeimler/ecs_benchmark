#ifndef ECS_BENCHMARKS_ENTITYX_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTITYX_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::entityx::EntityManager, ::entityx::Entity, ecs::benchmarks::base::components::PositionComponent,
          ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
          ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  // using EntityManager = ::entityx::EntityManager;
  // using Entity = ::entityx::Entity;

  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  [[nodiscard]] static inline bool valid(EntityManager& entities, Entity entity) { return entities.valid(entity.id()); }

  void addComponents(EntityManager& registry, Entity entity) override;

  [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent&
  getPositionComponent(EntityManager& entities, Entity entity) override {
    return *entities.component<ecs::benchmarks::base::components::PositionComponent>(entity.id());
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent& getPlayerComponent(EntityManager& entities,
                                                                                              Entity entity) override {
    return *entities.component<ecs::benchmarks::base::components::PlayerComponent>(entity.id());
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent& getHealthComponent(EntityManager& entities,
                                                                                              Entity entity) override {
    return *entities.component<ecs::benchmarks::base::components::HealthComponent>(entity.id());
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent& getDamageComponent(EntityManager& entities,
                                                                                              Entity entity) override {
    return *entities.component<ecs::benchmarks::base::components::DamageComponent>(entity.id());
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent& getSpriteComponent(EntityManager& entities,
                                                                                              Entity entity) override {
    return *entities.component<ecs::benchmarks::base::components::SpriteComponent>(entity.id());
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponentConst(EntityManager& entities, Entity entity) override {
    return *entities.component<ecs::benchmarks::base::components::PlayerComponent>(entity.id());
  }
};

} // namespace ecs::benchmarks::entityx::entities

#endif