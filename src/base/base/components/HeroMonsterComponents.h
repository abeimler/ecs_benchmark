#ifndef ECS_BENCHMARKS_BASE_COMPONENTS_HEROMONSTERCOMPONENT_H_
#define ECS_BENCHMARKS_BASE_COMPONENTS_HEROMONSTERCOMPONENT_H_

#include "base/random.h"

namespace ecs::benchmarks::base::components {

enum class PlayerType { NPC, Monster, Hero };

struct PlayerComponent {
  ecs::benchmarks::base::random_xoshiro128 rng{};
  PlayerType type{PlayerType::NPC};
};

enum class StatusEffect { Spawn, Dead, Alive };
struct HealthComponent {
  int32_t hp{0};
  int32_t maxhp{0};
  StatusEffect status{StatusEffect::Spawn};
};

struct DamageComponent {
  int32_t atk{0};
  int32_t def{0};
};

} // namespace ecs::benchmarks::base::components

#endif