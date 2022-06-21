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

        void BM_SystemsUpdateMixedEntities(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            std::vector<Entity> entities;
            Application app(m_options.add_more_complex_system);
            const ComponentsCounter components_counter = initApplicationWithMixedComponents(app, nentities, entities);
            for (auto _: state) {
                app.update(fakeTimeDelta);
            }
            this->setCounters(state, entities, components_counter);
            afterBenchmark(app);
            uninitApplication(app);
        }
    };

}

#endif //ECS_BENCHMARKS_OPENECSBENCHMARK_H_
