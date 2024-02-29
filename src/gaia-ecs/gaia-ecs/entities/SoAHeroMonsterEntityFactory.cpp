#include "SoAHeroMonsterEntityFactory.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"
#include "gaia-ecs/components/SoAPositionComponent.h"

namespace ecs::benchmarks::gaia_ecs::entities {

SoAHeroMonsterEntityFactory::Entity SoAHeroMonsterEntityFactory::createRandom(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.add();
  entities.build(ret)
      .add<components::SoAPositionComponent>()
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  initComponents(entities, ret);
  return ret;
}
SoAHeroMonsterEntityFactory::Entity SoAHeroMonsterEntityFactory::createHero(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.add();
  entities.build(ret)
      .add<components::SoAPositionComponent>()
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  initComponents(entities, ret, PlayerType::Hero);
  return ret;
}
SoAHeroMonsterEntityFactory::Entity SoAHeroMonsterEntityFactory::createMonster(EntityManager& entities) {
  using namespace ecs::benchmarks::base::components;
  auto ret = entities.add();
  entities.build(ret)
      .add<components::SoAPositionComponent>()
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
  initComponents(entities, ret, PlayerType::Monster);
  return ret;
}

void SoAHeroMonsterEntityFactory::addComponents(EntityManager& entities, Entity entity) {
  entities.build(entity)
      .add<ecs::benchmarks::base::components::PlayerComponent>()
      .add<ecs::benchmarks::base::components::HealthComponent>()
      .add<ecs::benchmarks::base::components::DamageComponent>()
      .add<components::SoAPositionComponent>()
      .add<ecs::benchmarks::base::components::SpriteComponent>();
}

} // namespace ecs::benchmarks::gaia_ecs::entities