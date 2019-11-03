#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <sstream>

#include <benchpress/benchpress.hpp>

#include <entt/EnttGroupBenchmark.h>

namespace enttgroup_benchmark {

constexpr size_t _10M = 10'000'000L;




BENCHMARK("[4] entt-group     Iterating over 10M entities, unpacking two components", [](benchpress::context* ctx) {
    EnttGroupBenchmark::EntityManager registry;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttGroupBenchmark::PositionComponent>(entity);
        registry.assign<EnttGroupBenchmark::DirectionComponent>(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        registry.group<EnttGroupBenchmark::PositionComponent>(entt::get<EnttGroupBenchmark::DirectionComponent>).each([](auto entity, auto &position, auto &velocity) {
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(&position);
            benchpress::escape(&velocity);
        });
    }
})





inline void init_entities(EnttGroupBenchmark::EntityManager& registry, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
        auto entity = registry.create();

        registry.assign<EnttGroupBenchmark::PositionComponent>(entity);
        registry.assign<EnttGroupBenchmark::DirectionComponent>(entity);


        if (i % 2) {
            registry.assign<EnttGroupBenchmark::ComflabulationComponent>(entity);
        }
    }
}

inline void runEntitiesSystemsEnttGroupBenchmark(benchpress::context* ctx, size_t nentities) {
    EnttGroupBenchmark::Application app;
    auto& registry = app.getEntityManager();

    init_entities(registry, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EnttGroupBenchmark::fakeDeltaTime);
    }
}



class BenchmarksEnttGroup {
    public:
    static const std::vector<int> ENTITIES;

    static inline void makeBenchmarks(std::string name) {
        makeBenchmarks(name, ENTITIES);
    }

    static void makeBenchmarks(std::string name, const std::vector<int>& entities) {
        for(int nentities : entities) {
            std::string tag = fmt::format("[{}]", nentities);
            std::string benchmark_name = fmt::format("{:>12} {:<10} {:>12} entities component systems update", tag, name, nentities);
            
            BENCHMARK(benchmark_name, [nentities](benchpress::context* ctx) {
                runEntitiesSystemsEnttGroupBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEnttGroup(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEnttGroup::ENTITIES = {
    10, 25, 50,
    100, 200, 400, 800,
    1600, 3200, 5000,
    10'000, 30'000,
    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000,
    10'000'000, 20'000'000
};

BenchmarksEnttGroup enttgroupbenchmarks("entt-group");


} // namespace enttgroup_benchmark
