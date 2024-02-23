#include "StableHeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"
#include "entt/components/StablePositionComponent.h"

namespace ecs::benchmarks::entt::entities {

StableHeroMonsterEntityFactory::Entity StableHeroMonsterEntityFactory::createRandom(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::base::components::PlayerComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::HealthComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DamageComponent>(ret);
  registry.emplace<components::StablePositionComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::SpriteComponent>(ret);
  initComponents(registry, ret);
  return ret;
}
StableHeroMonsterEntityFactory::Entity StableHeroMonsterEntityFactory::createHero(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::base::components::PlayerComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::HealthComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DamageComponent>(ret);
  registry.emplace<components::StablePositionComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::SpriteComponent>(ret);
  initComponents(registry, ret, PlayerType::Hero);
  return ret;
}
StableHeroMonsterEntityFactory::Entity StableHeroMonsterEntityFactory::createMonster(EntityManager& registry) {
  using namespace ecs::benchmarks::base::components;
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::base::components::PlayerComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::HealthComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DamageComponent>(ret);
  registry.emplace<components::StablePositionComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::SpriteComponent>(ret);
  initComponents(registry, ret, PlayerType::Monster);
  return ret;
}

void StableHeroMonsterEntityFactory::addComponents(EntityManager& registry, Entity entity) {
  registry.emplace_or_replace<ecs::benchmarks::base::components::PlayerComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::HealthComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::DamageComponent>(entity);
  registry.emplace_or_replace<components::StablePositionComponent>(entity);
  registry.emplace_or_replace<ecs::benchmarks::base::components::SpriteComponent>(entity);
}

} // namespace ecs::benchmarks::entt::entities
