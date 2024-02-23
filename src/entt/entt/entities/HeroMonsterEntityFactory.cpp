#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::base::components::PlayerComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::HealthComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DamageComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::SpriteComponent>(ret);
  initComponents(registry, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::base::components::PlayerComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::HealthComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DamageComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::SpriteComponent>(ret);
  initComponents(registry, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::base::components::PlayerComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::HealthComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DamageComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::SpriteComponent>(ret);
  initComponents(registry, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& registry, Entity entity) {
  registry.emplace_or_replace<ecs::benchmarks::base::components::PlayerComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::HealthComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::DamageComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::PositionComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::SpriteComponent>(entity);
}

} // namespace ecs::benchmarks::entt::entities
