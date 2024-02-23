#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::openecs::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create<PlayerEntity>();
  ;
  initComponents(entities, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create<HeroEntity>();
  initComponents(entities, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.create<MonsterEntity>();
  initComponents(entities, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& /*entities*/, Entity entity) {
  entity.add<ecs::benchmarks::base::components::PlayerComponent>();
  entity.add<ecs::benchmarks::base::components::HealthComponent>();
  entity.add<ecs::benchmarks::base::components::DamageComponent>();
  entity.add<ecs::benchmarks::base::components::SpriteComponent>();
  if (!entity.has<ecs::benchmarks::base::components::PositionComponent>()) {
    entity.add<ecs::benchmarks::base::components::PositionComponent>();
  }
}

} // namespace ecs::benchmarks::openecs::entities
