#ifndef ECS_BENCHMARKS_MOREECSBENCHMARK_H_
#define ECS_BENCHMARKS_MOREECSBENCHMARK_H_

#include "ECSBenchmark.h"
#include <benchmark/benchmark.h>
#include <concepts>

namespace ecs::benchmarks::base {

template <typename Iterable, typename Func>
concept HasEach = requires(Iterable it, Func func) { it.each(func); };
template <typename Iterable, typename Func>
concept HasForEach = requires(Iterable it, Func func) { it.for_each(func); };
template <typename Iterable, typename Func>
concept HasVisit = requires(Iterable it, Func func) { it.visit(func); };

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasClearComponentFeature = requires(EntityFactory factory, EntityManager& entity_manager, Entity entity) {
  factory.clearComponentsEmpty(entity_manager);
};
template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasAddComponentEmptyFeature = requires(EntityFactory factory, EntityManager& entity_manager, Entity entity) {
  factory.addComponentEmpty(entity_manager, entity);
};

template <StringLiteral Name, class Application, class EntityFactory, class HeroMonsterEntityFactory,
          ECSBenchmarkIncludeEntityBenchmarks include_entity_benchmarks = ECSBenchmarkIncludeEntityBenchmarks::No>
class ExtendedECSBenchmark
    : public ECSBenchmark<Name, Application, EntityFactory, HeroMonsterEntityFactory, include_entity_benchmarks> {
private:
  inline static constexpr auto default_initializable_entity_manager =
      std::default_initializable<typename EntityFactory::EntityManager>;

public:
  using EntityManager = typename EntityFactory::EntityManager;
  using Entity = typename EntityFactory::Entity;

  ExtendedECSBenchmark() = default;
  explicit ExtendedECSBenchmark(ESCBenchmarkOptions options)
      : ECSBenchmark<Name, Application, EntityFactory, HeroMonsterEntityFactory>(std::move(options)) {}
  virtual ~ExtendedECSBenchmark() = default;
  ExtendedECSBenchmark(const ExtendedECSBenchmark&) = default;
  ExtendedECSBenchmark& operator=(const ExtendedECSBenchmark&) = default;
  ExtendedECSBenchmark(ExtendedECSBenchmark&&) noexcept = default;
  ExtendedECSBenchmark& operator=(ExtendedECSBenchmark&&) noexcept = default;

protected:
  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponentWithPreCreatedView(benchmark::State& state, GetView&& get_view, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename Comp, typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponentWithPreCreatedView(benchmark::State& state, GetView&& get_view, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each<Comp>(view, func);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each<Comp>(view, func);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponentWithPreCreatedView(benchmark::State& state, GetView&& view) {
    BM_IterateSingleComponentWithPreCreatedView(state, view, [](auto&... comp) {
      dummy_each(comp...);
    });
  }

  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponent(benchmark::State& state, GetView get_view, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      for (auto _ : state) {
        generic_each(get_view(registry), func);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename Func>
  void BM_IterateSingleComponentCustom(benchmark::State& state, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);

      for (auto _ : state) {
        func(registry);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);

      for (auto _ : state) {
        func(registry);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename Comp, typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponent(benchmark::State& state, GetView&& get_view, Func&& func) {
    BM_IterateSingleComponentCustom(state, [&](auto& registry) {
      generic_each_comps<Comp>(get_view(registry), func);
    });
  }
  template <typename GetView>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponent(benchmark::State& state, GetView&& view) {
    BM_IterateSingleComponent(state, view, [](auto&... comp) {
      dummy_each(comp...);
    });
  }

  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateTwoComponentsWithPreCreatedView(benchmark::State& state, GetView&& get_view, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateTwoComponentsWithPreCreatedView(benchmark::State& state, GetView&& view) {
    BM_IterateTwoComponentsWithPreCreatedView(state, view, [](auto&... comp) {
      dummy_each(comp...);
    });
  }
  template <typename Func>
  void BM_IterateTwoComponentsCustom(benchmark::State& state, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);
      for (auto _ : state) {
        func(registry);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);
      for (auto _ : state) {
        func(registry);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateTwoComponents(benchmark::State& state, GetView&& get_view, Func&& func) {
    BM_IterateTwoComponentsCustom(state, [&](auto& registry) {
      generic_each(get_view(registry), func);
    });
  }
  template <typename GetView>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateTwoComponents(benchmark::State& state, GetView view) {
    BM_IterateTwoComponents(state, view, [](auto&... comp) {
      dummy_each(comp...);
    });
  }

  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(benchmark::State& state, GetView&& get_view,
                                                                   Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        generic_each(view, func);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(benchmark::State& state, GetView&& view) {
    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, view, [](auto&... comp) {
      dummy_each(comp...);
    });
  }
  template <typename Func>
  void BM_IterateThreeComponentsWithMixedEntitiesCustom(benchmark::State& state, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);
      for (auto _ : state) {
        func(registry);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);
      for (auto _ : state) {
        func(registry);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state, GetView&& get_view, Func&& func) {
    BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [&](auto& registry) {
      generic_each(get_view(registry), func);
    });
  }
  template <typename GetView>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state, GetView&& view) {
    BM_IterateThreeComponentsWithMixedEntities(state, view, [](auto&... comp) {
      dummy_each(comp...);
    });
  }


  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateSingleComponentWithPreCreatedViewCustom(benchmark::State& state, GetView&& get_view, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        func(registry, view);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithSingleComponent(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        func(registry, view);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateTwoComponentsWithPreCreatedViewCustom(benchmark::State& state, GetView&& get_view, Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        func(registry, view);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        func(registry, view);
      }
      this->setCounters(state, entities, components_counter);
    }
  }
  template <typename GetView, typename Func>
    requires std::invocable<GetView&, EntityManager&>
  void BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedViewCustom(benchmark::State& state, GetView&& get_view,
                                                                         Func&& func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        func(registry, view);
      }
      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);
      auto view = get_view(registry);
      for (auto _ : state) {
        func(registry, view);
      }
      this->setCounters(state, entities, components_counter);
    }
  }


    template <typename GetViewWithRegistry, typename PublishEventFunc>
      requires std::invocable<GetViewWithRegistry&, EntityManager&> && HasClearComponentFeature<EntityFactory>
    void BM_PublishEventViaComponentWithMixedEntitiesCustom(benchmark::State& state, GetViewWithRegistry&& get_view_with_registry,
                                                                            PublishEventFunc&& event_func) {
      const auto nentities = static_cast<size_t>(state.range(0));
      if constexpr (default_initializable_entity_manager) {
        EntityManager registry;
        std::vector<Entity> entities;
        const ComponentsCounter components_counter =
            this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);

        auto view = get_view_with_registry(registry);
        for (auto _ : state) {
          event_func(registry, view);
          this->m_entities_factory.clearComponentsEmpty(registry);
        }

        this->setCounters(state, entities, components_counter);
      } else {
        Application app(this->m_options.add_more_complex_system);
        EntityManager& registry = app.getEntities();
        std::vector<Entity> entities;
        const ComponentsCounter components_counter =
            this->createEntitiesWithMinimalComponents(registry, nentities, entities);

        auto view = get_view_with_registry(registry);
        for (auto _ : state) {
          event_func(registry, view);
          this->m_entities_factory.clearComponentsEmpty(registry);
        }

        this->setCounters(state, entities, components_counter);
        //state.counters["events_count"] = static_cast<double>(entities.size());
      }
    }
    template <typename GetViewWithRegistry, typename PublishEventFunc>
      requires std::invocable<GetViewWithRegistry&, EntityManager&> && HasClearComponentFeature<EntityFactory>
    void BM_PublishEventViaComponentWithMixedEntitiesViews(benchmark::State& state, GetViewWithRegistry&& get_view_with_registry, PublishEventFunc&& event_func) {
      BM_PublishEventViaComponentWithMixedEntitiesCustom(state, get_view_with_registry, [&](auto& registry, auto& view) {
        generic_each(view, [&](auto&&... comps){ event_func(std::forward<decltype(registry)>(registry), std::forward<decltype(comps)>(comps)...); });
      });
    }
    template <typename GetViewWithRegistry>
      requires std::invocable<GetViewWithRegistry&, EntityManager&> &&  HasClearComponentFeature<EntityFactory> && HasAddComponentEmptyFeature<EntityFactory>
    void BM_PublishEventViaComponentWithMixedEntitiesViews(benchmark::State& state, GetViewWithRegistry&& get_view_with_registry) {
      BM_PublishEventViaComponentWithMixedEntitiesViews(state, get_view_with_registry, [&](auto& registry, auto entity, auto&... /*comps*/) {
        this->m_entities_factory.addComponentEmpty(registry, entity);
      });
    }

  template <typename GetViewWithRegistry, typename GetViewWithEvent, typename PublishEventFunc, typename UpdateFunc>
  requires std::invocable<GetViewWithRegistry&, EntityManager&> && std::invocable<GetViewWithEvent&, EntityManager&> && HasClearComponentFeature<EntityFactory>
  void BM_PublishEventAndProgressEventViaComponentWithMixedEntitiesCustom(benchmark::State& state, GetViewWithRegistry&& get_view_with_registry, GetViewWithEvent&& get_view_with_event,
                                                                          PublishEventFunc&& event_func, UpdateFunc&& update_func) {
    const auto nentities = static_cast<size_t>(state.range(0));
    if constexpr (default_initializable_entity_manager) {
      EntityManager registry;
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->template createEntitiesWithMixedComponents<EntityFactory>(registry, nentities, entities);

      auto view = get_view_with_registry(registry);
      auto event_view = get_view_with_event(registry);
      for (auto _ : state) {
        update_func(registry, view);
        event_func(registry, event_view);
        this->m_entities_factory.clearComponentsEmpty(registry);
      }

      this->setCounters(state, entities, components_counter);
    } else {
      Application app(this->m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      const ComponentsCounter components_counter =
          this->createEntitiesWithMinimalComponents(registry, nentities, entities);

      auto view = get_view_with_registry(registry);
      auto event_view = get_view_with_event(registry);
      for (auto _ : state) {
        update_func(registry, view);
        event_func(registry, event_view);
        this->m_entities_factory.clearComponentsEmpty(registry);
      }

      this->setCounters(state, entities, components_counter);
      //state.counters["events_count"] = static_cast<double>(entities.size());
    }
  }
  template <typename GetViewWithRegistry, typename GetViewWithEvent, typename PublishEventFunc, typename UpdateFunc>
  requires std::invocable<GetViewWithRegistry&, EntityManager&> && std::invocable<GetViewWithEvent&, EntityManager&> && HasClearComponentFeature<EntityFactory>
  void BM_PublishEventAndProgressEventViaComponentWithMixedEntitiesViews(benchmark::State& state, GetViewWithRegistry&& get_view_with_registry, GetViewWithEvent&& get_view_with_event, PublishEventFunc&& event_func, UpdateFunc&& update_func) {
    BM_PublishEventAndProgressEventViaComponentWithMixedEntitiesCustom(state, get_view_with_registry, get_view_with_event, [&](auto& registry, auto& view) {
      generic_each(view, [&](auto&&... comps){ event_func(std::forward<decltype(registry)>(registry), std::forward<decltype(comps)>(comps)...); });
    }, [&](auto& /*registry*/, auto& view) {
       generic_each(view, update_func);
     });
  }
  template <typename GetViewWithRegistry, typename GetViewWithEvent>
    requires std::invocable<GetViewWithRegistry&, EntityManager&> && std::invocable<GetViewWithEvent&, EntityManager&> && HasClearComponentFeature<EntityFactory> && HasAddComponentEmptyFeature<EntityFactory>
  void BM_PublishEventAndProgressEventViaComponentWithMixedEntitiesViews(benchmark::State& state, GetViewWithRegistry&& get_view_with_registry, GetViewWithEvent&& get_view_with_event) {
    BM_PublishEventAndProgressEventViaComponentWithMixedEntitiesViews(state, get_view_with_registry, get_view_with_event, [&](auto& registry, auto entity, auto&... /*comps*/) {
      this->m_entities_factory.addComponentEmpty(registry, entity);
    }, [](auto& /*entity*/, auto&... comp) {
      dummy_each(comp...);
    });
  }


public:
  template <class Comp, class... Args>
  inline static void dummy_each(Comp& comp_or_entity, Args&... comps) {
    benchmark::DoNotOptimize(comp_or_entity);
    (benchmark::DoNotOptimize(comps), ...);
  }

  template <typename Iterable, typename Func>
    requires HasEach<Iterable, Func>
  inline static void generic_each(Iterable&& iterable, Func&& func) {
    std::forward<Iterable>(iterable).each(func);
  }
  template <typename Iterable, typename Func>
    requires HasForEach<Iterable, Func>
  inline static void generic(Iterable&& iterable, Func&& func) {
    std::forward<Iterable>(iterable).for_each(func);
  }
  template <typename Iterable, typename Func>
    requires HasVisit<Iterable, Func>
  inline static void generic(Iterable&& iterable, Func&& func) {
    std::forward<Iterable>(iterable).visit(func);
  }
};
} // namespace ecs::benchmarks::base

#define ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)                                \
  static void BM_IterateSingleComponent(benchmark::State& state) {                        \
    benchmark_suite.BM_IterateSingleComponent(state);                                     \
  }                                                                                       \
  BENCHMARK(BM_IterateSingleComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments); \
  static void BM_IterateTwoComponents(benchmark::State& state) {                          \
    benchmark_suite.BM_IterateTwoComponents(state);                                       \
  }                                                                                       \
  BENCHMARK(BM_IterateTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);   \
  static void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {       \
    benchmark_suite.BM_IterateThreeComponentsWithMixedEntities(state);                    \
  }                                                                                       \
  BENCHMARK(BM_IterateThreeComponentsWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

#endif // ECS_BENCHMARKS_MOREECSBENCHMARK_H_
