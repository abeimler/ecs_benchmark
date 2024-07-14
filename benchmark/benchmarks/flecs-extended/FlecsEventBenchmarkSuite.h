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
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"flecs (enqueue)", FlecsApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  FlecsEventBenchmarkSuite() = default;

  explicit FlecsEventBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_EnqueueAndUpdateEventsViaObserverWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    FlecsApplication app(this->m_options.add_more_complex_system);
    ::flecs::world& ecs = app.getEntities();

    // Create observer for custom event
    ecs.observer<ComponentOne, ComponentTwo>()
        .event<EventComponent>()
        .each([](::flecs::iter& /*it*/, size_t /*i*/, ComponentOne& comp1, ComponentTwo& comp2) {
          dummy_each(comp1, comp2);
        });

    // The observer filter can be matched against the entity, so make sure it
    // has the Position component before emitting the event. This does not
    // trigger the observer yet.
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(ecs, nentities, entities);

    auto q = ecs.query<ComponentOne, ComponentTwo>();
    for (auto _ : state) {
      // We can only call enqueue events while the world is deferred mode.
      ecs.defer_begin();
      q.each([&](::flecs::entity e, ComponentOne& comp1, ComponentTwo& comp2) {
        dummy_each(comp1, comp2);
        // Emit the custom event
        ecs.event<EventComponent>()
            .id<ComponentOne, ComponentTwo>()
            .entity(e)
            .enqueue();
      });
      // Flushes the queue, and invokes the observer
      ecs.defer_end();
      /// @FIXME: flecs_emit: idr = flecs_query_id_record_get(world, id); idr is NULL
    }

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }

};

} // namespace ecs::benchmarks::flecs

#endif // ECS_BENCHMARKS_FLECSBENCHMARK_H_
