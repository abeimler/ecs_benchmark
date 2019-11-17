#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <benchpress/benchpress.hpp>

namespace ecs_benchmark {

template <class EntityManager, class Entity, typename EntityCreatedType,
          class Application, typename TimeDelta>
class BaseBenchmark {
protected:
  const std::string name_;
  const bool addmorecomplexsystem_;
  const std::vector<int> entities_;

private:
  void init_entities(EntityManager &registry, int nentities) {
    for (size_t i = 0; i < nentities; i++) {
      EntityCreatedType entity = createOneEntity(registry);

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
          fmt::format("{:>14} {:<16} {:>12} entities component systems update",
                      tag, this->name_, nentities);

      std::function<void(benchpress::context *)> benchmark_func =
          [this, nentities = nentities](benchpress::context *ctx) {
            Application app;
            auto &registry = app.getEntityManager();
            this->init_entities(registry, nentities);

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              app.update(this->fakeDeltaTime);
            }

            ctx->stop_timer();
            this->afterBenchmark(app);
          };

      BENCHMARK(benchmark_name, benchmark_func)
    }
  }

public:
  const TimeDelta fakeDeltaTime = 1.0 / 60;

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

  virtual EntityCreatedType createOneEntity(EntityManager &registry) = 0;
  virtual void afterCreateEntity(EntityManager &registry,
                                 EntityCreatedType &entity) {}
  virtual void assignPositionComponent(EntityManager &registry,
                                       EntityCreatedType &entity) = 0;
  virtual void assignDirectionComponent(EntityManager &registry,
                                        EntityCreatedType &entity) = 0;
  virtual void assignComflabulationComponent(EntityManager &registry,
                                             EntityCreatedType &entity) = 0;

  virtual void afterBenchmark(Application &app) {}
};

} // namespace ecs_benchmark