#ifndef ECS_BENCHMARKS_BASE_HERMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_BASE_HERMONSTERENTITYFACTORY_H_

#include <vector>
#include <optional>

namespace ecs::benchmarks::base::entities {

template <class tEntityManager, typename tEntity, class tPlayerComponent, class tHealthComponent, class tDamageComponent>
class HeroMonsterEntityFactory {
public:
  using EntityManager = tEntityManager;
  using Entity = tEntity;
  using PlayerComponent = tPlayerComponent;
  using HealthComponent = tHealthComponent;
  using DamageComponent = tDamageComponent;

  struct PlayerArchetype {
    PlayerComponent player_comp;
    HealthComponent health_comp;
    DamageComponent damage_comp;
  };
  struct MonsterArchetype {
    PlayerComponent player_comp;
    HealthComponent health_comp;
    DamageComponent damage_comp;
  };

  // virtual dtor and the rule of 6
  HeroMonsterEntityFactory() = default;
  virtual ~HeroMonsterEntityFactory() = default;
  HeroMonsterEntityFactory(const HeroMonsterEntityFactory&) = default;
  HeroMonsterEntityFactory& operator=(const HeroMonsterEntityFactory&) = default;
  HeroMonsterEntityFactory(HeroMonsterEntityFactory&&) noexcept = default;
  HeroMonsterEntityFactory& operator=(HeroMonsterEntityFactory&&) noexcept = default;

  virtual Entity createRandom(EntityManager& registry) = 0;
  virtual Entity createHero(EntityManager& registry) = 0;
  virtual Entity createMonster(EntityManager& registry) = 0;

  virtual PlayerComponent& getPlayerComponent(EntityManager& registry, Entity entity) = 0;
  virtual HealthComponent& getHealthComponent(EntityManager& registry, Entity entity) = 0;
  virtual DamageComponent& getDamageComponent(EntityManager& registry, Entity entity) = 0;

  virtual void addComponents(EntityManager& registry, Entity entity) = 0;

  ecs::benchmarks::base::components::PlayerType
  initComponents(EntityManager& registry, Entity entity,
                 std::optional<ecs::benchmarks::base::components::PlayerType> opt_player_type = std::nullopt) {
    using namespace ecs::benchmarks::base::components;
    auto& player = getPlayerComponent(registry, entity);
    auto& health = getHealthComponent(registry, entity);
    auto& damage = getDamageComponent(registry, entity);

    player.type = opt_player_type.value_or([&player]() {
      const auto player_type_rate = player.rng.range(1, 100);
      return (player_type_rate <= 3)? PlayerType::NPC : (player_type_rate <= 30) ? PlayerType::Hero : PlayerType::Monster;
    }());
    switch(player.type) {
      case PlayerType::Hero:
        health.maxhp = player.rng.range(5, 15);
        damage.def = player.rng.range(2, 6);
        damage.atk = player.rng.range(4, 10);
        break;
      case PlayerType::Monster:
        health.maxhp = player.rng.range(4, 12);
        damage.def = player.rng.range(2, 8);
        damage.atk = player.rng.range(3, 9);
        break;
      case PlayerType::NPC:
        health.maxhp = player.rng.range(6, 12);
        damage.def = player.rng.range(3, 8);
        damage.atk = 0;
        break;
    }
    return player.type;
  }
};

} // namespace ecs::benchmarks::base::entities

#endif