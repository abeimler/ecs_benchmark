#ifndef ECS_BENCHMARKS_ENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITYBENCHMARK_H_

#include "BaseECSBenchmark.h"
#include "basic.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <concepts>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace ecs::benchmarks::base {

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasBulkFeature = requires(EntityFactory factory, EntityManager& entity_manager, size_t nentities) {
  factory.createEmptyBulk(entity_manager, nentities);
  factory.createBulk(entity_manager, nentities);
  factory.createMinimalBulk(entity_manager, nentities);
};

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasBulkFeatureWithOutput =
    requires(EntityFactory factory, EntityManager& entity_manager, std::vector<Entity>& entities) {
      factory.createEmptyBulk(entity_manager, entities);
      factory.createBulk(entity_manager, entities);
      factory.createMinimalBulk(entity_manager, entities);
    };

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasDestroyFeature = requires(EntityFactory factory, EntityManager& entity_manager, Entity entity) {
  factory.destroy(entity_manager, entity);
};

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasBulkDestroyFeature =
    requires(EntityFactory factory, EntityManager& entity_manager, std::vector<Entity>& entities) {
      factory.destroyBulk(entity_manager, entities);
    };

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasGetComponentsFeature = requires(EntityFactory factory, EntityManager& entity_manager, Entity entity) {
  // factory.getComponentOneConst(entity_manager, entity);
  // factory.getComponentTwoConst(entity_manager, entity);
  factory.getComponentOne(entity_manager, entity);
  factory.getComponentTwo(entity_manager, entity);
  factory.getOptionalComponentThree(entity_manager, entity);
};

template <StringLiteral Name, class EntityFactory, class tEntityManager = typename EntityFactory::EntityManager>
  requires std::default_initializable<tEntityManager>
class EntityBenchmark : public BaseECSBenchmark<EntityFactory> {
public:
  using EntityManager = tEntityManager;
  using Entity = typename EntityFactory::Entity;

  EntityBenchmark() {
    benchmark::AddCustomContext("framework.name", m_name);
    benchmark::AddCustomContext("options.add_more_complex_system",
                                m_options.add_more_complex_system ? "true" : "false");
    if (m_options.version.has_value()) {
      benchmark::AddCustomContext("framework.version", m_options.version.value());
    }
  }

  explicit EntityBenchmark(ESCBenchmarkOptions options) : m_options(std::move(options)) {
    benchmark::AddCustomContext("framework.name", m_name);
    benchmark::AddCustomContext("options.add_more_complex_system",
                                m_options.add_more_complex_system ? "true" : "false");
    if (m_options.version.has_value()) {
      benchmark::AddCustomContext("framework.version", m_options.version.value());
    }
  }

  virtual ~EntityBenchmark() = default;
  EntityBenchmark(const EntityBenchmark&) = default;
  EntityBenchmark& operator=(const EntityBenchmark&) = default;
  EntityBenchmark(EntityBenchmark&&) noexcept = default;
  EntityBenchmark& operator=(EntityBenchmark&&) noexcept = default;

  [[nodiscard]] inline const char* name() const noexcept { return m_name; }

  [[nodiscard]] inline auto framework_version() const { return m_options.version; }


