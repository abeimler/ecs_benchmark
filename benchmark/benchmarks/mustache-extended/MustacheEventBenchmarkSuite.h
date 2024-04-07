#ifndef ECS_BENCHMARKS_MUSTACHEEVENTBENCHMARK_H_
#define ECS_BENCHMARKS_MUSTACHEEVENTBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "mustache/MustacheApplication.h"
#include "mustache/entities/EntityFactory.h"
#include "mustache/entities/HeroMonsterEntityFactory.h"
#include "mustache/systems/DataSystem.h"
#include "mustache/systems/MoreComplexSystem.h"
#include "mustache/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::mustache {

struct Event {
  ::mustache::Entity entity;
};

struct DummyEventSystem : public ::mustache::System<DummyEventSystem>, public ::mustache::Receiver<Event> {
  void onConfigure(::mustache::World& world, ::mustache::SystemConfig& config) override {
    /// FIXME: Error at mustache/ecs/event_manager.hpp:85:22
    //world.events().subscribe<Event>(this);
    world.events().subscribe<Event>([&](const Event &e) {
      using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
      using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
      benchmark::DoNotOptimize(*world.entities().getComponent<ComponentOne,
                                        ::mustache::FunctionSafety::kUnsafe>(e.entity));
      benchmark::DoNotOptimize(*world.entities().getComponent<ComponentTwo,
                                                   ::mustache::FunctionSafety::kUnsafe>(e.entity));
    });
  }
  void onEvent(const Event &e) {
    benchmark::DoNotOptimize(e.entity.id());
  }
};

class PostEventSystem : public ::mustache::System<PostEventSystem> {
public:
  void onUpdate(::mustache::World& world) override {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    world.entities().forEach([&](::mustache::Entity entity, const ComponentOne& pos, const ComponentTwo& vel){
      world.events().post(Event{entity});
    });
  }
};


class MustacheEventBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"mustache (event)", MustacheApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  MustacheEventBenchmarkSuite() = default;

  explicit MustacheEventBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_PostAndUpdateEventsViaReceiverWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    const auto nentities = static_cast<size_t>(state.range(0));
    ::mustache::World world;
    auto& manager = world.entities();
    std::vector<Entity> entities;
    const base::ComponentsCounter components_counter =
        this->template createEntitiesWithMixedComponents<entities::EntityFactory>(manager, nentities, entities);

    const auto consumeEvent = [&](const Event &e) {
      using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
      using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
      benchmark::DoNotOptimize(*world.entities().getComponent<ComponentOne,
                                                              ::mustache::FunctionSafety::kUnsafe>(e.entity));
      benchmark::DoNotOptimize(*world.entities().getComponent<ComponentTwo,
                                                              ::mustache::FunctionSafety::kUnsafe>(e.entity));
    };
    ///@FIXME: add onUpdate ?
    world.systems().addSystem<PostEventSystem>();
    //world.systems().addSystem<DummyEventSystem>();
    world.events().subscribe<Event>(consumeEvent);
    world.init();

    for (auto _ : state) {
      world.update();
    }

    this->setCounters(state, entities, components_counter);
    //state.counters["events_count"] = static_cast<double>(entities.size());
  }
};

} // namespace ecs::benchmarks::mustache

#endif // ECS_BENCHMARKS_MUSTACHEEVENTBENCHMARK_H_
