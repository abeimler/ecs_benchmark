#include <ginseng/GinsengBenchmark.h>

#include <BaseBenchmark.h>

#include <benchpress/benchpress.hpp>

namespace ginseng_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] ginseng  Creating 10M entities", [](benchpress::context *ctx) {
  EntityManager db;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    ctx->stop_timer();
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
    ctx->stop_timer();
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
              db.add_component(entity, ComflabulationComponent{});

              db.destroy_entity(entity);
            }
          })

class BenchmarkGinseng
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Entity, Application,
                                          TimeDelta> {
public:
  BenchmarkGinseng(const std::string &name, bool addmorecomplexsystem)
      : BaseBenchmark(name, addmorecomplexsystem,
                      {10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                       30'000, 100'000, 500'000, 1'000'000, 2'000'000,
                       5'000'000, 10'000'000, 20'000'000}) {}
  ~BenchmarkGinseng() override = default;

  auto createOneEntity(EntityManager &db) -> Entity override {
    return db.create_entity();
  }
  void assignPositionComponent(EntityManager &db, Entity &entity) override {
    db.add_component(entity, PositionComponent{});
  }
  void assignDirectionComponent(EntityManager &db, Entity &entity) override {
    db.add_component(entity, DirectionComponent{});
  }
  void assignComflabulationComponent(EntityManager &db,
                                     Entity &entity) override {
    db.add_component(entity, ComflabulationComponent{});
  }

};

BenchmarkGinseng ginsengbenchmarks("ginseng", false);
BenchmarkGinseng ginsengbenchmarks_morecomplex("ginseng-morecomplex", true);

} // namespace ginseng_benchmark
