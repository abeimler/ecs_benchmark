#ifndef ECS_BENCHMARKS_ENTT_STABLEAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_STABLEAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/StableMovementSystem.h"

namespace ecs::benchmarks::entt {
    class StableEnttApplication final
            : public ecs::benchmarks::base::Application<::entt::registry, float, systems::StableMovementSystem, systems::DataSystem, systems::MoreComplexSystem> {
    public:
        StableEnttApplication() = default;
        explicit StableEnttApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}
        ~StableEnttApplication() = default;
        StableEnttApplication(const StableEnttApplication &) = delete;
        StableEnttApplication &operator=(const StableEnttApplication &) = delete;
        StableEnttApplication(StableEnttApplication &&) = default;
        StableEnttApplication &operator=(StableEnttApplication &&) = default;
    };
}

#endif //ECS_BENCHMARKS_ENTT_STABLEAPPLICATION_H_
