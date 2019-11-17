#include <ecs/ECSBenchmark.h>

#include <BaseBenchmark.h>

#include <benchpress/benchpress.hpp>

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

  ctx->stop_timer();
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

  ctx->stop_timer();
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

class BenchmarkECS
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Entity*, Application,
                                          TimeDelta> {
public:
  BenchmarkECS(const std::string &name, bool addmorecomplexsystem)
      : BaseBenchmark(name, addmorecomplexsystem,
                      {10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                       30'000, 100'000, 500'000, 1'000'000, 2'000'000,
                       5'000'000, 10'000'000, 20'000'000}) {}
  ~BenchmarkECS() override = default;

  auto createOneEntity(EntityManager &registry) -> Entity* override {
    return registry.create();
  }
  void assignPositionComponent(EntityManager & /*registry*/,
                               Entity *&entity) override {
    entity->assign<PositionComponent>();
  }
  void assignDirectionComponent(EntityManager & /*registry*/,
                                Entity *&entity) override {
    entity->assign<DirectionComponent>();
  }
  void assignComflabulationComponent(EntityManager & /*registry*/,
                                     Entity *&entity) override {
    entity->assign<ComflabulationComponent>();
  }
};

BenchmarkECS ecsbenchmarks("ecs", false);
BenchmarkECS ecsbenchmarks_morecomplex("ecs-morecomplex", true);

} // namespace ecs_benchmark
