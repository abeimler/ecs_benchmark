#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <benchpress/benchpress.hpp>

#include <enttlegacy/EnttLegacyBenchmark.h>

namespace enttlegacy_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] enttlegacy     Creating 10M entities",
          [](benchpress::context *ctx) {
            EnttLegacyBenchmark::EntityManager registry;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              std::vector<EnttLegacyBenchmark::Entity> created_entities(_10M);

              ctx->start_timer();
              for (size_t c = 0; c < _10M; c++) {
                auto entity = registry.create();
                created_entities.emplace_back(entity);
              }
              ctx->stop_timer();

              // cleanup memory to avoid full memory
              for (auto entity : created_entities) {
                registry.destroy(entity);
              }
            }
          })

BENCHMARK("[2] enttlegacy     Destroying 10M entities",
          [](benchpress::context *ctx) {
            EnttLegacyBenchmark::EntityManager registry;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              std::vector<EnttLegacyBenchmark::Entity> created_entities(_10M);

              for (size_t c = 0; c < _10M; c++) {
                auto entity = registry.create();
                created_entities.emplace_back(entity);
              }

              ctx->start_timer();
              for (auto entity : created_entities) {
                registry.destroy(entity);
              }
              ctx->stop_timer();
            }
          })

BENCHMARK(
    "[3] enttlegacy     Iterating over 10M entities, unpacking one component",
    [](benchpress::context *ctx) {
      EnttLegacyBenchmark::EntityManager registry;

      for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttLegacyBenchmark::PositionComponent>(entity);
      }

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for (auto entity :
             registry.view<EnttLegacyBenchmark::PositionComponent>()) {
          DISABLE_REDUNDANT_CODE_OPT();
          auto &position =
              registry.get<EnttLegacyBenchmark::PositionComponent>(entity);

          benchpress::escape(&position);
        }
      }
    })

BENCHMARK(
    "[4] enttlegacy     Iterating over 10M entities, unpacking two components",
    [](benchpress::context *ctx) {
      EnttLegacyBenchmark::EntityManager registry;

      for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttLegacyBenchmark::PositionComponent>(entity);
        registry.assign<EnttLegacyBenchmark::DirectionComponent>(entity);
      }

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for (auto entity :
             registry.view<EnttLegacyBenchmark::PositionComponent,
                           EnttLegacyBenchmark::DirectionComponent>()) {
          DISABLE_REDUNDANT_CODE_OPT();
          auto &position =
              registry.get<EnttLegacyBenchmark::PositionComponent>(entity);
          auto &velocity =
              registry.get<EnttLegacyBenchmark::DirectionComponent>(entity);

          benchpress::escape(&position);
          benchpress::escape(&velocity);
        }
      }
    })

BENCHMARK("enttlegacy     create destroy entity with components",
          [](benchpress::context *ctx) {
            EnttLegacyBenchmark::EntityManager registry;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = registry.create();

              registry.assign<EnttLegacyBenchmark::PositionComponent>(entity);
              registry.assign<EnttLegacyBenchmark::DirectionComponent>(entity);
              registry.assign<EnttLegacyBenchmark::ComflabulationComponent>(
                  entity);

              registry.destroy(entity);
            }
          })

inline void init_entities(EnttLegacyBenchmark::EntityManager &registry,
                          size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = registry.create();

    registry.assign<EnttLegacyBenchmark::PositionComponent>(entity);
    registry.assign<EnttLegacyBenchmark::DirectionComponent>(entity);

    if (i % 2 != 0) {
      registry.assign<EnttLegacyBenchmark::ComflabulationComponent>(entity);
    }
  }
}

inline void runEntitiesSystemsEnttLegacyBenchmark(benchpress::context *ctx,
                                                  size_t nentities) {
  EnttLegacyBenchmark::Application app;
  auto &registry = app.getEntityManager();

  init_entities(registry, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(EnttLegacyBenchmark::fakeDeltaTime);
  }
}

class BenchmarksEnttLegacy {
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
        runEntitiesSystemsEnttLegacyBenchmark(ctx, nentities);
      })
    }
  }

  BenchmarksEnttLegacy(const std::string &name) { makeBenchmarks(name); }
};
const std::vector<int> BenchmarksEnttLegacy::ENTITIES = {
    10,        25,        50,        100,        200,       400,     800,
    1600,      3200,      5000,      10'000,     30'000,    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000};

BenchmarksEnttLegacy enttlegacybenchmarks("enttlegacy");

} // namespace enttlegacy_benchmark
