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

  using TimeDelta = float;
  inline static const auto update = [](::flecs::iter& it, size_t /*index*/,
                                       ecs::benchmarks::base::components::DataComponent& data) {
    using DataComponent = ecs::benchmarks::base::components::DataComponent;
    const TimeDelta dt = it.delta_time();

    data.dingy += 0.0001 * gsl::narrow_cast<double>(dt);
    data.mingy = !data.mingy;
    data.thingy++;
    /// @FIXME(pico_ecs): SIGSEGV (Segmentation fault), can't copy string ... support for components with dynamic memory
    /// (std::string) ?
    // data.stringy = fmt::format(FMT_STRING("{:4.2f}"), data.dingy);
    std::string stringy = fmt::format("{:4.2f}", data.dingy);
    std::char_traits<char>::copy(gsl::span<char>(data.stringy).data(), gsl::span<const char>(stringy).data(),
                                 std::min(stringy.length(), DataComponent::StringyMaxLength));
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif