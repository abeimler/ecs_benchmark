#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::flecs::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.entity()
                 .add<ecs::benchmarks::base::components::PlayerComponent>()
                 .add<ecs::benchmarks::base::components::HealthComponent>()
                 .add<ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.entity()
                 .add<ecs::benchmarks::base::components::PlayerComponent>()
                 .add<ecs::benchmarks::base::components::HealthComponent>()
                 .add<ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.entity()
                 .add<ecs::benchmarks::base::components::PlayerComponent>()
                 .add<ecs::benchmarks::base::components::HealthComponent>()
                 .add<ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& /*entities*/, Entity entity) {
  entity.add<ecs::benchmarks::base::components::PlayerComponent>();
  entity.add<ecs::benchmarks::base::components::HealthComponent>();
  entity.add<ecs::benchmarks::base::components::DamageComponent>();
  entity.add<ecs::benchmarks::base::components::SpriteComponent>();
  entity.add<ecs::benchmarks::base::components::DamageComponent>();
  if (!entity.has<ecs::benchmarks::base::components::DamageComponent>()) {
    entity.add<ecs::benchmarks::base::components::DamageComponent>();
  }
}

} // namespace ecs::benchmarks::flecs::entities
