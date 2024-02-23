#ifndef ECS_BENCHMARKS_BASE_SPRITE_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_BASE_SPRITE_RENDERSYSTEM_H_

#include "System.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta>
class SpriteSystem : public System<EntityManager, TimeDelta> {
public:
  inline static constexpr char PlayerSprite = '@';
  inline static constexpr char MonsterSprite = 'k';
  inline static constexpr char NPCSprite = 'h';
  inline static constexpr char GraveSprite = '|';
  inline static constexpr char SpawnSprite = '_';
  inline static constexpr char NoneSprite = ' ';

  SpriteSystem() = default;
  virtual ~SpriteSystem() = default;
  SpriteSystem(const SpriteSystem&) = delete;
  SpriteSystem& operator=(const SpriteSystem&) = delete;
  SpriteSystem(SpriteSystem&&) noexcept = default;
  SpriteSystem& operator=(SpriteSystem&&) noexcept = default;

  static void updateSprite(ecs::benchmarks::base::components::SpriteComponent& spr,
                           const ecs::benchmarks::base::components::PlayerComponent& player,
                           const ecs::benchmarks::base::components::HealthComponent& health) {
    spr.character = [&]() {
      switch (health.status) {
        case components::StatusEffect::Alive:
          switch (player.type) {
            case components::PlayerType::Hero:
              return PlayerSprite;
            case components::PlayerType::Monster:
              return MonsterSprite;
            case components::PlayerType::NPC:
              return NPCSprite;
          }
          break;
        case components::StatusEffect::Dead:
          return GraveSprite;
        case components::StatusEffect::Spawn:
          return SpawnSprite;
      }
      return NoneSprite;
    }();
  }
};

} // namespace ecs::benchmarks::base::systems

#endif