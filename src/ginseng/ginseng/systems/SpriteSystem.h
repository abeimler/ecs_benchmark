#ifndef ECS_BENCHMARKS_GINSENG_SPRITESYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_SPRITESYSTEM_H_

#include "base/systems/SpriteSystem.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::systems {

class SpriteSystem final : public ecs::benchmarks::base::systems::SpriteSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::ginseng::systems

#endif