  void BM_CreateNoEntities(benchmark::State& state) {
    const size_t nentities = 0;
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;

      state.ResumeTiming();
      for (size_t i = 0; i < nentities; ++i) {
        this->m_entities_factory.createEmpty(registry);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  void BM_CreateEmptyEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;

      state.ResumeTiming();
      for (size_t i = 0; i < nentities; ++i) {
        this->m_entities_factory.createEmpty(registry);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
    requires HasBulkFeatureWithOutput<tEntityFactory>
  void BM_CreateEmptyEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;
      std::vector<Entity> entities;
      entities.resize(nentities);

      state.ResumeTiming();
      this->m_entities_factory.createEmptyBulk(registry, entities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }
  template <class tEntityFactory = EntityFactory>
    requires HasBulkFeature<tEntityFactory>
  void BM_CreateEmptyEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;

      state.ResumeTiming();
      this->m_entities_factory.createEmptyBulk(registry, nentities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  void BM_CreateEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;

      state.ResumeTiming();
      for (size_t i = 0; i < nentities; ++i) {
        this->m_entities_factory.createMinimal(registry);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
    requires HasBulkFeatureWithOutput<tEntityFactory>
  void BM_CreateEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;
      std::vector<Entity> entities;
      entities.resize(nentities);

      state.ResumeTiming();
      this->m_entities_factory.createMinimalBulk(registry, entities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }
  template <class tEntityFactory = EntityFactory>
    requires HasBulkFeature<tEntityFactory>
  void BM_CreateEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;

      state.ResumeTiming();
      this->m_entities_factory.createMinimalBulk(registry, nentities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }


  template <class tEntityFactory = EntityFactory>
    requires HasDestroyFeature<tEntityFactory>
  void BM_DestroyEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;
      std::vector<Entity> entities;
      entities.reserve(nentities);
      for (size_t i = 0; i < nentities; i++) {
        entities.push_back(this->m_entities_factory.createMinimal(registry));
      }

      state.ResumeTiming();
      for (auto& entity : entities) {
        this->m_entities_factory.destroy(registry, entity);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }
  template <class tEntityFactory = EntityFactory>
    requires HasBulkDestroyFeature<tEntityFactory>
  void BM_DestroyEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      EntityManager registry;
      std::vector<Entity> entities;
      entities.resize(nentities);
      this->m_entities_factory.createMinimalBulk(registry, entities);

      state.ResumeTiming();
      this->m_entities_factory.destroyBulk(registry, entities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
    requires HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackNoComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    EntityManager registry;
    std::vector<Entity> entities;
    for (size_t i = 0; i < nentities; i++) {
      entities.push_back(this->m_entities_factory.createEmpty(registry));
    }

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getOptionalComponentThree(registry, entity));
      }
    }
    this->setCounters(state, entities,
                      {
                          .component_one_count{0},
                          .component_two_count{0},
                          .component_three_count{0},
                      });
  }

  template <class tEntityFactory = EntityFactory>
    requires HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackOneComponent_NoEntities(benchmark::State& state) {
    const auto nentities = 0;
    EntityManager registry;
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
    requires HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackOneComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    EntityManager registry;
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);


    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
    requires HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackTwoComponents(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    EntityManager registry;
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentTwo(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
    requires HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackThreeComponents(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    EntityManager registry;
    std::vector<Entity> entities;
    const ComponentsCounter components_counter = this->createEntitiesWithHalfComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentTwo(registry, entity));
        benchmark::DoNotOptimize(this->m_entities_factory.getOptionalComponentThree(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  void BM_RemoveAddComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    EntityManager registry;
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        this->m_entities_factory.removeComponentOne(registry, entity);
        this->m_entities_factory.addComponentOne(registry, entity);
      }
    }
    this->setCounters(state, entities, components_counter);
  }

protected:
  inline static constexpr auto m_name{Name.value};
  const ESCBenchmarkOptions m_options;
};
} // namespace ecs::benchmarks::base

#define MINIMAL_ECS_ENTITY_BENCHMARKS(benchmark_suite)                                 \
  static void BM_CreateNoEntities(benchmark::State& state) {                           \
    benchmark_suite.BM_CreateNoEntities(state);                                        \
  }                                                                                    \
  BENCHMARK(BM_CreateNoEntities);                                                      \
  static void BM_CreateEmptyEntities(benchmark::State& state) {                        \
    benchmark_suite.BM_CreateEmptyEntities(state);                                     \
  }                                                                                    \
  BENCHMARK(BM_CreateEmptyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments); \
  static void BM_UnpackNoComponent(benchmark::State& state) {                          \
    benchmark_suite.BM_UnpackNoComponent(state);                                       \
  }                                                                                    \
  BENCHMARK(BM_UnpackNoComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);   \
  static void BM_CreateEntities(benchmark::State& state) {                             \
    benchmark_suite.BM_CreateEntities(state);                                          \
  }                                                                                    \
  BENCHMARK(BM_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);      \
  static void BM_UnpackOneComponent(benchmark::State& state) {                         \
    benchmark_suite.BM_UnpackOneComponent(state);                                      \
  }                                                                                    \
  BENCHMARK(BM_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);  \
  static void BM_UnpackOneComponent_NoEntities(benchmark::State& state) {              \
    benchmark_suite.BM_UnpackOneComponent_NoEntities(state);                           \
  }                                                                                    \
  BENCHMARK(BM_UnpackOneComponent_NoEntities);                                         \
  static void BM_UnpackTwoComponents(benchmark::State& state) {                        \
    benchmark_suite.BM_UnpackTwoComponents(state);                                     \
  }                                                                                    \
  BENCHMARK(BM_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments); \
  static void BM_UnpackThreeComponents(benchmark::State& state) {                      \
    benchmark_suite.BM_UnpackThreeComponents(state);                                   \
  }                                                                                    \
  BENCHMARK(BM_UnpackThreeComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);

#define ECS_REMOVE_ENTITY_BENCHMARKS(benchmark_suite)                                 \
  static void BM_RemoveAddComponent(benchmark::State& state) {                        \
    benchmark_suite.BM_RemoveAddComponent(state);                                     \
  }                                                                                   \
  BENCHMARK(BM_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments); \
  static void BM_DestroyEntities(benchmark::State& state) {                           \
    benchmark_suite.BM_DestroyEntities(state);                                        \
  }                                                                                   \
  BENCHMARK(BM_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

#define ECS_ENTITY_BENCHMARKS(benchmark_suite)   \
  MINIMAL_ECS_ENTITY_BENCHMARKS(benchmark_suite) \
  ECS_REMOVE_ENTITY_BENCHMARKS(benchmark_suite)


#endif // ECS_BENCHMARKS_ENTITYBENCHMARK_H_
