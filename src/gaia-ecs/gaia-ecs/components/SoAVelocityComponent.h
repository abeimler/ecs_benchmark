#ifndef ECS_BENCHMARKS_GAIA_COMPONENTS_SOAVELOCITYCOMPONENT_H_
#define ECS_BENCHMARKS_GAIA_COMPONENTS_SOAVELOCITYCOMPONENT_H_

#include "base/components/VelocityComponent.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::components {

struct SoAVelocityComponent {
  double x{1.0};
  double y{1.0};

  static constexpr auto Layout = ::gaia::mem::DataLayout::SoA;
};

} // namespace ecs::benchmarks::gaia_ecs::components

#endif