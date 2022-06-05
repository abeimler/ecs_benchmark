#ifndef ECS_BENCHMARKS_ENTT_RUNTIMEAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_RUNTIMEAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"

#include "systems/RuntimeDataSystem.h"
#include "systems/RuntimeMoreComplexSystem.h"
#include "systems/RuntimeMovementSystem.h"

namespace ecs::benchmarks::entt {
    class EnttRuntimeApplication final
            : public ecs::benchmarks::base::Application<::entt::registry, float, systems::RuntimeMovementSystem, systems::RuntimeDataSystem, systems::RuntimeMoreComplexSystem> {
    public:
        EnttRuntimeApplication() = default;

        explicit EnttRuntimeApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}

        ~EnttRuntimeApplication() = default;

        EnttRuntimeApplication(const EnttRuntimeApplication &) = delete;

        EnttRuntimeApplication &operator=(const EnttRuntimeApplication &) = delete;

        EnttRuntimeApplication(EnttRuntimeApplication &&) = default;

        EnttRuntimeApplication &operator=(EnttRuntimeApplication &&) = default;
    };
}

#endif //ECS_BENCHMARKS_ENTT_RUNTIMEAPPLICATION_H_
