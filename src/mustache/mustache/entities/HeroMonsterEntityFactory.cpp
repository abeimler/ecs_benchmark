#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::mustache::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create<ecs::benchmarks::base::components::PlayerComponent,
                             ecs::benchmarks::base::components::HealthComponent,
                             ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create<ecs::benchmarks::base::components::PlayerComponent,
                             ecs::benchmarks::base::components::HealthComponent,
                             ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create<ecs::benchmarks::base::components::PlayerComponent,
                             ecs::benchmarks::base::components::HealthComponent,
                             ecs::benchmarks::base::components::DamageComponent>();
  initComponents(entities, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& entities, Entity entity) {
  entities.assign<ecs::benchmarks::base::components::PlayerComponent>(entity);
  entities.assign<ecs::benchmarks::base::components::HealthComponent>(entity);
  entities.assign<ecs::benchmarks::base::components::DamageComponent>(entity);
}

} // namespace ecs::benchmarks::mustache::entities
