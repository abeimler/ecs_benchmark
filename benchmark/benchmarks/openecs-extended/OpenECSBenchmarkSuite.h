#ifndef ECS_BENCHMARKS_OPENECSBENCHMARK_H_
#define ECS_BENCHMARKS_OPENECSBENCHMARK_H_

#include <utility>

#include "openecs/systems/DataSystem.h"
#include "openecs/systems/MoreComplexSystem.h"
#include "openecs/systems/MovementSystem.h"
#include "openecs/entities/EntityFactory.h"
#include "openecs/OpenECSApplication.h"

#include "ExtendedECSBenchmark.h"

namespace ecs::benchmarks::openecs {

    class OpenECSBenchmarkSuite final
            : public ecs::benchmarks::base::ExtendedECSBenchmark<"openecs", OpenECSApplication, entities::EntityFactory> {
    public:
        OpenECSBenchmarkSuite() = default;

        explicit OpenECSBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ExtendedECSBenchmark(std::move(options)) {}

        /*
        base::ComponentsCounter
        initApplicationWithMixedComponents(OpenECSApplication &app, size_t nentities, std::vector<Entity> &out) {
            app.init();
            /// @FIXME: SIGSEGV (Segmentation fault), can remove component(s) when createEntitiesWithMixedComponents
            return this->template createEntitiesWithMixedComponentsFromEmpty<entities::EntityFactory>(app.getEntities(), nentities, out);
        }
        */

        void BM_IterateSingleComponent(benchmark::State &state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

            BM_IterateSingleComponentCustom(state, [](auto& entities) {
                entities.with([](ComponentOne& comp){
                    dummy_each(comp);
                });
            });
        }

        void BM_IterateTwoComponents(benchmark::State &state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
            using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

            BM_IterateTwoComponentsCustom(state, [](auto& entities) {
                entities.with([](ComponentOne& comp, ComponentTwo& comp2) {
                    dummy_each(comp, comp2);
                });
            });
        }

        void BM_IterateThreeComponentsWithMixedEntities(benchmark::State &state) {
            using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
            using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
            using ComponentThree = ecs::benchmarks::base::components::DataComponent;

            BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [](auto& entities) {
                entities.with([](ComponentOne& comp, ComponentTwo& comp2, ComponentThree& comp3) {
                    dummy_each(comp, comp2, comp3);
                });
            });
        }
    };

}

#endif //ECS_BENCHMARKS_OPENECSBENCHMARK_H_
