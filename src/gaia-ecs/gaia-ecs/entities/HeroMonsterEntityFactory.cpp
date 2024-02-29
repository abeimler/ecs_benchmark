#include "HeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::gaia_ecs::entities {

HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createRandom(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.add();
  entities.build(ret)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  initComponents(entities, ret);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createHero(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.add();
  entities.build(ret)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  initComponents(entities, ret, PlayerType::Hero);
  return ret;
}
HeroMonsterEntityFactory::Entity HeroMonsterEntityFactory::createMonster(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.add();
  entities.build(ret)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  initComponents(entities, ret, PlayerType::Monster);
  return ret;
}

void HeroMonsterEntityFactory::addComponents(EntityManager& entities, Entity entity) {
  auto builder = entities.build(entity);
  builder
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  if (!entities.has<ecs::benchmarks::base::components::PositionComponent>(entity)) {
    builder.add<ecs::benchmarks::base::components::PositionComponent>();
  }
  builder.commit();

}

} // namespace ecs::benchmarks::gaia_ecs::entities