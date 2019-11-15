#include <benchpress/benchpress.hpp>

#include <entityx/EntityXBenchmark.h>

#include <BaseBenchmark.h>

namespace entityx1_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] entityx1 Creating 10M entities", [](benchpress::context *ctx) {
  Application app;
  auto &entities = app.entities;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    ctx->stop_timer();
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

BENCHMARK("[2] entityx1 Destroying 10M entities", [](benchpress::context *ctx) {
  Application app;
  auto &entities = app.entities;

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    ctx->stop_timer();
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

BENCHMARK("[3] entityx1 Iterating over 10M entities, unpacking one component",
          [](benchpress::context *ctx) {
            Application app;
            auto &entities = app.entities;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = entities.create();
              entity.assign<PositionComponent>();
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              Component<PositionComponent> position;

              for (auto entity : entities.entities_with_components(position)) {
                DISABLE_REDUNDANT_CODE_OPT();
                benchpress::escape(&entity);
                benchpress::escape(position.get());
              }
            }
          })

BENCHMARK("[4] entityx1 Iterating over 10M entities, unpacking two components",
          [](benchpress::context *ctx) {
            Application app;
            auto &entities = app.entities;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = entities.create();
              entity.assign<PositionComponent>();
              entity.assign<DirectionComponent>();
            }

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              Component<PositionComponent> position;
              Component<DirectionComponent> velocity;

              for (auto entity :
                   entities.entities_with_components(position, velocity)) {
                DISABLE_REDUNDANT_CODE_OPT();
                benchpress::escape(&entity);
                benchpress::escape(position.get());
                benchpress::escape(velocity.get());
              }
            }
          })

BENCHMARK("entityx1 create destroy entity with components",
          [](benchpress::context *ctx) {
            Application app;
            auto &entities = app.entities;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = entities.create();

              entity.assign<PositionComponent>();
              entity.assign<DirectionComponent>();
              entity.assign<ComflabulationComponent>();

              entity.destroy();
            }
          })

class BenchmarkEntityX
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Entity, Application,
                                          TimeDelta> {
public:
  BenchmarkEntityX(const std::string &name, bool addmorecomplexsystem)
      : BaseBenchmark(name, addmorecomplexsystem,
                      {10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                       30'000, 100'000, 500'000, 1'000'000, 2'000'000,
                       5'000'000, 10'000'000, 20'000'000}) {}
  ~BenchmarkEntityX() override = default;

  auto createOneEntity(EntityManager &registry) -> Entity override {
    return registry.create();
  }
  void assignPositionComponent(EntityManager & /*registry*/,
                               Entity &entity) override {
    entity.assign<PositionComponent>();
  }
  void assignDirectionComponent(EntityManager & /*registry*/,
                                Entity &entity) override {
    entity.assign<DirectionComponent>();
  }
  void assignComflabulationComponent(EntityManager & /*registry*/,
                                     Entity &entity) override {
    entity.assign<ComflabulationComponent>();
  }

};

BenchmarkEntityX entityxbenchmarks("entityx1", false);
BenchmarkEntityX entityxbenchmarks_morecomplex("entityx1-morecomplex", true);

} // namespace entityx1_benchmark
