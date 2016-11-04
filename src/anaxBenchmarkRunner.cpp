#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include <anax/anax.hpp>

#include "AnaxBenchmark.h"

inline void init_entities(anax::World& entities, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
		auto entity = entities.createEntity();

		entity.addComponent<AnaxBenchmark::PositionComponent>();
		entity.addComponent<AnaxBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.addComponent<AnaxBenchmark::ComflabulationComponent>();
		}

        entity.activate();
	}
}

inline void runEntitiesSystemsAnaxBenchmark(benchpress::context* ctx, size_t nentities) {
    AnaxBenchmark::Application app;

    init_entities(app, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(AnaxBenchmark::fakeDeltaTime);
    }
}









BENCHMARK("anax create destroy entity with components", [](benchpress::context* ctx) {
    anax::World entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = entities.createEntity();

        entity.addComponent<AnaxBenchmark::PositionComponent>();
		entity.addComponent<AnaxBenchmark::DirectionComponent>();
		entity.addComponent<AnaxBenchmark::ComflabulationComponent>();

        entity.kill();
    }
})




BENCHMARK("anax    25 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 25);
})

BENCHMARK("anax    50 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 50);
})

BENCHMARK("anax   100 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 100);
})

BENCHMARK("anax   200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 200);
})


BENCHMARK("anax   400 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 400);
})


BENCHMARK("anax   800 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 800);
})


BENCHMARK("anax  1600 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 1600);
})



BENCHMARK("anax  3200 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 3200);
})


BENCHMARK("anax  5000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 5000);
})


BENCHMARK("anax 10000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 10'000);
})

BENCHMARK("anax 30000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 30'000);
})

BENCHMARK("anax 100000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 100'000L);
})


BENCHMARK("anax 500000 entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 500'000L);
})

BENCHMARK("anax 1M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 1'000'000L);
})


BENCHMARK("anax 2M entities component systems update", [](benchpress::context* ctx) {
    runEntitiesSystemsAnaxBenchmark(ctx, 2'000'000L);
})

