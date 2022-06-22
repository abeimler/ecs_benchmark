#ifndef ECS_BENCHMARKS_OPENECSBENCHMARK_H_
#define ECS_BENCHMARKS_OPENECSBENCHMARK_H_

#include "ECSBenchmark.h"

#include <utility>

#include "openecs/systems/DataSystem.h"
#include "openecs/systems/MoreComplexSystem.h"
#include "openecs/systems/MovementSystem.h"
#include "openecs/entities/EntityFactory.h"
#include "openecs/OpenECSApplication.h"

namespace ecs::benchmarks::openecs {

    class OpenECSBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"openecs", OpenECSApplication, entities::EntityFactory> {
    public:
        OpenECSBenchmarkSuite() = default;

        explicit OpenECSBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}

        /*
        base::ComponentsCounter
        initApplicationWithMixedComponents(OpenECSApplication &app, size_t nentities, std::vector<Entity> &out) {
            /// @FIXME: SIGSEGV (Segmentation fault), can remove component(s) when createEntitiesWithMixedComponents
            const auto ret = this->template createEntitiesWithMixedComponentsFromEmpty<entities::EntityFactory>(app.getEntities(), nentities, out);
            app.init();
            return ret;
        }
        */
    };

}

#endif //ECS_BENCHMARKS_OPENECSBENCHMARK_H_
