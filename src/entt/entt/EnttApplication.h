#ifndef ECS_BENCHMARKS_ENTT_APPLICATION_H_
#define ECS_BENCHMARKS_ENTT_APPLICATION_H_

#include <entt/entt.hpp>

#include "base/Application.h"

#include "systems/ComflabSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::entt {
    class EnttApplication final
            : public ecs::benchmarks::base::Application<::entt::registry, float, systems::MovementSystem, systems::ComflabSystem, systems::MoreComplexSystem> {
    public:
        EnttApplication() = default;

        explicit EnttApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}

        ~EnttApplication() = default;

        EnttApplication(const EnttApplication &) = delete;

        EnttApplication &operator=(const EnttApplication &) = delete;

        EnttApplication(EnttApplication &&) = default;

        EnttApplication &operator=(EnttApplication &&) = default;
    };
}

#endif //ECS_BENCHMARKS_ENTT_APPLICATION_H_
