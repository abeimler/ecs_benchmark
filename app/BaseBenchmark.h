#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <benchpress/benchpress.hpp>

namespace ecs_benchmark {

template <class EntityManager, class Entity, class Application,
          typename TimeDelta>
class BaseBenchmark {
private:
  const std::string name_;
  const bool addmorecomplexsystem_;
  const std::vector<int> entities_;

  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;

public:
  BaseBenchmark(const std::string &name)
      : name_(name), addmorecomplexsystem_(false),
        entities_({10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                   30'000, 100'000, 500'000, 1'000'000, 2'000'000, 5'000'000}) {
    makeBenchmarks();
  }
  BaseBenchmark(const std::string &name, bool addmorecomplexsystem)
      : name_(name), addmorecomplexsystem_(addmorecomplexsystem),
        entities_({10, 25, 50, 100, 200, 400, 800, 1600, 3200, 5000, 10'000,
                   30'000, 100'000, 500'000, 1'000'000, 2'000'000, 5'000'000}) {
    makeBenchmarks();
  }
  BaseBenchmark(const std::string &name, bool addmorecomplexsystem,
                const std::vector<int> &entities)
      : name_(name), addmorecomplexsystem_(addmorecomplexsystem),
        entities_(entities) {
    makeBenchmarks();
  }
  virtual ~BaseBenchmark() = default;

  virtual Entity& createOneEntity(EntityManager &registry) = 0;
  virtual void afterCreateEntity(EntityManager &registry, Entity &entity) {}
  virtual void assignPositionComponent(EntityManager &registry,
                                       Entity &entity) = 0;
  virtual void assignDirectionComponent(EntityManager &registry,
                                        Entity &entity) = 0;
  virtual void assignComflabulationComponent(EntityManager &registry,
                                             Entity &entity) = 0;

  virtual Application createApplication(bool addmorecomplexsystem) = 0;
  virtual void afterBenchmark(Application& app) {}

  void runEntitiesSystemsBenchmark(benchpress::context *ctx, int nentities) {
    Application app = this->createApplication(this->addmorecomplexsystem_);
    auto &registry = app.getEntityManager();

    this->init_entities(registry, nentities);
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
      app.update(fakeDeltaTime);
    }
    ctx->stop_timer();
    this->afterBenchmark(app);
  }

  void init_entities(EntityManager &registry, int nentities) {
    for (size_t i = 0; i < nentities; i++) {
      auto&& entity = createOneEntity(registry);

      assignPositionComponent(registry, entity);
      assignDirectionComponent(registry, entity);

      if (i % 2 != 0) {
        assignComflabulationComponent(registry, entity);
      }
    }
  }

  void makeBenchmarks() {
    for (int nentities : this->entities_) {
      std::string tag = fmt::format("[{}]", nentities);
      std::string benchmark_name =
          fmt::format("{:>12} {:<10} {:>12} entities component systems update",
                      tag, this->name_, nentities);

      std::function<void(benchpress::context *)> benchmark_func =
          [=](benchpress::context *ctx) {
            this->runEntitiesSystemsBenchmark(ctx, nentities);
          };

      BENCHMARK(benchmark_name, benchmark_func)
    }
  }
};

} // namespace benchmark_ecs_app