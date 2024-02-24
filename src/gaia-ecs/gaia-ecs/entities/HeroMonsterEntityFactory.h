#ifndef ECS_BENCHMARKS_GAIA_ECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_GAIA_ECS_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::entities {

class HeroMonsterEntityFactory {
public:
  using EntityManager = ::gaia::ecs::World;
  using Entity = ::gaia::ecs::Entity;
  using BaseHeroMonsterEntityFactory = ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
      EntityManager, Entity, ecs::benchmarks::base::components::PositionComponent,
      ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
      ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent>;

  Entity createRandom(EntityManager& entities);
  Entity createHero(EntityManager& entities);
  Entity createMonster(EntityManager& entities);

  void addComponents(EntityManager& entities, Entity entity);

  //[[nodiscard]] static inline auto getEntitiesCount(EntityManager& entities) {
  //  return entities.size();
  //}

  [[nodiscard]] inline const ecs::benchmarks::base::components::PositionComponent&
  getPositionComponentConst(EntityManager& entities, Entity entity) {
    return entities.get<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent& getPlayerComponentConst(EntityManager& entities,
                                                                                                         Entity entity) {
    return entities.get<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::HealthComponent& getHealthComponentConst(EntityManager& entities, Entity entity) {
    return entities.get<ecs::benchmarks::base::components::HealthComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::DamageComponent& getDamageComponentConst(EntityManager& entities, Entity entity) {
    return entities.get<ecs::benchmarks::base::components::DamageComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::SpriteComponent& getSpriteComponentConst(EntityManager& entities,
                                                                                                         Entity entity) {
    return entities.get<ecs::benchmarks::base::components::SpriteComponent>(entity);
  }

  ecs::benchmarks::base::components::PlayerType
  initComponents(EntityManager& w, Entity e,
                 std::optional<ecs::benchmarks::base::components::PlayerType> opt_player_type = std::nullopt) {
    using namespace ecs::benchmarks::base::components;

    auto position = getPositionComponentConst(w, e);
    auto player = getPlayerComponentConst(w, e);
    auto health = getHealthComponentConst(w, e);
    auto damage = getDamageComponentConst(w, e);
    auto sprite = getSpriteComponentConst(w, e);

    auto ret = BaseHeroMonsterEntityFactory::setComponents(position,
                             player,
                             health,
                             damage,
                             sprite,
                             opt_player_type);

    w.set(e)
        .set<PositionComponent>(position)
        .set<PlayerComponent>(player)
        .set<HealthComponent>(health)
        .set<DamageComponent>(damage)
        .set<SpriteComponent>(sprite);

    return ret;
  }
};

} // namespace ecs::benchmarks::gaia_ecs::entities

#endif