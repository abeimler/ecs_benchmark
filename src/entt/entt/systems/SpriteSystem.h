#ifndef ECS_BENCHMARKS_ENTT_SPRTIE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_SPRTIE_MORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/SpriteSystem.h"

namespace ecs::benchmarks::entt::systems {

class SpriteSystem final : public ecs::benchmarks::base::systems::SpriteSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif