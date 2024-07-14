#ifndef ECS_BENCHMARKS_ENTTSTABLEEVENTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTSTABLEEVENTBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/StableEnttApplication.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include "entt/entities/StableEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

struct Event {
  using ComponentOne = ecs::benchmarks::entt::components::StablePositionComponent;
  using ComponentTwo = ecs::benchmarks::entt::components::StableVelocityComponent;

  ComponentOne* comp1;
  ComponentTwo* comp2;
};

struct DummyListener {
public:
  DummyListener(::entt::registry& registry,
                ::entt::dispatcher& dispatcher) : m_registry(registry), m_dispatcher(dispatcher) {}

  void setup() {
    m_dispatcher.sink<Event>().connect<&DummyListener::receive>(*this);
  }
  void teardown() {
    m_dispatcher.sink<Event>().disconnect<&DummyListener::receive>(*this);
  }

  void receive(Event& event) {
    benchmark::DoNotOptimize(*event.comp1);
    benchmark::DoNotOptimize(*event.comp2);
    //benchmark::DoNotOptimize(event);
  }

private:
  ::entt::registry& m_registry;
  ::entt::dispatcher& m_dispatcher;
};

class EnttStableEventEmitBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (emit, stable)", StableEnttApplication, entities::StableEntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  EnttStableEventEmitBenchmarkSuite() = default;

  explicit EnttStableEventEmitBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_TriggerAndUpdateEventsViaDispatcherWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::entt::components::StablePositionComponent;
    using ComponentTwo = ecs::benchmarks::entt::components::StableVelocityComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    StableEnttApplication::Application app(this->m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::StableEntityFactory>(registry, nentities, entities);

    ::entt::dispatcher dispatcher{};
    DummyListener listener (registry, dispatcher);

    listener.setup();

    auto view = registry.template view<ComponentOne, ComponentTwo>();
    for (auto _ : state) {
      view.each([&](auto /*entity*/, auto& comp1, auto& comp2) {
        //dummy_each(comp1, comp2);
        dispatcher.trigger<Event>({.comp1 = &comp1, .comp2 = &comp2});
      });
    }

    listener.teardown();

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTSTABLEEVENTBENCHMARK_H_
