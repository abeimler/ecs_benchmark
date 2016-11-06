#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include <Artemis/Artemis.h>

#include "ArtemisBenchmark.h"

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
            ss << std::right << std::setw(10) << tag << ' ';
            ss << name << ' ';
            ss << std::right << std::setw(8) << nentities;
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



/*

BENCHMARK("artemis    25 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 25);
})





BENCHMARK("artemis    50 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 50);
})



BENCHMARK("artemis   100 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 100);
})







BENCHMARK("artemis   200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 200);
})







BENCHMARK("artemis   400 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 400);
})





BENCHMARK("artemis   800 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 800);
})



BENCHMARK("artemis  1600 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 1600);
})



BENCHMARK("artemis  3200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 3200);
})


BENCHMARK("artemis  5000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 5000);
})



BENCHMARK("artemis 10000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 10'000);
})

BENCHMARK("artemis 30000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 30'000);
})



BENCHMARK("artemis 100000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 100'000L);
})


BENCHMARK("artemis 500000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 500'000L);
})


BENCHMARK("artemis 1M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 1'000'000L);
})


BENCHMARK("artemis 2M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsArtemisBenchmark(ctx, 2'000'000L);
})



*/