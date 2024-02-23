#ifndef ECS_BENCHMARKS_GAIA_ECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAHEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::entities {

class SoAHeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::gaia::ecs::World, ::gaia::ecs::Entity, components::SoAPositionComponent,
          ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
          ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  Entity createRandom(EntityManager& entities) override;
  Entity createHero(EntityManager& entities) override;
  Entity createMonster(EntityManager& entities) override;

  void addComponents(EntityManager& entities, Entity entity) override;

  //[[nodiscard]] static inline auto getEntitiesCount(EntityManager& entities) {
  //  return entities.size();
  //}

  /// @FIXME: get component as non-const
  [[nodiscard]] inline components::SoAPositionComponent& getPositionComponent(EntityManager& entities, Entity entity) {
    return *const_cast<components::SoAPositionComponent*>(&entities.get<components::SoAPositionComponent>(entity));
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent& getPlayerComponent(EntityManager& entities,
                                                                                              Entity entity) {
    return *const_cast<ecs::benchmarks::base::components::PlayerComponent*>(
        &entities.get<ecs::benchmarks::base::components::PlayerComponent>(entity));
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent& getHealthComponent(EntityManager& entities,
                                                                                              Entity entity) {
    return *const_cast<ecs::benchmarks::base::components::HealthComponent*>(
        &entities.get<ecs::benchmarks::base::components::HealthComponent>(entity));
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent& getDamageComponent(EntityManager& entities,
                                                                                              Entity entity) {
    return *const_cast<ecs::benchmarks::base::components::DamageComponent*>(
        &entities.get<ecs::benchmarks::base::components::DamageComponent>(entity));
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent& getSpriteComponent(EntityManager& entities,
                                                                                              Entity entity) {
    return *const_cast<ecs::benchmarks::base::components::SpriteComponent*>(
        &entities.get<ecs::benchmarks::base::components::SpriteComponent>(entity));
  }
};

} // namespace ecs::benchmarks::gaia_ecs::entities

#endif