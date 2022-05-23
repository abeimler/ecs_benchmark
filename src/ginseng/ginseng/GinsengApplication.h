#ifndef ECS_BENCHMARKS_GINSENG_APPLICATION_H_
#define ECS_BENCHMARKS_GINSENG_APPLICATION_H_

#include <ginseng/ginseng.hpp>

#include "base/Application.h"

#include "systems/ComflabSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::ginseng {
    class GinsengApplication final
            : public ecs::benchmarks::base::Application<::ginseng::database, float, systems::MovementSystem, systems::ComflabSystem, systems::MoreComplexSystem> {
    public:
        GinsengApplication() = default;
        explicit GinsengApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}
        ~GinsengApplication() = default;
        GinsengApplication(const GinsengApplication &) = delete;
        GinsengApplication &operator=(const GinsengApplication &) = delete;
        GinsengApplication(GinsengApplication &&) = default;
        GinsengApplication &operator=(GinsengApplication &&) = default;
    };
}

#endif //ECS_BENCHMARKS_GINSENG_APPLICATION_H_
