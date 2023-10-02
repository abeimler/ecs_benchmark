#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::ginseng::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create_entity();
  registry.add_component(ret, ecs::benchmarks::base::components::PlayerComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::HealthComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::DamageComponent{});
  initComponents(registry, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create_entity();
  registry.add_component(ret, ecs::benchmarks::base::components::PlayerComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::HealthComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::DamageComponent{});
  initComponents(registry, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create_entity();
  registry.add_component(ret, ecs::benchmarks::base::components::PlayerComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::HealthComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::DamageComponent{});
  initComponents(registry, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& registry, Entity entity) {
  registry.add_component(entity, ecs::benchmarks::base::components::PlayerComponent{});
  registry.add_component(entity, ecs::benchmarks::base::components::HealthComponent{});
  registry.add_component(entity, ecs::benchmarks::base::components::DamageComponent{});
}

} // namespace ecs::benchmarks::entt::entities
