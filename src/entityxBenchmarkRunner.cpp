#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.h"

#include "EntityXBenchmark.h"

inline void init_entities(entityx::EntityManager& entities, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}
}

inline void runEntitiesSystemsEntityXBenchmark(benchpress::context* ctx, size_t nentities) {
    EntityXBenchmark::Application app;
    auto& entities = app.entities;

    init_entities(entities, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
}




BENCHMARK("entityx create destroy entity with components", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = entities.create();

        entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();
		entity.assign<EntityXBenchmark::ComflabulationComponent>();

        entity.destroy();
    }
})





class BenchmarksEntityX {
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
                runEntitiesSystemsEntityXBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEntityX(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEntityX::ENTITIES = {
    25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000
};

BenchmarksEntityX entityxbenchmarks ("entityx");





/*
BENCHMARK("[25]     entityx      25 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 25);
})

BENCHMARK("[50]     entityx      50 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 50);
})

BENCHMARK("[100]    entityx     100 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 100);
})

BENCHMARK("[200]    entityx     200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 200);
})


BENCHMARK("[400]    entityx     400 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 400);
})


BENCHMARK("[800]    entityx     800 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 800);
})


BENCHMARK("[1600]    entityx   1600 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 1600);
})



BENCHMARK("[3200]    entityx   3200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 3200);
})


BENCHMARK("[5000]    entityx   5000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 5000);
})


BENCHMARK("[10000]   entityx  10000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 10'000);
})

BENCHMARK("[30000]   entityx  30000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 30'000);
})


BENCHMARK("[100000]  entityx 100000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 100'000L);
})


BENCHMARK("[500000]  entityx 500000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 500'000L);
})

BENCHMARK("[1000000] entityx     1M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 1'000'000L);
})

BENCHMARK("[2000000] entityx     2M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsEntityXBenchmark(ctx, 2'000'000L);
})
*/