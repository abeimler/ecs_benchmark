#ifndef ECS_BENCHMARKS_OOPBENCHMARK_H_
#define ECS_BENCHMARKS_OOPBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "oop/OOPApplication.h"
#include "oop/entities/EntityFactory.h"


namespace ecs::benchmarks::oop {

class OOPBenchmarkSuite final : public ecs::benchmarks::base::BaseECSBenchmark<entities::EntityFactory> {
public:
  using EntityManager = typename entities::OOPEntityManager;
  using Entity = typename entities::EntityFactory::Entity;

  const float fakeTimeDelta{1.0F / 60.0F};

  OOPBenchmarkSuite() {
    benchmark::AddCustomContext("framework.name", m_name);
    benchmark::AddCustomContext(
        "options.add_more_complex_system",
        m_options.add_more_complex_system == base::add_more_complex_system_t::UseMoreComplexSystems ? "true" : "false");
    if (m_options.version.has_value()) {
      benchmark::AddCustomContext("framework.version", m_options.version.value());
    }
  }
  explicit OOPBenchmarkSuite(base::ESCBenchmarkOptions options) : m_options(std::move(options)) {
    benchmark::AddCustomContext("framework.name", m_name);
    benchmark::AddCustomContext(
        "options.add_more_complex_system",
        m_options.add_more_complex_system == base::add_more_complex_system_t::UseMoreComplexSystems ? "true" : "false");
    if (m_options.version.has_value()) {
      benchmark::AddCustomContext("framework.version", m_options.version.value());
    }
  }

  void createEntitiesWithMixedEntities(OOPApplication& app, size_t nentities, std::vector<Entity>& out) {
    out.clear();
    out.reserve(nentities);
    // inspired from EnTT benchmark "pathological",
    // https://github.com/skypjack/entt/blob/de0e5862dd02fa669325a0a06b7936af4d2a841d/test/benchmark/benchmark.cpp#L44
    for (size_t i = 0, j = 0; i < nentities; i++) {
      bool added = false;
      if (nentities < 100 || (i >= 2 * nentities / 4 && i <= 3 * nentities / 4)) {
        if (nentities < 100 || (j % 10) == 0U) {
          if ((i % 7) == 0U) {
            out.push_back(m_entities_factory.createMinimal(app.getEntities()));
            added = true;
          }
          if ((i % 11) == 0U) {
            out.push_back(m_entities_factory.createMinimal(app.getEntities()));
            added = true;
          }
          if ((i % 13) == 0U) {
            out.push_back(m_entities_factory.createMinimal(app.getEntities()));
            added = true;
          }
          // if ((i % 17) == 0U) {
          //   out.push_back(m_entities_factory.create(app.getEntities()));
          //   m_entities_factory.destroy(registry, out.back());
          //   added = true;
          // }
        }
        j++;
      }
      if (!added) {
        out.push_back(m_entities_factory.create(app.getEntities()));
      }
    }
  }

  void BM_SystemsUpdate(benchmark::State& state) {
    const auto nentities = static_cast<size_t>(state.range(0));
    std::vector<Entity> entities;
    OOPApplication app(m_options.add_more_complex_system);
    createEntitiesWithMixedEntities(app, nentities, entities);
    for (auto _ : state) {
      app.update(fakeTimeDelta);
    }
    state.PauseTiming();
    state.counters["entities"] = static_cast<double>(entities.size());
    app.uninit();
  }

private:
  inline static constexpr auto m_name = "oop";
  const base::ESCBenchmarkOptions m_options;
};

} // namespace ecs::benchmarks::oop

#endif // ECS_BENCHMARKS_OOPBENCHMARK_H_
