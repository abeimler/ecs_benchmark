#ifndef ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
#define ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_

#include <utility>

#include "ExtendedECSBenchmark.h"

#include "mustache/systems/DataSystem.h"
#include "mustache/systems/MoreComplexSystem.h"
#include "mustache/systems/MovementSystem.h"
#include "mustache/entities/EntityFactory.h"
#include "mustache/MustacheApplication.h"

namespace ecs::benchmarks::mustache {

    class MustacheBenchmarkSuite final
            : public ecs::benchmarks::base::ExtendedECSBenchmark<"mustache", MustacheApplication, entities::EntityFactory> {
    public:
        MustacheBenchmarkSuite() = default;

        explicit MustacheBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ExtendedECSBenchmark(std::move(options)) {}


        void BM_IterateSingleComponent(benchmark::State& state) {
          using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

          BM_IterateSingleComponentCustom(state, [](auto& entities) {
              //auto& arch = entities.template getArchetype<ComponentOne>();
              const auto run_mode = ::mustache::JobRunMode::kCurrentThread;
              entities.forEach(
                      [](ComponentOne& comp) {
                          dummy_each(comp);
                      },
                      run_mode);
          });
        }

        void BM_IterateTwoComponents(benchmark::State& state) {
          using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
          using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

          BM_IterateTwoComponentsCustom(state, [](auto& entities) {
            const auto run_mode = ::mustache::JobRunMode::kCurrentThread;
            entities.forEach(
                [](ComponentOne& comp, ComponentTwo& comp2) {
                  dummy_each(comp, comp2);
                },
                run_mode);
          });
        }

        void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
          using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
          using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
          using ComponentThree = ecs::benchmarks::base::components::DataComponent;

          BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [](auto& entities) {
            const auto run_mode = ::mustache::JobRunMode::kCurrentThread;
            entities.forEach(
                [](ComponentOne& comp, ComponentTwo& comp2, ComponentThree& comp3) {
                  dummy_each(comp, comp2, comp3);
                },
                run_mode);
          });
        }
    };

}

#endif //ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
