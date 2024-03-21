#ifndef ECS_BENCHMARKS_FLECSEVENTBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSEVENTBENCHMARK_H_

#include "base/components/EmptyComponent.h"
#include "ExtendedECSBenchmark.h"
#include "flecs/FlecsApplication.h"
#include "flecs/entities/EntityFactory.h"
#include "flecs/entities/HeroMonsterEntityFactory.h"
#include "flecs/systems/DataSystem.h"
#include "flecs/systems/MoreComplexSystem.h"
#include "flecs/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::flecs {

class FlecsEventBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"flecs (emit)", FlecsApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  FlecsEventBenchmarkSuite() = default;

  explicit FlecsEventBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_EmitAndUpdateEventsViaObserverWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    FlecsApplication app(this->m_options.add_more_complex_system);
    ::flecs::world& ecs = app.getEntities();

    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(ecs, nentities, entities);

    auto q = ecs.query<ComponentOne, ComponentTwo>();
    q.each([&](::flecs::entity e, ComponentOne& /*comp1*/, ComponentTwo& /*comp2*/) {
      e.observe<EventComponent>([&](::flecs::entity src) {
        auto& comp1 = this->m_entities_factory.getComponentOne(ecs, src);
        auto& comp2 = this->m_entities_factory.getComponentTwo(ecs, src);
        dummy_each(comp1, comp2);
      });
    });

    for (auto _ : state) {
      q.each([&](::flecs::entity e, ComponentOne& /*comp1*/, ComponentTwo& /*comp2*/) {
        e.emit<EventComponent>();
      });
    }

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }
};

} // namespace ecs::benchmarks::flecs

#endif // ECS_BENCHMARKS_FLECSBENCHMARK_H_
