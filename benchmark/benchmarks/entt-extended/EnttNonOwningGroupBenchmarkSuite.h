#ifndef ECS_BENCHMARKS_ENTTNONOWNINGGROUPBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTNONOWNINGGROUPBENCHMARK_H_

#include <utility>

#include "entt/entities/EntityFactory.h"
#include "entt/EnttGroupApplication.h"

#include "ExtendedECSBenchmark.h"

namespace ecs::benchmarks::entt {

    class EnttNonOwningGroupBenchmarkSuite final
            : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (group, non-owning)", EnttGroupApplication, entities::EntityFactory> {
    public:
        EnttNonOwningGroupBenchmarkSuite() = default;

        explicit EnttNonOwningGroupBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ExtendedECSBenchmark(std::move(options)) {}

        void BM_IterateTwoComponents(benchmark::State& state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
            using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

            BM_IterateTwoComponentsWithPreCreatedView(state, [](auto& registry) {
                return registry.template group<>(::entt::get<ComponentOne, ComponentTwo>);
            });
        }

        void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
            using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
            using ComponentThree = ecs::benchmarks::base::components::DataComponent;

            BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, [](auto& registry) {
                return registry.template group<>(::entt::get<ComponentOne, ComponentTwo, ComponentThree>);
            });
        }
    };

}

#endif //ECS_BENCHMARKS_ENTTNONOWNINGGROUPBENCHMARK_H_
