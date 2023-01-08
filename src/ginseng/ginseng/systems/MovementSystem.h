#ifndef ECS_BENCHMARKS_GINSENG_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_MOVEMENTSYSTEM_H_

#include "base/systems/MovementSystem.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::systems {

class MovementSystem final : public ecs::benchmarks::base::systems::MovementSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::ginseng::systems

#endif