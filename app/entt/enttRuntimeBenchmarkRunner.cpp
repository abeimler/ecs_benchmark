#include <entt/EnttRuntimeBenchmark.h>

#include <array>
#include <benchpress/benchpress.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace enttruntime_benchmark {

constexpr size_t _10M = 10'000'000L;

/// @NOTE: void "too many arguments provided to function-like macro
/// invocation"-error in BENCHMARK-Macro
typedef std::array<entt::component, 1> array_types_component_1;
typedef std::array<entt::component, 2> array_types_component_2;
array_types_component_1 array_types_1 = 
      {EnttRuntimeBenchmark::EntityManager::type<EnttRuntimeBenchmark::PositionComponent>()};

array_types_component_2 array_types_2 = {EnttRuntimeBenchmark::EntityManager::type<EnttRuntimeBenchmark::PositionComponent>(),
       EnttRuntimeBenchmark::EntityManager::type<EnttRuntimeBenchmark::DirectionComponent>()};

BENCHMARK(
    "[3] entt-runtime     Iterating over 10M entities, unpacking one component",
    [](benchpress::context *ctx) {
      EnttRuntimeBenchmark::EntityManager registry;

      for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttRuntimeBenchmark::PositionComponent>(entity);
      }
      array_types_component_1& types_1 = array_types_1;

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for (auto entity :
             registry.runtime_view(std::begin(types_1), std::end(types_1))) {
          DISABLE_REDUNDANT_CODE_OPT();
          auto &position =
              registry.get<EnttRuntimeBenchmark::PositionComponent>(entity);

          benchpress::escape(&entity);
          benchpress::escape(&position);
        }
      }
    })

BENCHMARK(
    "[4] entt-runtime     Iterating over 10M entities, unpacking two "
    "components",
    [](benchpress::context *ctx) {
      EnttRuntimeBenchmark::EntityManager registry;

      for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttRuntimeBenchmark::PositionComponent>(entity);
        registry.assign<EnttRuntimeBenchmark::DirectionComponent>(entity);
      }
      array_types_component_2& types_2 = array_types_2;

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for (auto entity :
             registry.runtime_view(std::begin(types_2), std::end(types_2))) {
          DISABLE_REDUNDANT_CODE_OPT();
          auto &position =
              registry.get<EnttRuntimeBenchmark::PositionComponent>(entity);
          auto &velocity =
              registry.get<EnttRuntimeBenchmark::DirectionComponent>(entity);

          benchpress::escape(&entity);
          benchpress::escape(&position);
          benchpress::escape(&velocity);
        }
      }
    })

inline void init_entities(EnttRuntimeBenchmark::EntityManager &registry,
                          size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = registry.create();

    registry.assign<EnttRuntimeBenchmark::PositionComponent>(entity);
    registry.assign<EnttRuntimeBenchmark::DirectionComponent>(entity);

    if (i % 2 != 0) {
      registry.assign<EnttRuntimeBenchmark::ComflabulationComponent>(entity);
    }
  }
}

inline void runEntitiesSystemsEnttRuntimeBenchmark(benchpress::context *ctx,
                                                   size_t nentities) {
  EnttRuntimeBenchmark::Application app;
  auto &registry = app.getEntityManager();

  init_entities(registry, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(EnttRuntimeBenchmark::fakeDeltaTime);
  }
}

class BenchmarksEnttRuntime {
public:
  static const std::vector<int> ENTITIES;

  static inline void makeBenchmarks(const std::string &name) {
    makeBenchmarks(name, ENTITIES);
  }

  static void makeBenchmarks(const std::string &name,
                             const std::vector<int> &entities) {
    for (int nentities : entities) {
      std::string tag = fmt::format("[{}]", nentities);
      std::string benchmark_name =
          fmt::format("{:>12} {:<10} {:>12} entities component systems update",
                      tag, name, nentities);

      BENCHMARK(benchmark_name, [nentities](benchpress::context *ctx) {
        runEntitiesSystemsEnttRuntimeBenchmark(ctx, nentities);
      })
    }
  }

  BenchmarksEnttRuntime(const std::string &name) { makeBenchmarks(name); }
};
const std::vector<int> BenchmarksEnttRuntime::ENTITIES = {
    10,        25,        50,        100,        200,       400,     800,
    1600,      3200,      5000,      10'000,     30'000,    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000};

BenchmarksEnttRuntime enttbenchmarks("entt-runtime");

} // namespace enttruntime_benchmark
