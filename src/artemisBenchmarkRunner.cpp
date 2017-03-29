#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include <Artemis/Artemis.h>

#include "ArtemisBenchmark.h"








BENCHMARK("artemis create destroy entity with components", [](benchpress::context* ctx) {
    artemis::World world;
    artemis::EntityManager* em = world.getEntityManager();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto& entity = em->create();

        entity.addComponent(new ArtemisBenchmark::PositionComponent());
		entity.addComponent(new ArtemisBenchmark::DirectionComponent());
		entity.addComponent(new ArtemisBenchmark::ComflabulationComponent());

        entity.remove();
    }
})








inline void init_entities(artemis::EntityManager* entities, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
		auto& entity = entities->create();

		entity.addComponent(new ArtemisBenchmark::PositionComponent());
		entity.addComponent(new ArtemisBenchmark::DirectionComponent());

		if (i % 2) {
			entity.addComponent(new ArtemisBenchmark::ComflabulationComponent());
		}

        entity.refresh();
	}
}

inline void runEntitiesSystemsArtemisBenchmark(benchpress::context* ctx, size_t nentities) {
    ArtemisBenchmark::Application app;
    auto entities = app.getEntityManager();

    init_entities(entities, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(ArtemisBenchmark::fakeDeltaTime);
    }
}


class BenchmarksArtemis {
    public:
    static const std::vector<int> ENTITIES;

    static inline void makeBenchmarks(std::string name) {
        makeBenchmarks(name, ENTITIES);
    }
    
    static void makeBenchmarks(std::string name, const std::vector<int>& entities) {
        for(int nentities : entities) {
            std::string tag = "[" + std::to_string(nentities) + "]";

            std::stringstream ss;
            ss << std::right << std::setw(12) << tag << ' ';
            ss << std::left << std::setw(8) << name << ' ';
            ss << std::right << std::setw(12) << nentities;
            ss << " entities component systems update";

            std::string benchmark_name = ss.str();
            BENCHMARK(benchmark_name, [nentities](benchpress::context* ctx) {
                runEntitiesSystemsArtemisBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksArtemis(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksArtemis::ENTITIES = {
    25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000
};

BenchmarksArtemis artemisbenchmarks ("artemis");


