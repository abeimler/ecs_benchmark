#ifndef ECS_BENCHMARKS_GAIA_ECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_DATASYSTEM_H_

#include "base/systems/DataSystem.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <gaia.h>
#include <gsl-lite/gsl-lite.hpp>
#include <string>

namespace ecs::benchmarks::gaia_ecs::systems {

class DataSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;

  void OnCreated() override { m_q = world().query().all<ecs::benchmarks::base::components::DataComponent&>(); }

  void OnUpdate() override {
    using DataComponent = ecs::benchmarks::base::components::DataComponent;
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](ecs::benchmarks::base::components::DataComponent& data) {
      data.dingy += 0.0001 * dt;
      data.mingy = !data.mingy;
      data.thingy++;
      /// @FIXME(pico_ecs): SIGSEGV (Segmentation fault), can't copy string ... support for components with dynamic
      /// memory (std::string) ?
      // data.stringy = fmt::format(FMT_STRING("{:4.2f}"), data[i].dingy);
      std::string stringy = fmt::format("{:4.2f}", data.dingy);
      std::char_traits<char>::copy(data.stringy, stringy.data(),
                                   std::min(stringy.length(), DataComponent::StringyMaxLength));
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
