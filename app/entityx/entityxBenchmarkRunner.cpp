#include <string>
#include <vector>
#include <thread>
#include <memory>

#include <benchpress/benchpress.hpp>

#include <entityx/EntityXBenchmark.h>

namespace entityx1_benchmark {

constexpr size_t _10M = 10'000'000L;

BENCHMARK("[1] entityx1 Creating 10M entities", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<EntityXBenchmark::Entity> created_entities (_10M);

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

BENCHMARK("[2] entityx1 Destroying 10M entities", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.entities;
    
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<EntityXBenchmark::Entity> created_entities (_10M);

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

BENCHMARK("[3] entityx1 Iterating over 10M entities, unpacking one component", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.entities;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = entities.create();
        entity.assign<EntityXBenchmark::PositionComponent>();
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXBenchmark::Component<EntityXBenchmark::PositionComponent> position;

        for (auto entity : entities.entities_with_components(position)) {
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(position.get());
        }
    }
})

BENCHMARK("[4] entityx1 Iterating over 10M entities, unpacking two components", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.entities;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = entities.create();
        entity.assign<EntityXBenchmark::PositionComponent>();
        entity.assign<EntityXBenchmark::DirectionComponent>();
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXBenchmark::Component<EntityXBenchmark::PositionComponent> position;
        EntityXBenchmark::Component<EntityXBenchmark::DirectionComponent> velocity;

        for (auto entity : entities.entities_with_components(position, velocity)) {
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(position.get());
            benchpress::escape(velocity.get());
        }
    }
})










BENCHMARK("entityx1 create destroy entity with components", [](benchpress::context* ctx) {
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
            ss << std::right << std::setw(12) << tag << ' ';
            ss << std::left << std::setw(8) << name << ' ';
            ss << std::right << std::setw(12) << nentities;
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
    10, 25, 50, 
    100, 200, 400, 800, 
    1600, 3200, 5000, 
    10'000, 30'000, 
    100'000, 500'000, 
    1'000'000, 2'000'000, 5'000'000,
    10'000'000, 20'000'000
};

BenchmarksEntityX entityxbenchmarks ("entityx1");


} // namespace entityx1_benchmark
