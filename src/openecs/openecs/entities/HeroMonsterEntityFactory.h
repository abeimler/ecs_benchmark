#ifndef ECS_BENCHMARKS_OPENECS_HEROMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_OPENECS_HEROMONSTERENTITYFACTORY_H_

#include "base/components/HeroMonsterComponents.h"
#include "base/entities/HeroMonsterEntityFactory.h"
#include <ecs.h>

namespace ecs::benchmarks::openecs::entities {

struct PlayerEntity final : public ::ecs::EntityAlias<ecs::benchmarks::base::components::PlayerComponent,
                                                      ecs::benchmarks::base::components::HealthComponent,
                                                      ecs::benchmarks::base::components::DamageComponent> {
  PlayerEntity() {
    add<ecs::benchmarks::base::components::PlayerComponent>();
    add<ecs::benchmarks::base::components::HealthComponent>();
    add<ecs::benchmarks::base::components::DamageComponent>();
  }
};
struct HeroEntity final : public ::ecs::EntityAlias<ecs::benchmarks::base::components::PlayerComponent,
                                                    ecs::benchmarks::base::components::HealthComponent,
                                                    ecs::benchmarks::base::components::DamageComponent> {
  HeroEntity() {
    add<ecs::benchmarks::base::components::PlayerComponent>();
    add<ecs::benchmarks::base::components::HealthComponent>();
    add<ecs::benchmarks::base::components::DamageComponent>();
  }
};
struct MonsterEntity final : public ::ecs::EntityAlias<ecs::benchmarks::base::components::PlayerComponent,
                                                       ecs::benchmarks::base::components::HealthComponent,
                                                       ecs::benchmarks::base::components::DamageComponent> {
  MonsterEntity() {
    add<ecs::benchmarks::base::components::PlayerComponent>();
    add<ecs::benchmarks::base::components::HealthComponent>();
    add<ecs::benchmarks::base::components::DamageComponent>();
  }
};

class HeroMonsterEntityFactory final
    : public ecs::benchmarks::base::entities::HeroMonsterEntityFactory<
          ::ecs::EntityManager, ::ecs::Entity, ecs::benchmarks::base::components::PlayerComponent,
          ecs::benchmarks::base::components::HealthComponent, ecs::benchmarks::base::components::DamageComponent> {
public:
  Entity createRandom(EntityManager& entities) override;
  Entity createHero(EntityManager& entities) override;
  Entity createMonster(EntityManager& entities) override;

  void addComponents(EntityManager& entities, Entity entity) override;

  [[nodiscard]] inline ecs::benchmarks::base::components::PlayerComponent&
  getPlayerComponent(EntityManager& /*entities*/, Entity entity) override {
    return entity.get<ecs::benchmarks::base::components::PlayerComponent>();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::HealthComponent&
  getHealthComponent(EntityManager& /*entities*/, Entity entity) override {
    return entity.get<ecs::benchmarks::base::components::HealthComponent>();
  }

  [[nodiscard]] inline ecs::benchmarks::base::components::DamageComponent&
  getDamageComponent(EntityManager& /*entities*/, Entity entity) override {
    return entity.get<ecs::benchmarks::base::components::DamageComponent>();
  }
};

} // namespace ecs::benchmarks::openecs::entities

#endif