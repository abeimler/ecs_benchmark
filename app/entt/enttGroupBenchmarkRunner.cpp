#include <benchpress/benchpress.hpp>

#include <entt/EnttGroupBenchmark.h>

#include <BaseBenchmark.h>

namespace enttgroup_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK(
    "[4] entt-group     Iterating over 10M entities, unpacking two components",
    [](benchpress::context *ctx) {
      EntityManager registry;

      for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<PositionComponent>(entity);
        registry.assign<DirectionComponent>(entity);
      }

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        registry.group<PositionComponent>(entt::get<DirectionComponent>)
            .each([](auto entity, auto &position, auto &velocity) {
              DISABLE_REDUNDANT_CODE_OPT();
              benchpress::escape(&entity);
              benchpress::escape(&position);
              benchpress::escape(&velocity);
            });
      }
    })

class BenchmarkEnttGroup
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Application,
                                          TimeDelta> {
public:
  BenchmarkEnttGroup(const std::string &name, bool addmorecomplexsystem)
      : BaseBenchmark(name, addmorecomplexsystem,
                      {10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                       30'000, 100'000, 500'000, 1'000'000, 2'000'000,
                       5'000'000, 10'000'000, 20'000'000}) {}

  auto createOneEntity(EntityManager &registry) -> Entity& override {
    return this->entities_.emplace_back(registry.create());
  }
  void afterBenchmark(Application&  /*app*/) override {
    this->entities_.clear();
  }
  void assignPositionComponent(EntityManager &registry,
                               Entity &entity) override {
    registry.assign<PositionComponent>(entity);
  }
  void assignDirectionComponent(EntityManager &registry,
                                Entity &entity) override {
    registry.assign<DirectionComponent>(entity);
  }
  void assignComflabulationComponent(EntityManager &registry,
                                     Entity &entity) override {
    registry.assign<ComflabulationComponent>(entity);
  }

  auto createApplication(bool addmorecomplexsystem) -> Application override {
    return Application(addmorecomplexsystem);
  }
private:
  std::vector<Entity> entities_;
};

BenchmarkEnttGroup enttgroupbenchmarks("entt-group", false);
BenchmarkEnttGroup enttgroupbenchmarks_morecomplex("entt-group-morecomplex",
                                                    true);

} // namespace enttgroup_benchmark
