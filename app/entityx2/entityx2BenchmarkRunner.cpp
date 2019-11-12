#include <entityx2/EntityX2Benchmark.h>

#include <benchpress/benchpress.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace entityx2_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] entityx2 Creating 10M entities", [](benchpress::context *ctx) {
  EntityManager entities;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity> created_entities(_10M);

    ctx->start_timer();
    for (size_t c = 0; c < _10M; c++) {
      auto entity = entities.create();
      created_entities.emplace_back(entity);
    }
    ctx->stop_timer();

    // cleanup memory to avoid full memory
    for (auto entity : created_entities) {
      entities.destroy(entity.id());
    }
  }
})

BENCHMARK("[2] entityx2 Destroying 10M entities", [](benchpress::context *ctx) {
  EntityManager entities;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity> created_entities(_10M);

    for (size_t c = 0; c < _10M; c++) {
      auto entity = entities.create();
      created_entities.emplace_back(entity);
    }

    ctx->start_timer();
    for (auto entity : created_entities) {
      entities.destroy(entity.id());
    }
    ctx->stop_timer();
  }
})

BENCHMARK("[3] entityx2 Iterating over 10M entities, unpacking one component",
          [](benchpress::context *ctx) {
            EntityManager entities;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = entities.create();
              entity.assign<PositionComponent>();
            }

            auto update_func =
                [&](Entity entity,
                    PositionComponent &position) {
                  DISABLE_REDUNDANT_CODE_OPT();
                  benchpress::escape(&entity);
                  benchpress::escape(&position);
                };

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              entities.for_each<PositionComponent>(update_func);
            }
          })

/// @NOTE: avoid "too many arguments provided to function-like macro
/// invocation"-error in BENCHMARK-Macro
inline auto update_func_components_2 =
    [](Entity entity,
       PositionComponent &position,
       DirectionComponent &velocity) {
      DISABLE_REDUNDANT_CODE_OPT();
      benchpress::escape(&entity);
      benchpress::escape(&position);
      benchpress::escape(&velocity);
    };
inline auto for_each_update_func_components_2 =
    [](EntityManager &entities) {
      entities.for_each<PositionComponent,
                        DirectionComponent>(
          update_func_components_2);
    };
BENCHMARK("[4] entityx2 Iterating over 10M entities, unpacking two component",
          [](benchpress::context *ctx) {
            EntityManager entities;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = entities.create();
              entity.assign<PositionComponent>();
              entity.assign<DirectionComponent>();
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              for_each_update_func_components_2(entities);
            }
          })

BENCHMARK("[5] entityx2 Creating 10M entities at once",
          [](benchpress::context *ctx) {
            EntityManager entities;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              std::vector<Entity> created_entities;

              ctx->start_timer();
              created_entities = entities.create_many(_10M);
              ctx->stop_timer();

              // cleanup memory to avoid full memory
              for (auto entity : created_entities) {
                entities.destroy(entity.id());
              }
            }
          })

BENCHMARK("[6] entityx2 Destroying 10M entities at once",
          [](benchpress::context *ctx) {
            EntityManager entities;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              ctx->stop_timer();
              std::vector<Entity> created_entities;
              created_entities = entities.create_many(_10M);

              ctx->start_timer();
              entities.reset();
              ctx->stop_timer();
            }
          })

BENCHMARK("entityx2 create destroy entity with components",
          [](benchpress::context *ctx) {
            EntityManager entities;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = entities.create();

              entity.assign<PositionComponent>();
              entity.assign<DirectionComponent>();
              entity.assign<ComflabulationComponent>();

              entities.destroy(entity.id());
            }
          })

inline void init_entities(EntityManager &entities,
                          size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = entities.create();

    entity.assign<PositionComponent>();
    entity.assign<DirectionComponent>();

    if (i % 2 != 0) {
      entity.assign<ComflabulationComponent>();
    }
  }
}

inline void runEntitiesSystemsEntityX2Benchmark(benchpress::context *ctx,
                                                size_t nentities,
                                                bool addmorecomplexsystem) {
  Application app (addmorecomplexsystem);
  auto &entities = app.getEntityManager();

  init_entities(entities, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(EntityX2Benchmark::fakeDeltaTime);
  }
}

class BenchmarksEntityX2 {
public:
  static const std::vector<int> ENTITIES;

  static inline void makeBenchmarks(const std::string &name, bool addmorecomplexsystem) {
    makeBenchmarks(name, ENTITIES, addmorecomplexsystem);
  }

  static void makeBenchmarks(const std::string &name,
                             const std::vector<int> &entities,
                             bool addmorecomplexsystem) {
    for (int nentities : entities) {
      std::string tag = fmt::format("[{}]", nentities);
      std::string benchmark_name =
          fmt::format("{:>12} {:<10} {:>12} entities component systems update",
                      tag, name, nentities);

      BENCHMARK(benchmark_name, [&](benchpress::context *ctx) {
        runEntitiesSystemsEntityX2Benchmark(ctx, nentities, addmorecomplexsystem);
      })
    }
  }

  BenchmarksEntityX2(const std::string &name, bool addmorecomplexsystem) { 
    makeBenchmarks(name, addmorecomplexsystem); 
  }
};
const std::vector<int> BenchmarksEntityX2::ENTITIES = {
    10,        25,        50,        100,        200,        400,     800,
    1600,      3200,      5000,      10'000,     30'000,     100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000,
};

BenchmarksEntityX2 entityx2benchmarks("entityx2", false);
BenchmarksEntityX2 entityx2benchmarks_morecomplex("entityx2-morecomplex", false);

} // namespace entityx2_benchmark