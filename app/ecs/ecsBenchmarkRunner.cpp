#include <ecs/ECSBenchmark.h>

#include <benchpress/benchpress.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace ecs_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] ecs     Creating 10M entities", [](benchpress::context *ctx) {
  EntityManager *registry = ECS::World::createWorld();

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity *> created_entities(_10M);

    ctx->start_timer();
    for (size_t c = 0; c < _10M; c++) {
      auto entity = registry->create();
      created_entities.emplace_back(entity);
    }
    ctx->stop_timer();

    registry->cleanup();
  }

  registry->destroyWorld();
})

BENCHMARK("[2] ecs     Destroying 10M entities", [](benchpress::context *ctx) {
  EntityManager *registry = ECS::World::createWorld();

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    std::vector<Entity *> created_entities(_10M);

    for (size_t c = 0; c < _10M; c++) {
      auto entity = registry->create();
      created_entities.emplace_back(entity);
    }

    ctx->start_timer();
    for (auto entity : created_entities) {
      registry->destroy(entity);
    }
    ctx->stop_timer();
  }

  registry->destroyWorld();
})

BENCHMARK("[3] ecs     Iterating over 10M entities, unpacking one component",
          [](benchpress::context *ctx) {
            EntityManager *registry = ECS::World::createWorld();

            for (size_t c = 0; c < _10M; c++) {
              auto entity = registry->create();
              entity->assign<PositionComponent>();
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              registry->each<PositionComponent>(
                  [&](Entity *entity, PositionComponentHandle position) {
                    DISABLE_REDUNDANT_CODE_OPT();

                    benchpress::escape(entity);
                    benchpress::escape(&position);
                  });
            }

            ctx->stop_timer();
            registry->destroyWorld();
          })

/// @NOTE: avoid "too many arguments provided to function-like macro
/// invocation"-error in BENCHMARK-Macro
/*
inline auto update_func_components_2 = [](Entity *entity,
                                          PositionComponentHandle position,
                                          DirectionComponentHandle velocity) {
  DISABLE_REDUNDANT_CODE_OPT();

  benchpress::escape(entity);
  benchpress::escape(&position);
  benchpress::escape(&velocity);
};
inline auto for_each_update_func_components_2 = [](EntityManager *registry) {
  registry->each<PositionComponent, DirectionComponent>(
      update_func_components_2);
};
BENCHMARK("[4] ecs     Iterating over 10M entities, unpacking two components",
          [](benchpress::context *ctx) {
            EntityManager *registry = ECS::World::createWorld();

            for (size_t c = 0; c < _10M; c++) {
              auto entity = registry->create();
              entity->assign<PositionComponent>();
              entity->assign<DirectionComponent>();
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              for_each_update_func_components_2(registry);
            }

            ctx->stop_timer();
            registry->destroyWorld();
          })
*/

BENCHMARK("[6] ecs     Destroying 10M entities at once",
          [](benchpress::context *ctx) {
            EntityManager *registry = ECS::World::createWorld();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              ctx->stop_timer();
              for (size_t c = 0; c < _10M; c++) {
                auto entity = registry->create();
              }

              ctx->start_timer();
              registry->cleanup();
              ctx->stop_timer();
            }

            ctx->stop_timer();
            registry->destroyWorld();
          })

BENCHMARK("ecs     create destroy entity with components",
          [](benchpress::context *ctx) {
            EntityManager *registry = ECS::World::createWorld();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = registry->create();

              entity->assign<PositionComponent>();
              entity->assign<DirectionComponent>();
              entity->assign<ComflabulationComponent>();

              registry->destroy(entity);
            }

            ctx->stop_timer();
            registry->destroyWorld();
          })

inline void init_entities(EntityManager *registry, size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = registry->create();

    entity->assign<PositionComponent>();
    entity->assign<DirectionComponent>();

    if (i % 2 != 0) {
      entity->assign<ComflabulationComponent>();
    }
  }
}

inline void runEntitiesSystemsECSBenchmark(benchpress::context *ctx,
                                           size_t nentities,
                                           bool addmorecomplexsystem) {
  Application app(addmorecomplexsystem);
  auto registry = app.getEntityManager();

  init_entities(registry, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(ECSBenchmark::fakeDeltaTime);
  }
}

class BenchmarksECS {
public:
  static const std::vector<int> ENTITIES;

  static inline void makeBenchmarks(const std::string &name,
                                    bool addmorecomplexsystem) {
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
        runEntitiesSystemsECSBenchmark(ctx, nentities, addmorecomplexsystem);
      })
    }
  }

  BenchmarksECS(const std::string &name, bool addmorecomplexsystem) {
    makeBenchmarks(name, addmorecomplexsystem);
  }
};
const std::vector<int> BenchmarksECS::ENTITIES = {
    10,        25,        50,        100,        200,       400,     800,
    1600,      3200,      5000,      10'000,     30'000,    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000};

BenchmarksECS ecsbenchmarks("ecs", false);
BenchmarksECS ecsbenchmarks_morecomplex("ecs-morecomplex", true);

} // namespace ecs_benchmark
