#ifndef ECS_BENCHMARKS_ENTT_COMPONENTS_VELOCITYPOSITIONCOMPONENT_H_
#define ECS_BENCHMARKS_ENTT_COMPONENTS_VELOCITYPOSITIONCOMPONENT_H_

#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::components {

struct StableVelocityComponent : ecs::benchmarks::base::components::VelocityComponent {
  static constexpr auto in_place_delete = true;
};

} // namespace ecs::benchmarks::entt::components

#endif