#include <artemis/ArtemisBenchmark.h>

#include <benchpress/benchpress.hpp>

#include <BaseBenchmark.h>

namespace artemis_benchmark {

BENCHMARK("artemis create destroy entity with components",
          [](benchpress::context *ctx) {
            artemis::World world;
            artemis::EntityManager *em = world.getEntityManager();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto &entity = em->create();

              entity.addComponent(new PositionComponent());
              entity.addComponent(new DirectionComponent());
              entity.addComponent(new ComflabulationComponent());

              entity.remove();
            }
          })

class BenchmarkArtemis
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Application,
                                          TimeDelta> {
public:
  BenchmarkArtemis(const std::string &name, bool addmorecomplexsystem)
      : BaseBenchmark(name, addmorecomplexsystem,
                      {10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                       30'000, 100'000, 500'000, 1'000'000, 2'000'000}) {}

  auto createOneEntity(EntityManager &registry) -> Entity& override {
    return registry.create();
  }
  void afterCreateEntity(EntityManager & /*registry*/, Entity &entity) override {
    entity.refresh();
  }
  void assignPositionComponent(EntityManager & /*registry*/,
                               Entity &entity) override {
    entity.addComponent(new PositionComponent());
  }
  void assignDirectionComponent(EntityManager & /*registry*/,
                                Entity &entity) override {
    entity.addComponent(new DirectionComponent());
  }
  void assignComflabulationComponent(EntityManager & /*registry*/,
                                     Entity &entity) override {
    entity.addComponent(new ComflabulationComponent());
  }

  auto createApplication(bool addmorecomplexsystem) -> Application override {
    return Application(addmorecomplexsystem);
  }
};


BenchmarkArtemis artemisbenchmarks("artemis", false);
BenchmarkArtemis artemisbenchmarks_morecomplex("artemis-morecomplex", true);

} // namespace artemis_benchmark