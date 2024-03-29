#ifndef ECS_BENCHMARKS_ENTT_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTT_HEROMONSTERENTITYFACTORY_H_

#include "entt/entt.h"

#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/entities/HeroMonsterEntityFactory.h"

namespace ecs::benchmarks::entt::entities {

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::entt::registry, ::entt::registry::entity_type, ecs::benchmarks::base::components::PositionComponent,
          ecs::benchmarks::base::components::PlayerComponent, ecs::benchmarks::base::components::HealthComponent,
          ecs::benchmarks::base::components::DamageComponent, ecs::benchmarks::base::components::SpriteComponent> {
public:
  // using EntityManager = ::entt::registry;
  // using Entity = ::entt::registry::entity_type;

  Entity createRandom(EntityManager& registry) override;
  Entity createHero(EntityManager& registry) override;
  Entity createMonster(EntityManager& registry) override;

  void addComponents(EntityManager& registry, Entity entity) override;

  [[nodiscard]] static inline auto getEntitiesCount(EntityManager& registry) {
    return registry.storage<Entity>().size();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent&
  getPositionComponent(EntityManager& registry, Entity entity) override {
    return registry.get<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent& getPlayerComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent& getHealthComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get<ecs::benchmarks::base::components::HealthComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent& getDamageComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get<ecs::benchmarks::base::components::DamageComponent>(entity);
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::SpriteComponent& getSpriteComponent(EntityManager& registry,
                                                                                              Entity entity) override {
    return registry.get<ecs::benchmarks::base::components::SpriteComponent>(entity);
  }

  [[nodiscard]] inline const ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponentConst(EntityManager& registry, Entity entity) override {
    return registry.get<ecs::benchmarks::base::components::PlayerComponent>(entity);
  }
};

} // namespace ecs::benchmarks::entt::entities

#endif