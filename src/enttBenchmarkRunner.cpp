#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <sstream>

#include "benchpress/benchpress.hpp"

#include "registry.hpp"

#include "EnttBenchmark.h"

inline void init_entities(EnttBenchmark::EntityManager& registry, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
	auto entity = registry.create();

	registry.assign<EnttBenchmark::PositionComponent>(entity);
	registry.assign<EnttBenchmark::DirectionComponent>(entity);


	if (i % 2) {
		registry.assign<EnttBenchmark::ComflabulationComponent>(entity);
	}
    }
}

inline void runEntitiesSystemsEnttBenchmark(benchpress::context* ctx, size_t nentities) {
    EnttBenchmark::Application app;
    auto& registry = app.getEntityManager();

    init_entities(registry, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EnttBenchmark::fakeDeltaTime);
    }
}

BENCHMARK("entt create destroy entity with components", [](benchpress::context* ctx) {
    EnttBenchmark::EntityManager registry;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = registry.create();

	registry.assign<EnttBenchmark::PositionComponent>(entity);
	registry.assign<EnttBenchmark::DirectionComponent>(entity);
	registry.assign<EnttBenchmark::ComflabulationComponent>(entity);

        registry.destroy(entity);
    }
})

class BenchmarksEntt {
    public:
    static const std::vector<int> ENTITIES;

    static inline void makeBenchmarks(std::string name) {
        makeBenchmarks(name, ENTITIES);
    }

    static void makeBenchmarks(std::string name, const std::vector<int>& entities) {
        for(int nentities : entities) {
            std::string tag = "[" + std::to_string(nentities) + "]";

            std::stringstream ss;
            ss << std::right << std::setw(10) << tag << ' ';
            ss << name << ' ';
            ss << std::right << std::setw(8) << nentities;
            ss << " entities component systems update";

            std::string benchmark_name = ss.str();
            BENCHMARK(benchmark_name, [nentities](benchpress::context* ctx) {
                runEntitiesSystemsEnttBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEntt(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEntt::ENTITIES = {
    25, 50,
    100, 200, 400, 800,
    1600, 3200, 5000,
    10'000, 30'000,
    100'000, 500'000,
    1'000'000, 2'000'000
};

BenchmarksEntt enttbenchmarks("entt");
