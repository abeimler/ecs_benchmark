#ifndef ECS_BENCHMARKS_FLECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_FLECS_DATASYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/DataSystem.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <gsl-lite/gsl-lite.hpp>
#include <string>

namespace ecs::benchmarks::flecs::systems {

class DataSystem {
public:
  using Entity = ::flecs::entity;

  using TimeDelta = double;
  inline static const auto update = [](::flecs::iter& it,
                                       ecs::benchmarks::base::components::DataComponent* data) {
    using DataComponent = ecs::benchmarks::base::components::DataComponent;
    const auto dt = gsl::narrow_cast<TimeDelta>(it.delta_time());

    for (auto i : it) {
      data[i].dingy += 0.0001 * dt;
      data[i].mingy = !data[i].mingy;
      data[i].thingy++;
      /// @FIXME(pico_ecs): SIGSEGV (Segmentation fault), can't copy string ... support for components with dynamic memory
      /// (std::string) ?
      // data.stringy = fmt::format(FMT_STRING("{:4.2f}"), data[i].dingy);
      std::string stringy = fmt::format(FMT_STRING("{:4.2f}"), data[i].dingy);
      std::char_traits<char>::copy(data[i].stringy, stringy.data(),
                                  std::min(stringy.length(), DataComponent::StringyMaxLength));
    }
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
