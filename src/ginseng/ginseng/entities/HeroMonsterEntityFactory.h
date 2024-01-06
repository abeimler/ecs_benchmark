#ifndef ECS_BENCHMARKS_GINSENG_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_GINSENG_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::ginseng::database, ::ginseng::database::ent_id, ecs::benchmarks::base::components::PlayerComponent,
          ecs::benchmarks::base::components::HealthComponent, ecs::benchmarks::base::components::DamageComponent> {
public:
  // using EntityManager = ::ginseng::database;
  // using Entity = ::ginseng::database::ent_id;
  using Component = ::ginseng::database::com_id;

  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  [[nodiscard]] static inline auto getEntitiesCount(EntityManager& registry) {
    return registry.size();
  }

  [[nodiscard]] static inline bool valid(EntityManager& registry, Entity entity) {
    return registry.exists(entity);
  }

  void addComponents(EntityManager& registry, Entity entity) override;

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent& getPlayerComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get_component<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent& getHealthComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get_component<ecs::benchmarks::base::components::HealthComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent& getDamageComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get_component<ecs::benchmarks::base::components::DamageComponent>(entity);
  }
};

} // namespace ecs::benchmarks::ginseng::entities

#endif