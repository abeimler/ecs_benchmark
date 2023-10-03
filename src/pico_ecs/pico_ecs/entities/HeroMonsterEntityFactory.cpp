#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::pico_ecs::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = ecs_create(registry.ecs.get());
  ecs_add(registry.ecs.get(), ret, registry.PlayerComponent, nullptr);
  ecs_add(registry.ecs.get(), ret, registry.HealthComponent, nullptr);
  ecs_add(registry.ecs.get(), ret, registry.DamageComponent, nullptr);
  initComponents(registry, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = ecs_create(registry.ecs.get());
  ecs_add(registry.ecs.get(), ret, registry.PlayerComponent, nullptr);
  ecs_add(registry.ecs.get(), ret, registry.HealthComponent, nullptr);
  ecs_add(registry.ecs.get(), ret, registry.DamageComponent, nullptr);
  initComponents(registry, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = ecs_create(registry.ecs.get());
  ecs_add(registry.ecs.get(), ret, registry.PlayerComponent, nullptr);
  ecs_add(registry.ecs.get(), ret, registry.HealthComponent, nullptr);
  ecs_add(registry.ecs.get(), ret, registry.DamageComponent, nullptr);
  initComponents(registry, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& registry, Entity entity) {
  ecs_add(registry.ecs.get(), entity, registry.PlayerComponent, nullptr);
  ecs_add(registry.ecs.get(), entity, registry.HealthComponent, nullptr);
  ecs_add(registry.ecs.get(), entity, registry.DamageComponent, nullptr);
}

} // namespace ecs::benchmarks::pico_ecs::entities
