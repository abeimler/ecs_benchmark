#ifndef ECS_BENCHMARKS_GAIA_COMPONENTS_SOAPOSITIONCOMPONENT_H_
#define ECS_BENCHMARKS_GAIA_COMPONENTS_SOAPOSITIONCOMPONENT_H_

#include "base/components/PositionComponent.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::components {

struct SoAPositionComponent {
  float x{0.0F};
  float y{0.0F};

  static constexpr auto Layout = ::gaia::mem::DataLayout::SoA;
};

} // namespace ecs::benchmarks::gaia_ecs::components

#endif