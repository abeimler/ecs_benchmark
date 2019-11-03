#include <string>
#include <vector>
#include <thread>
#include <memory>

#include <Artemis/Artemis.h>

#include <benchpress/benchpress.hpp>

#include <artemis/ArtemisBenchmark.h>








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
            std::string tag = fmt::format("[{}]", nentities);
            std::string benchmark_name = fmt::format("{:>12} {:<10} {:>12} entities component systems update", tag, name, nentities);
            
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
    10, 25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000
};

BenchmarksArtemis artemisbenchmarks ("artemis");


