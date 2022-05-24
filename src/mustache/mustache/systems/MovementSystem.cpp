#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::mustache::systems {

    void MovementSystem::update(::mustache::World &world, TimeDelta dt) {
        constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
        world.entities().forEach([dt](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent &position,
                                      ecs::benchmarks::base::components::DirectionComponent &direction) {
            updatePosition(position, direction, dt);
        }, run_mode);
    }

    void MovementSystem::onUpdate(::mustache::World &world) {
        constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
        world.entities().forEach([](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent &position,
                                    ecs::benchmarks::base::components::DirectionComponent &direction) {
            constexpr float dt = 1.0F / 60.0F;
            updatePosition(position, direction, dt);
        }, run_mode);
    }
}