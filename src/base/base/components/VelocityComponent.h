#ifndef ECS_BENCHMARKS_BASE_COMPONENTS_VELOCITYCOMPONENT_H_
#define ECS_BENCHMARKS_BASE_COMPONENTS_VELOCITYCOMPONENT_H_

namespace ecs::benchmarks::base::components {

struct VelocityComponent {
  double x{1.0};
  double y{1.0};
};

} // namespace ecs::benchmarks::base::components

#endif