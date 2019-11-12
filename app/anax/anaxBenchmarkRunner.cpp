#include <anax/AnaxBenchmark.h>

#include <anax/anax.hpp>
#include <benchpress/benchpress.hpp>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace anax_benchmark {

BENCHMARK("anax create destroy entity with components",
          [](benchpress::context *ctx) {
            anax::World entities;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              auto entity = entities.createEntity();

              entity.addComponent<PositionComponent>();
              entity.addComponent<DirectionComponent>();
              entity.addComponent<ComflabulationComponent>();

              entity.kill();
            }
          })

inline void init_entities(anax::World &entities, size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = entities.createEntity();

    entity.addComponent<PositionComponent>();
    entity.addComponent<DirectionComponent>();

    if (i % 2 != 0) {
      entity.addComponent<ComflabulationComponent>();
    }

    entity.activate();
  }
}

inline void runEntitiesSystemsAnaxBenchmark(benchpress::context *ctx,
                                            size_t nentities) {
  Application app;

  init_entities(app, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(AnaxBenchmark::fakeDeltaTime);
  }
}

class AnaxBenchmarks {
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
        runEntitiesSystemsAnaxBenchmark(ctx, nentities);
      })
    }
  }

  AnaxBenchmarks(const std::string &name) { makeBenchmarks(name); }
};
const std::vector<int> AnaxBenchmarks::ENTITIES = {
    10,   25,   50,     100,    200,     400,     800,       1600,
    3200, 5000, 10'000, 30'000, 100'000, 500'000, 1'000'000, 2'000'000};

AnaxBenchmarks anaxbenchmarks("anax");

} // namespace anax_benchmark
