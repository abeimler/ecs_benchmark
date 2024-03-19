#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/EnttApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

template<class Event>
struct DummyListener {
  void receive(Event& event) { benchmark::DoNotOptimize(event); }
};

class EnttBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt", EnttApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  EnttBenchmarkSuite() = default;

  explicit EnttBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentCustom(state, [](auto& registry) {
      auto& storage = registry.template storage<ComponentOne>();
      std::for_each(storage.begin(), storage.end(), [](auto& comp) {
        dummy_each(comp);
      });
    });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsWithPreCreatedView(state, [](auto& registry) {
      return registry.template view<ComponentOne, ComponentTwo>();
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, [](auto& registry) {
      return registry.template view<ComponentOne, ComponentTwo, ComponentThree>();
    });
  }

  void BM_PublishEventViaComponentWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    BM_PublishEventViaComponentWithMixedEntitiesViews(
        state,
        [](auto& registry) {
          return registry.template view<ComponentOne, ComponentTwo>();
        });
  }
  void BM_PublishEventAndProgressEventViaComponentWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    BM_PublishEventAndProgressEventViaComponentWithMixedEntitiesViews(
      state,
      [](auto& registry) {
        return registry.template view<ComponentOne, ComponentTwo>();
      },
      [](auto& registry) {
        return registry.template view<ComponentOne, ComponentTwo, EventComponent>();
      });
  }

  void BM_PublishEventAndProgressEventViaDispatcherWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    EnttApplication::Application app(this->m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(registry, nentities, entities);

    ::entt::dispatcher dispatcher{};
    DummyListener<EventComponent> listener;
    dispatcher.sink<EventComponent>().connect<&DummyListener<EventComponent>::receive>(listener);

    auto view = registry.template view<ComponentOne, ComponentTwo>();
    for (auto _ : state) {
      view.each([&](auto /*entity*/, auto& comp1, auto& comp2) {
        dummy_each(comp1, comp2);
        dispatcher.enqueue<EventComponent>({});
      });
      dispatcher.update();
    }

    dispatcher.sink<EventComponent>().disconnect<&DummyListener<EventComponent>::receive>(listener);

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }
  void BM_PublishEventViaDispatcherWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    EnttApplication::Application app(this->m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(registry, nentities, entities);

    ::entt::dispatcher dispatcher{};
    DummyListener<EventComponent> listener;
    dispatcher.sink<EventComponent>().connect<&DummyListener<EventComponent>::receive>(listener);

    auto view = registry.template view<ComponentOne, ComponentTwo>();
    for (auto _ : state) {
      view.each([&](auto /*entity*/, auto& comp1, auto& comp2) {
        dummy_each(comp1, comp2);
        dispatcher.enqueue<EventComponent>({});
      });
    }

    dispatcher.sink<EventComponent>().disconnect<&DummyListener<EventComponent>::receive>(listener);

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }

  void BM_EnqueueEventViaDispatcherWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    EnttApplication::Application app(this->m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(registry, nentities, entities);

    ::entt::dispatcher dispatcher{};
    DummyListener<EventComponent> listener;
    dispatcher.sink<EventComponent>().connect<&DummyListener<EventComponent>::receive>(listener);

    auto view = registry.template view<ComponentOne, ComponentTwo>();
    view.each([&](auto /*entity*/, auto& comp1, auto& comp2) {
      dummy_each(comp1, comp2);
      dispatcher.enqueue<EventComponent>({});
    });
    state.counters["events_count"] = static_cast<double>(dispatcher.size());

    for (auto _ : state) {
      dispatcher.update();
    }

    dispatcher.sink<EventComponent>().disconnect<&DummyListener<EventComponent>::receive>(listener);

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTBENCHMARK_H_
