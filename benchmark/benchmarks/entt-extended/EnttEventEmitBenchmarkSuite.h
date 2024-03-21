#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/EnttApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

struct Event {
  ::entt::entity entity;
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
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    auto& comp1 = m_registry.get<ComponentOne>(event.entity);
    auto& comp2 = m_registry.get<ComponentTwo>(event.entity);

    benchmark::DoNotOptimize(comp1);
    benchmark::DoNotOptimize(comp2);
    //benchmark::DoNotOptimize(event);
  }

private:
  ::entt::registry& m_registry;
  ::entt::dispatcher& m_dispatcher;
};

class EnttEventEmitBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (emit)", EnttApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  EnttEventEmitBenchmarkSuite() = default;

  explicit EnttEventEmitBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_TriggerAndUpdateEventsViaDispatcherWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    EnttApplication::Application app(this->m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(registry, nentities, entities);

    ::entt::dispatcher dispatcher{};
    DummyListener listener (registry, dispatcher);

    listener.setup();

    auto view = registry.template view<ComponentOne, ComponentTwo>();
    for (auto _ : state) {
      view.each([&](auto entity, auto& /*comp1*/, auto& /*comp2*/) {
        //dummy_each(comp1, comp2);
        dispatcher.trigger<Event>({.entity = entity});
      });
    }

    listener.teardown();

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTBENCHMARK_H_
