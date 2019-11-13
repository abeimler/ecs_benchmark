#include <benchpress/benchpress.hpp>

#include <anax/AnaxBenchmark.h>

#include <BaseBenchmark.h>

namespace anax_benchmark {

BENCHMARK("anax create destroy entity with components",
          [](benchpress::context *ctx) {
            EntityManager entities;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = entities.createEntity();

              entity.addComponent<PositionComponent>();
              entity.addComponent<DirectionComponent>();
              entity.addComponent<ComflabulationComponent>();

              entity.kill();
            }
          })

class BenchmarkAnax
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Application,
                                          TimeDelta> {
public:
  BenchmarkAnax(const std::string &name, bool addmorecomplexsystem)
      : BaseBenchmark(name, addmorecomplexsystem,
                      {10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                       30'000, 100'000, 500'000, 1'000'000, 2'000'000}) {}

  auto createOneEntity(EntityManager &registry) -> Entity& override {
    return this->entities_.emplace_back(registry.createEntity());
  }
  void afterCreateEntity(EntityManager & /*registry*/, Entity &entity) override {
    entity.activate();
  }
  void afterBenchmark(Application&  /*app*/) override {
    this->entities_.clear();
  }
  void assignPositionComponent(EntityManager & /*registry*/,
                               Entity &entity) override {
    entity.addComponent<PositionComponent>();
  }
  void assignDirectionComponent(EntityManager & /*registry*/,
                                Entity &entity) override {
    entity.addComponent<DirectionComponent>();
  }
  void assignComflabulationComponent(EntityManager & /*registry*/,
                                     Entity &entity) override {
    entity.addComponent<ComflabulationComponent>();
  }

  auto createApplication(bool addmorecomplexsystem) -> Application override {
    return Application(addmorecomplexsystem);
  }
private:
  std::vector<Entity> entities_;
};

BenchmarkAnax anaxbenchmarks("anax", false);
BenchmarkAnax anaxbenchmarks_morecomplex("anax-morecomplex", true);

} // namespace anax_benchmark
