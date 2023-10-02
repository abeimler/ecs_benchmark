#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entityx::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create();
  ret.assign<ecs::benchmarks::base::components::PlayerComponent>();
  ret.assign<ecs::benchmarks::base::components::HealthComponent>();
  ret.assign<ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create();
  ret.assign<ecs::benchmarks::base::components::PlayerComponent>();
  ret.assign<ecs::benchmarks::base::components::HealthComponent>();
  ret.assign<ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create();
  ret.assign<ecs::benchmarks::base::components::PlayerComponent>();
  ret.assign<ecs::benchmarks::base::components::HealthComponent>();
  ret.assign<ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& /*entities*/, Entity entity) {
  entity.assign<ecs::benchmarks::base::components::PlayerComponent>();
  entity.assign<ecs::benchmarks::base::components::HealthComponent>();
  entity.assign<ecs::benchmarks::base::components::DamageComponent>();
}

} // namespace ecs::benchmarks::entt::entities
