#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::mustache::systems {

    void MoreComplexSystem::update(::mustache::World& world, TimeDelta dt) {
        constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
        world.entities().forEach([this, dt](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent &position, ecs::benchmarks::base::components::DirectionComponent &direction, ecs::benchmarks::base::components::ComflabulationComponent &comflab) {
            updateComponents(position, direction, comflab, dt);
        }, run_mode);
    }

    void MoreComplexSystem::onUpdate(::mustache::World& world) {
        constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
        world.entities().forEach([this](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent &position, ecs::benchmarks::base::components::DirectionComponent &direction, ecs::benchmarks::base::components::ComflabulationComponent &comflab) {
            constexpr float dt = 1.0F / 60.0F;
            updateComponents(position, direction, comflab, dt);
        }, run_mode);
    }
}