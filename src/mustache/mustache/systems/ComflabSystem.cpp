#include "ComflabSystem.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::mustache::systems {

    void ComflabSystem::update(::mustache::World &world, TimeDelta dt) {
        constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
        world.entities().forEach(
                [dt](Entity /*entity*/, ecs::benchmarks::base::components::ComflabulationComponent &comflab) {
                    updateComflabulation(comflab, dt);
                }, run_mode);
    }

    void ComflabSystem::onUpdate(::mustache::World &world) {
        constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
        world.entities().forEach(
                [](Entity /*entity*/, ecs::benchmarks::base::components::ComflabulationComponent &comflab) {
                    constexpr float dt = 1.0F / 60.0F;
                    updateComflabulation(comflab, dt);
                }, run_mode);
    }

}