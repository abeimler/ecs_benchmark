#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include <anax/anax.hpp>

#include "AnaxBenchmark.h"

namespace anax_benchmark {


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



class AnaxBenchmarks {
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
                runEntitiesSystemsAnaxBenchmark(ctx, nentities);
            })
        }
    }

    AnaxBenchmarks(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> AnaxBenchmarks::ENTITIES = {
    25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000
};

AnaxBenchmarks anaxbenchmarks ("anax");



} // namespace anax_benchmark

