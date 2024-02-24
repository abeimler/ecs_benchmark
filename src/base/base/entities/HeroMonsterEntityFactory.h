#ifndef ECS_BENCHMARKS_BASE_HERMONSTERENTITYFACTORY_H_
#define ECS_BENCHMARKS_BASE_HERMONSTERENTITYFACTORY_H_

#include <gsl/gsl-lite.hpp>
#include <optional>

namespace ecs::benchmarks::base::entities {

template <class tEntityManager, typename tEntity, class tPositionComponent, class tPlayerComponent,
          class tHealthComponent, class tDamageComponent, class tSpriteComponent>
class HeroMonsterEntityFactory {
public:
  using EntityManager = tEntityManager;
  using Entity = tEntity;
  using PositionComponent = tPositionComponent;
  using PlayerComponent = tPlayerComponent;
  using HealthComponent = tHealthComponent;
  using DamageComponent = tDamageComponent;
  using SpriteComponent = tSpriteComponent;

  inline static constexpr auto SpawAreaMaxX = 320;
  inline static constexpr auto SpawAreaMaxY = 240;
  inline static constexpr auto SpawAreaMargin = 100;

  struct PlayerArchetype {
    PositionComponent position_comp;
    PlayerComponent player_comp;
    HealthComponent health_comp;
    DamageComponent damage_comp;
    SpriteComponent sprite_comp;
  };
  struct MonsterArchetype {
    PositionComponent position_comp;
    PlayerComponent player_comp;
    HealthComponent health_comp;
    DamageComponent damage_comp;
    SpriteComponent sprite_comp;
  };

  HeroMonsterEntityFactory() = default;
  virtual ~HeroMonsterEntityFactory() = default;
  HeroMonsterEntityFactory(const HeroMonsterEntityFactory&) = default;
  HeroMonsterEntityFactory& operator=(const HeroMonsterEntityFactory&) = default;
  HeroMonsterEntityFactory(HeroMonsterEntityFactory&&) noexcept = default;
  HeroMonsterEntityFactory& operator=(HeroMonsterEntityFactory&&) noexcept = default;

  virtual Entity createRandom(EntityManager& registry) = 0;
  virtual Entity createHero(EntityManager& registry) = 0;
  virtual Entity createMonster(EntityManager& registry) = 0;

  virtual PositionComponent& getPositionComponent(EntityManager& registry, Entity entity) = 0;
  virtual PlayerComponent& getPlayerComponent(EntityManager& registry, Entity entity) = 0;
  virtual HealthComponent& getHealthComponent(EntityManager& registry, Entity entity) = 0;
  virtual DamageComponent& getDamageComponent(EntityManager& registry, Entity entity) = 0;
  virtual SpriteComponent& getSpriteComponent(EntityManager& registry, Entity entity) = 0;

  virtual const PlayerComponent& getPlayerComponentConst(EntityManager& registry, Entity entity) = 0;

  virtual void addComponents(EntityManager& registry, Entity entity) = 0;

  ecs::benchmarks::base::components::PlayerType
  initComponents(EntityManager& registry, Entity entity,
                 std::optional<ecs::benchmarks::base::components::PlayerType> opt_player_type = std::nullopt) {
    auto& position = getPositionComponent(registry, entity);
    auto& player = getPlayerComponent(registry, entity);
    auto& health = getHealthComponent(registry, entity);
    auto& damage = getDamageComponent(registry, entity);
    auto& sprite = getSpriteComponent(registry, entity);

    return setComponents(position, player, health, damage, sprite, opt_player_type);
  }

  static ecs::benchmarks::base::components::PlayerType
  setComponents(PositionComponent& position, PlayerComponent& player, HealthComponent& health, DamageComponent& damage,
                SpriteComponent& sprite,
                std::optional<ecs::benchmarks::base::components::PlayerType> opt_player_type = std::nullopt) {
    using namespace ecs::benchmarks::base::components;

    player.type = opt_player_type.value_or([&player]() {
      const auto player_type_rate = player.rng.range(1, 100);
      return (player_type_rate <= 3)    ? PlayerType::NPC
             : (player_type_rate <= 30) ? PlayerType::Hero
                                        : PlayerType::Monster;
    }());
    switch (player.type) {
      case PlayerType::Hero:
        health.maxhp = gsl::narrow_cast<int>(player.rng.range(5, 15));
        damage.def = gsl::narrow_cast<int>(player.rng.range(2, 6));
        damage.atk = gsl::narrow_cast<int>(player.rng.range(4, 10));
        break;
      case PlayerType::Monster:
        health.maxhp = gsl::narrow_cast<int>(player.rng.range(4, 12));
        damage.def = gsl::narrow_cast<int>(player.rng.range(2, 8));
        damage.atk = gsl::narrow_cast<int>(player.rng.range(3, 9));
        break;
      case PlayerType::NPC:
        health.maxhp = gsl::narrow_cast<int>(player.rng.range(6, 12));
        damage.def = gsl::narrow_cast<int>(player.rng.range(3, 8));
        damage.atk = 0;
        break;
    }

    sprite.character = '_';
    position.x = gsl::narrow_cast<float>(player.rng.range(0, SpawAreaMaxX + SpawAreaMargin)) - SpawAreaMargin;
    position.y = gsl::narrow_cast<float>(player.rng.range(0, SpawAreaMaxY + SpawAreaMargin)) - SpawAreaMargin;

    return player.type;
  }
};

} // namespace ecs::benchmarks::base::entities

#endif