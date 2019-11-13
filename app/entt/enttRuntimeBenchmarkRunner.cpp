#include <benchpress/benchpress.hpp>

#include <entt/EnttRuntimeBenchmark.h>

#include <BaseBenchmark.h>

namespace enttruntime_benchmark {

constexpr size_t _10M = 10'000'000L;

/// @NOTE: void "too many arguments provided to function-like macro
/// invocation"-error in BENCHMARK-Macro
typedef std::array<entt::component, 1> array_types_component_1;
typedef std::array<entt::component, 2> array_types_component_2;
array_types_component_1 array_types_1 = {
    EntityManager::type<PositionComponent>()};

array_types_component_2 array_types_2 = {
    EntityManager::type<PositionComponent>(),
    EntityManager::type<DirectionComponent>()};

BENCHMARK(
    "[3] entt-runtime     Iterating over 10M entities, unpacking one component",
    [](benchpress::context *ctx) {
      EntityManager registry;

      for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<PositionComponent>(entity);
      }
      array_types_component_1 &types_1 = array_types_1;

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for (auto entity :
             registry.runtime_view(std::begin(types_1), std::end(types_1))) {
          DISABLE_REDUNDANT_CODE_OPT();
          auto &position = registry.get<PositionComponent>(entity);

          benchpress::escape(&entity);
          benchpress::escape(&position);
        }
      }
    })

BENCHMARK("[4] entt-runtime     Iterating over 10M entities, unpacking two "
          "components",
          [](benchpress::context *ctx) {
            EntityManager registry;

            for (size_t c = 0; c < _10M; c++) {
              auto entity = registry.create();
              registry.assign<PositionComponent>(entity);
              registry.assign<DirectionComponent>(entity);
            }
            array_types_component_2 &types_2 = array_types_2;

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              for (auto entity : registry.runtime_view(std::begin(types_2),
                                                       std::end(types_2))) {
                DISABLE_REDUNDANT_CODE_OPT();
                auto &position = registry.get<PositionComponent>(entity);
                auto &velocity = registry.get<DirectionComponent>(entity);

                benchpress::escape(&entity);
                benchpress::escape(&position);
                benchpress::escape(&velocity);
              }
            }
          })

inline void init_entities(EntityManager &registry, size_t nentities) {
  for (size_t i = 0; i < nentities; i++) {
    auto entity = registry.create();

    registry.assign<PositionComponent>(entity);
    registry.assign<DirectionComponent>(entity);

    if (i % 2 != 0) {
      registry.assign<ComflabulationComponent>(entity);
    }
  }
}

inline void runEntitiesSystemsEnttRuntimeBenchmark(benchpress::context *ctx,
                                                   size_t nentities) {
  Application app;
  auto &registry = app.getEntityManager();

  init_entities(registry, nentities);

  ctx->reset_timer();
  for (size_t i = 0; i < ctx->num_iterations(); ++i) {
    app.update(EnttRuntimeBenchmark::fakeDeltaTime);
  }
}

class BenchmarkEnttRuntime
    : public ecs_benchmark::BaseBenchmark<EntityManager, Entity, Application,
                                          TimeDelta> {
public:
  BenchmarkEnttRuntime(const std::string &name, bool addmorecomplexsystem)
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

BenchmarkEnttRuntime enttbenchmarks("entt-runtime", false);
BenchmarkEnttRuntime enttbenchmarks_morecomplex("entt-runtime-morecomplex", true);

} // namespace enttruntime_benchmark
