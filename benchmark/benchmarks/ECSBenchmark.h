#ifndef ECS_BENCHMARKS_ECSBENCHMARK_H_
#define ECS_BENCHMARKS_ECSBENCHMARK_H_

#include "BaseECSBenchmark.h"
#include "EntityBenchmark.h"
#include "basic.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <concepts>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace ecs::benchmarks::base {

template <StringLiteral Name, class Application, class EntityFactory, bool include_entity_benchmarks = false>
class ECSBenchmark : protected BaseECSBenchmark<EntityFactory> {
public:
  using EntityManager = typename EntityFactory::EntityManager;
  using Entity = typename EntityFactory::Entity;

  const float fakeTimeDelta{1.0F / 60.0F};

  ECSBenchmark() {
    benchmark::AddCustomContext("framework.name", m_name);
    benchmark::AddCustomContext("options.add_more_complex_system",
                                m_options.add_more_complex_system ? "true" : "false");
    if (m_options.version.has_value()) {
      benchmark::AddCustomContext("framework.version", m_options.version.value());
    }
  }
  explicit ECSBenchmark(ESCBenchmarkOptions options) : m_options(std::move(options)) {
    benchmark::AddCustomContext("framework.name", m_name);
    benchmark::AddCustomContext("options.add_more_complex_system",
                                m_options.add_more_complex_system ? "true" : "false");
    if (m_options.version.has_value()) {
      benchmark::AddCustomContext("framework.version", m_options.version.value());
    }
  }
  virtual ~ECSBenchmark() = default;
  ECSBenchmark(const ECSBenchmark&) = default;
  ECSBenchmark& operator=(const ECSBenchmark&) = default;
  ECSBenchmark(ECSBenchmark&&) noexcept = default;
  ECSBenchmark& operator=(ECSBenchmark&&) noexcept = default;

  [[nodiscard]] inline const char* name() const noexcept { return m_name; }
  [[nodiscard]] inline auto framework_version() const { return m_options.version; }


  void BM_SystemsUpdate_NoEntities(benchmark::State& state) {
    // const auto nentities = 0;
    std::vector<Entity> entities;
    Application app(m_options.add_more_complex_system);
    const ComponentsCounter components_counter = this->initApplicationWithoutEntities(app);
    for (auto _ : state) {
      app.update(fakeTimeDelta);
    }
    this->setCounters(state, entities, components_counter);
    afterBenchmark(app);
    uninitApplication(app);
  }

  void BM_SystemsUpdate(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    std::vector<Entity> entities;
    Application app(m_options.add_more_complex_system);
    const ComponentsCounter components_counter = this->initApplicationWithEntities(app, nentities, entities);
    for (auto _ : state) {
      app.update(fakeTimeDelta);
    }
    this->setCounters(state, entities, components_counter);
    afterBenchmark(app);
    uninitApplication(app);
  }

