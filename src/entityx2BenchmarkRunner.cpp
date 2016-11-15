#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <sstream>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.hh"

#include "EntityX2Benchmark.h"

inline void init_entities(EntityX2Benchmark::EntityManager& entities, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
		auto entity = entities.create();

		entity.assign<EntityX2Benchmark::PositionComponent>();
		entity.assign<EntityX2Benchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityX2Benchmark::ComflabulationComponent>();
		}
	}
}

inline void runEntitiesSystemsEntityX2Benchmark(benchpress::context* ctx, size_t nentities) {
    EntityX2Benchmark::Application app;
    auto& entities = app.getEntityManager();

    init_entities(entities, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityX2Benchmark::fakeDeltaTime);
    }
}



BENCHMARK("entityx2 create destroy entity with components", [](benchpress::context* ctx) {
    EntityX2Benchmark::EntityManager entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = entities.create();

        entity.assign<EntityX2Benchmark::PositionComponent>();
		entity.assign<EntityX2Benchmark::DirectionComponent>();
		entity.assign<EntityX2Benchmark::ComflabulationComponent>();

        entities.destroy(entity.id());
    }
})


class BenchmarksEntityX2 {
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
                runEntitiesSystemsEntityX2Benchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEntityX2(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEntityX2::ENTITIES = {
    25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000
};

BenchmarksEntityX2 entityx2benchmarks ("entityx2");



