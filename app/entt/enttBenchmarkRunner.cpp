#include <entt/EnttBenchmark.h>

#include <benchpress/benchpress.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace entt_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] entt     Creating 10M entities", [](benchpress::context *ctx) {
  EntityManager registry;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity> created_entities(_10M);

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

BENCHMARK("[2] entt     Destroying 10M entities", [](benchpress::context *ctx) {
  EntityManager registry;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity> created_entities(_10M);

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

BENCHMARK("[3] entt     Iterating over 10M entities, unpacking one component",
          [](benchpress::context *ctx) {
            EntityManager registry;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = registry.create();
              registry.assign<PositionComponent>(entity);
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              for (auto entity :
                   registry.view<PositionComponent>()) {
                DISABLE_REDUNDANT_CODE_OPT();
                auto &position =
                    registry.get<PositionComponent>(entity);

                benchpress::escape(&entity);
                benchpress::escape(&position);
              }
            }
          })

BENCHMARK("[4] entt     Iterating over 10M entities, unpacking two components",
          [](benchpress::context *ctx) {
            EntityManager registry;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = registry.create();
              registry.assign<PositionComponent>(entity);
              registry.assign<DirectionComponent>(entity);
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              for (auto entity :
                   registry.view<PositionComponent,
                                 DirectionComponent>()) {
                DISABLE_REDUNDANT_CODE_OPT();
                auto &position =
                    registry.get<PositionComponent>(entity);
                auto &velocity =
                    registry.get<DirectionComponent>(entity);

                benchpress::escape(&entity);
                benchpress::escape(&position);
                benchpress::escape(&velocity);
              }
            }
          })

BENCHMARK("[5] entt     Creating 10M entities at once",
          [](benchpress::context *ctx) {
            EntityManager registry;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              std::vector<Entity> created_entities(_10M);

              ctx->start_timer();
              registry.create(std::begin(created_entities),
                              std::end(created_entities));
              ctx->stop_timer();

              // cleanup memory to avoid full memory
              for (auto entity : created_entities) {
                registry.destroy(entity);
              }
            }
          })

BENCHMARK("entt     create destroy entity with components",
          [](benchpress::context *ctx) {
            EntityManager registry;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = registry.create();

              registry.assign<PositionComponent>(entity);
              registry.assign<DirectionComponent>(entity);
              registry.assign<ComflabulationComponent>(entity);

              registry.destroy(entity);
            }
          })

inline void init_entities(EntityManager &registry,
                          size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = registry.create();

    registry.assign<PositionComponent>(entity);
    registry.assign<DirectionComponent>(entity);

    if (i % 2 != 0) {
      registry.assign<ComflabulationComponent>(entity);
    }
  }
}

inline void runEntitiesSystemsEnttBenchmark(benchpress::context *ctx,
                                            size_t nentities) {
  Application app;
  auto &registry = app.getEntityManager();

  init_entities(registry, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(EnttBenchmark::fakeDeltaTime);
  }
}

class BenchmarksEntt {
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
        runEntitiesSystemsEnttBenchmark(ctx, nentities);
      })
    }
  }

  BenchmarksEntt(const std::string &name) { makeBenchmarks(name); }
};
const std::vector<int> BenchmarksEntt::ENTITIES = {
    10,        25,        50,        100,        200,       400,     800,
    1600,      3200,      5000,      10'000,     30'000,    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000};

BenchmarksEntt enttbenchmarks("entt");

} // namespace entt_benchmark