  void BM_SystemsUpdateMixedEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    std::vector<Entity> entities;
    Application app(m_options.add_more_complex_system);
    const ComponentsCounter components_counter =
        this->template initApplicationWithMixedComponents<EntityFactory>(app, nentities, entities);
    for (auto _ : state) {
      app.update(fakeTimeDelta);
    }
    this->setCounters(state, entities, components_counter);
    afterBenchmark(app);
    uninitApplication(app);
  }


  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks void BM_CreateNoEntities(benchmark::State& state) {
    const auto nentities = 0;
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();

      state.ResumeTiming();
      for (size_t i = 0; i < nentities; ++i) {
        this->m_entities_factory.createEmpty(registry);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks void BM_CreateEmptyEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();

      state.ResumeTiming();
      for (size_t i = 0; i < nentities; ++i) {
        this->m_entities_factory.createEmpty(registry);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasBulkFeature<tEntityFactory>
  void BM_CreateEmptyEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      entities.resize(nentities);

      state.ResumeTiming();
      this->m_entities_factory.createEmptyBulk(registry, entities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks void BM_CreateEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();

      state.ResumeTiming();
      for (size_t i = 0; i < nentities; ++i) {
        this->m_entities_factory.createMinimal(registry);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasBulkFeatureWithOutput<tEntityFactory>
  void BM_CreateEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      entities.resize(nentities);

      state.ResumeTiming();
      this->m_entities_factory.createMinimalBulk(registry, entities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }


  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasDestroyFeature<tEntityFactory>
  void BM_DestroyEntities(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      entities.resize(nentities);
      if constexpr (HasBulkFeature<EntityFactory>) {
        this->m_entities_factory.createMinimalBulk(registry, entities);
      } else {
        for (auto& entity : entities) {
          entity = this->m_entities_factory.createMinimal(registry);
        }
      }

      state.ResumeTiming();
      for (auto& entity : entities) {
        this->m_entities_factory.destroy(registry, entity);
      }
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasBulkDestroyFeature<tEntityFactory>
  void BM_DestroyEntitiesInBulk(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
      state.PauseTiming();
      Application app(m_options.add_more_complex_system);
      EntityManager& registry = app.getEntities();
      std::vector<Entity> entities;
      entities.resize(nentities);
      this->m_entities_factory.createMinimalBulk(registry, entities);

      state.ResumeTiming();
      this->m_entities_factory.destroyBulk(registry, entities);
    }
    state.counters["entities"] = static_cast<double>(nentities);
  }


  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackNoComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(entity);
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackOneComponent_NoEntities(benchmark::State& state) {
    const auto nentities = 0;
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
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
  requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackOneComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
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
  requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackOneConstComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOneConst(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackTwoComponents(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const ComponentsCounter components_counter =
        this->createEntitiesWithMinimalComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentTwoConst(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
  void BM_UnpackThreeComponents(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
    std::vector<Entity> entities;
    const ComponentsCounter components_counter = this->createEntitiesWithHalfComponents(registry, nentities, entities);

    for (auto _ : state) {
      for (auto& entity : entities) {
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
        benchmark::DoNotOptimize(this->m_entities_factory.getComponentTwoConst(registry, entity));
        benchmark::DoNotOptimize(this->m_entities_factory.getOptionalComponentThree(registry, entity));
      }
    }
    this->setCounters(state, entities, components_counter);
  }

  template <class tEntityFactory = EntityFactory>
  requires include_entity_benchmarks void BM_RemoveAddComponent(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    Application app(m_options.add_more_complex_system);
    EntityManager& registry = app.getEntities();
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
  ComponentsCounter initApplicationWithoutEntities(Application& app) {
    app.init();
    return this->createNoEntities(app.getEntities());
  }
  ComponentsCounter initApplicationWithoutEntities(Application& app, std::vector<Entity>& out) {
    app.init();
    return this->createNoEntities(app.getEntities(), out);
  }

  ComponentsCounter initApplicationWithEntities(Application& app, size_t nentities) {
    app.init();
    return this->createEntities(app.getEntities(), nentities);
  }
  ComponentsCounter initApplicationWithEntities(Application& app, size_t nentities, std::vector<Entity>& out) {
    app.init();
    return this->createEntities(app.getEntities(), nentities, out);
  }

  ComponentsCounter initApplicationWithHalfComponents(Application& app, size_t nentities) {
    app.init();
    return this->createEntitiesWithHalfComponents(app.getEntities(), nentities);
  }
  ComponentsCounter initApplicationWithHalfComponents(Application& app, size_t nentities, std::vector<Entity>& out) {
    app.init();
    return this->createEntitiesWithHalfComponents(app.getEntities(), nentities, out);
  }

  template <class tEntityFactory = EntityFactory, class tEntityManager = typename tEntityFactory::EntityManager>
  requires HasRemoveComponentsFeatures<tEntityFactory>
      ComponentsCounter initApplicationWithMixedComponents(Application& app, size_t nentities) {
    app.init();
    return this->template createEntitiesWithMixedComponents<tEntityManager>(app.getEntities(), nentities);
  }
  template <class tEntityFactory = EntityFactory, class tEntityManager = typename tEntityFactory::EntityManager>
  requires HasRemoveComponentsFeatures<tEntityFactory> ComponentsCounter
  initApplicationWithMixedComponents(Application& app, size_t nentities, std::vector<Entity>& out) {
    app.init();
    return this->template createEntitiesWithMixedComponents<tEntityFactory, tEntityManager>(app.getEntities(),
                                                                                            nentities, out);
  }

  template <class tEntityFactory = EntityFactory, class tEntityManager = typename tEntityFactory::EntityManager>
  requires HasAddComponentsFeatures<tEntityFactory>
      ComponentsCounter initApplicationWithMixedComponentsFromEmpty(Application& app, size_t nentities) {
    app.init();
    return this->template createEntitiesWithMixedComponentsFromEmpty<tEntityFactory, tEntityManager>(app.getEntities(),
                                                                                                     nentities);
  }
  template <class tEntityFactory = EntityFactory, class tEntityManager = typename tEntityFactory::EntityManager>
  requires HasAddComponentsFeatures<tEntityFactory> ComponentsCounter
  initApplicationWithMixedComponentsFromEmpty(Application& app, size_t nentities, std::vector<Entity>& out) {
    app.init();
    return this->template createEntitiesWithMixedComponentsFromEmpty<tEntityFactory, tEntityManager>(app.getEntities(),
                                                                                                     nentities, out);
  }

  ComponentsCounter initApplicationWithMinimalComponents(Application& app, size_t nentities, std::vector<Entity>& out) {
    app.init();
    return this->createEntitiesWithMinimalComponents(app.getEntities(), nentities, out);
  }

  ComponentsCounter initApplicationWithSingleComponent(Application& app, size_t nentities, std::vector<Entity>& out) {
    app.init();
    return this->createEntitiesWithSingleComponent(app.getEntities(), nentities, out);
  }

  void uninitApplication(Application& app) { app.uninit(); }

  virtual void afterBenchmark(Application& /*app*/) {}

  inline static constexpr auto m_name{Name.value};
  const ESCBenchmarkOptions m_options;
  EntityFactory m_entities_factory;
};
} // namespace ecs::benchmarks::base

#define ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)                           \
  static void BM_SystemsUpdate_NoEntities(benchmark::State& state) {             \
    benchmark_suite.BM_SystemsUpdate_NoEntities(state);                          \
  }                                                                              \
  BENCHMARK(BM_SystemsUpdate_NoEntities);                                        \
  static void BM_SystemsUpdate(benchmark::State& state) {                        \
    benchmark_suite.BM_SystemsUpdate(state);                                     \
  }                                                                              \
  BENCHMARK(BM_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments); \
  static void BM_SystemsUpdateMixedEntities(benchmark::State& state) {           \
    benchmark_suite.BM_SystemsUpdateMixedEntities(state);                        \
  }                                                                              \
  BENCHMARK(BM_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


#define ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)                          \
  static void BM_ComplexSystemsUpdate_NoEntities(benchmark::State& state) {             \
    benchmark_suite.BM_SystemsUpdate_NoEntities(state);                                 \
  }                                                                                     \
  BENCHMARK(BM_ComplexSystemsUpdate_NoEntities);                                        \
  static void BM_ComplexSystemsUpdate(benchmark::State& state) {                        \
    benchmark_suite.BM_SystemsUpdate(state);                                            \
  }                                                                                     \
  BENCHMARK(BM_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments); \
  static void BM_ComplexSystemsUpdateMixedEntities(benchmark::State& state) {           \
    benchmark_suite.BM_SystemsUpdateMixedEntities(state);                               \
  }                                                                                     \
  BENCHMARK(BM_ComplexSystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


#endif // ECS_BENCHMARKS_ECSBENCHMARK_H_
