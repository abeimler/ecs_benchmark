#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <benchpress/benchpress.hpp>

#include <ginseng/GinsengBenchmark.h>

namespace ginseng_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] ginseng  Creating 10M entities", [](benchpress::context *ctx) {
  EntityManager db;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity> created_entities(_10M);

    ctx->start_timer();
    for (size_t c = 0; c < _10M; c++) {
      auto entity = db.create_entity();
      created_entities.emplace_back(entity);
    }
    ctx->stop_timer();

    // cleanup memory to avoid full memory
    for (auto entity : created_entities) {
      db.destroy_entity(entity);
    }
  }
})

BENCHMARK("[2] ginseng  Destroying 10M entities", [](benchpress::context *ctx) {
  EntityManager db;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity> created_entities(_10M);

    for (size_t c = 0; c < _10M; c++) {
      auto entity = db.create_entity();
      created_entities.emplace_back(entity);
    }

    ctx->start_timer();
    for (auto entity : created_entities) {
      db.destroy_entity(entity);
    }
    ctx->stop_timer();
  }
})

BENCHMARK("[3] ginseng  Iterating over 10M entities, unpacking one component",
          [](benchpress::context *ctx) {
            EntityManager db;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = db.create_entity();
              db.add_component(entity, PositionComponent{});
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              db.visit([&](PositionComponent &position) {
                DISABLE_REDUNDANT_CODE_OPT();
                benchpress::escape(&position);
              });
            }
          })

BENCHMARK("[4] ginseng  Iterating over 10M entities, unpacking two components",
          [](benchpress::context *ctx) {
            EntityManager db;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = db.create_entity();
              db.add_component(entity, PositionComponent{});
              db.add_component(entity, DirectionComponent{});
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              db.visit([&](PositionComponent &position,
                           DirectionComponent &velocity) {
                DISABLE_REDUNDANT_CODE_OPT();
                benchpress::escape(&position);
                benchpress::escape(&velocity);
              });
            }
          })

BENCHMARK("ginseng  create destroy entity with components",
          [](benchpress::context *ctx) {
            EntityManager db;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = db.create_entity();

              db.add_component(entity, PositionComponent{});
              db.add_component(entity, DirectionComponent{});
              db.add_component(entity,
                               ComflabulationComponent{});

              db.destroy_entity(entity);
            }
          })

inline void init_entities(EntityManager &db,
                          size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = db.create_entity();

    db.add_component(entity, PositionComponent{});
    db.add_component(entity, DirectionComponent{});

    if (i % 2 != 0) {
      db.add_component(entity, ComflabulationComponent{});
    }
  }
}

inline void runEntitiesSystemsGinsengBenchmark(benchpress::context *ctx,
                                               size_t nentities) {
  Application app;
  auto &db = app.getEntityManager();

  init_entities(db, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(GinsengBenchmark::fakeDeltaTime);
  }
}

class BenchmarksGinseng {
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
        runEntitiesSystemsGinsengBenchmark(ctx, nentities);
      })
    }
  }

  BenchmarksGinseng(const std::string &name) { makeBenchmarks(name); }
};
const std::vector<int> BenchmarksGinseng::ENTITIES = {
    10,        25,        50,        100,        200,       400,     800,
    1600,      3200,      5000,      10'000,     30'000,    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000};

BenchmarksGinseng ginsengbenchmarks("ginseng");

} // namespace ginseng_benchmark
