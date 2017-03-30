#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <sstream>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.hh"

#include "EntityX2Benchmark.h"

namespace entityx2_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("entityx2 Creating 10M entities", [](benchpress::context* ctx) {
    EntityX2Benchmark::EntityManager entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<EntityX2Benchmark::Entity> created_entities (_10M);

        ctx->start_timer();
        for (size_t c = 0; c < _10M; c++) {
            auto entity = entities.create();
            created_entities.emplace_back(entity);
        }
        ctx->stop_timer();

        // cleanup memory to avoid full memory 
        for (auto entity : created_entities) {
            entities.destroy(entity.id());
        }
    }
})

BENCHMARK("entityx2 Destroying 10M entities", [](benchpress::context* ctx) {
    EntityX2Benchmark::EntityManager entities;
    
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<EntityX2Benchmark::Entity> created_entities (_10M);

        for (size_t c = 0; c < _10M; c++) {
            auto entity = entities.create();
            created_entities.emplace_back(entity);
        }
        
        ctx->start_timer();
        for (auto entity : created_entities) {
            entities.destroy(entity.id());
        }
        ctx->stop_timer();
    }
})

BENCHMARK("entityx2 Iterating over 10M entities, unpacking one component", [](benchpress::context* ctx) {
    EntityX2Benchmark::EntityManager entities;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = entities.create();
        entity.assign<EntityX2Benchmark::PositionComponent>();
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityX2Benchmark::Component<EntityX2Benchmark::PositionComponent> position;

        for (auto entity : entities.entities_with_components(position)) {
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(position.get());
        }
    }
})

BENCHMARK("entityx2 Iterating over 10M entities, unpacking two components", [](benchpress::context* ctx) {
    EntityX2Benchmark::EntityManager entities;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = entities.create();
        entity.assign<EntityX2Benchmark::PositionComponent>();
        entity.assign<EntityX2Benchmark::DirectionComponent>();
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityX2Benchmark::Component<EntityX2Benchmark::PositionComponent> position;
        EntityX2Benchmark::Component<EntityX2Benchmark::DirectionComponent> velocity;

        for (auto entity : entities.entities_with_components(position, velocity)) {
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(position.get());
            benchpress::escape(velocity.get());
        }
    }
})







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
            ss << std::right << std::setw(12) << tag << ' ';
            ss << std::left << std::setw(8) << name << ' ';
            ss << std::right << std::setw(12) << nentities;
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
    10, 25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000, 5'000'000,
    10'000'000
};

BenchmarksEntityX2 entityx2benchmarks ("entityx2");



} // namespace entityx2_benchmark