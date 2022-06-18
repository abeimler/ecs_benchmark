#ifndef ECS_BENCHMARKS_ENTTRUNTIMEBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTRUNTIMEBENCHMARK_H_

#include <utility>

#include "ExtendedECSBenchmark.h"

#include "entt/entities/EntityFactory.h"
#include "entt/EnttRuntimeApplication.h"

namespace ecs::benchmarks::entt {

    class EnttRuntimeBenchmarkSuite final
            : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (runtime)", EnttRuntimeApplication, entities::EntityFactory> {
    public:
        EnttRuntimeBenchmarkSuite() = default;

        explicit EnttRuntimeBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ExtendedECSBenchmark(std::move(options)) {}

        void BM_IterateSingleComponent(benchmark::State& state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

            BM_IterateSingleComponentWithPreCreatedViewCustom(state, [](auto& registry) {
                    ::entt::runtime_view view{};
                    view.iterate(registry.template storage<ComponentOne>());
                    return view;
                },
                [&](auto& registry, auto& view) {
                    view.each([&](auto entity){
                        auto& comp = registry.template get<ComponentOne>(entity);
                        dummy_each(comp);
                    });
                });
        }

        void BM_IterateTwoComponents(benchmark::State& state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
            using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

            BM_IterateTwoComponentsWithPreCreatedViewCustom(state, [](auto& registry) {
                    ::entt::runtime_view view{};
                    view.iterate(registry.template storage<ComponentOne>())
                        .iterate(registry.template storage<ComponentTwo>());
                    return view;
                },
                [&](auto& registry, auto& view) {
                    view.each([&](auto entity) {
                        auto& comp = registry.template get<ComponentOne>(entity);
                        auto& comp2 = registry.template get<ComponentTwo>(entity);
                        dummy_each(comp, comp2);
                    });
                });
        }

        void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
          using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
          using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
          using ComponentThree = ecs::benchmarks::base::components::VelocityComponent;

          BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedViewCustom(state, [](auto& registry) {
                ::entt::runtime_view view{};
                view.iterate(registry.template storage<ComponentOne>())
                    .iterate(registry.template storage<ComponentTwo>())
                    .iterate(registry.template storage<ComponentThree>());
                return view;
            },
            [&](auto& registry, auto& view) {
                view.each([&](auto entity) {
                    auto& comp = registry.template get<ComponentOne>(entity);
                    auto& comp2 = registry.template get<ComponentTwo>(entity);
                    dummy_each(comp, comp2);
                });
            });
        }
    };

}

#endif //ECS_BENCHMARKS_ENTTRUNTIMEBENCHMARK_H_
