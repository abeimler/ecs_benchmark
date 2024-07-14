#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAHEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAHEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include "gaia-ecs/components/SoAVelocityComponent.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::entities {


class SoAHeroMonsterEntityFactory {
public:
  using EntityManager = ::gaia::ecs::World;
  using Entity = ::gaia::ecs::Entity;
  using BaseHeroMonsterEntityFactory = ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
      EntityManager, Entity, components::SoAPositionComponent, ecs::benchmarks::base::components::PlayerComponent,
      ecs::benchmarks::base::components::HealthComponent, ecs::benchmarks::base::components::DamageComponent,
      ecs::benchmarks::base::components::SpriteComponent>;

  Entity createRandom(EntityManager& entities);
  Entity createHero(EntityManager& entities);
  Entity createMonster(EntityManager& entities);

  void addComponents(EntityManager& entities, Entity entity);

  template <class C>
  [[nodiscard]] static inline auto getComponentCount(EntityManager& entities) {
    auto query = entities.query().all<C>();
    return query.count();
  }

  [[nodiscard]] inline components::SoAPositionComponent
  getPositionComponent(EntityManager& entities, Entity entity) {
    return entities.get<components::SoAPositionComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponent(EntityManager& entities, Entity entity) {
    return entities.set<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent&
  getHealthComponent(EntityManager& entities, Entity entity) {
    return entities.set<ecs::benchmarks::base::components::HealthComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent&
  getDamageComponent(EntityManager& entities, Entity entity) {
    return entities.set<ecs::benchmarks::base::components::DamageComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent&
  getSpriteComponent(EntityManager& entities, Entity entity) {
    return entities.set<ecs::benchmarks::base::components::SpriteComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponentConst(EntityManager& entities, Entity entity) {
    return entities.get<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }


  ecs::benchmarks::base::components::PlayerType
  initComponents(EntityManager& w, Entity e,
                 std::optional<ecs::benchmarks::base::components::PlayerType> opt_player_type = std::nullopt) {
    using namespace ecs::benchmarks::base::components;

    auto position = getPositionComponent(w, e);
    auto& player = getPlayerComponent(w, e);
    auto& health = getHealthComponent(w, e);
    auto& damage = getDamageComponent(w, e);
    auto& sprite = getSpriteComponent(w, e);

    auto ret = BaseHeroMonsterEntityFactory::setComponents(position, player, health, damage, sprite, opt_player_type);

    w.set<components::SoAPositionComponent>(e) = position;

    return ret;
  }
};

} // namespace ecs::benchmarks::gaia_ecs::entities

#endif