#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <sstream>

#include "benchpress/benchpress.hpp"

#include "GinsengBenchmark.h"

namespace ginseng_benchmark {

constexpr size_t _10M = 10'000'000L;


BENCHMARK("[1] ginseng     Creating 10M entities", [](benchpress::context* ctx) {
    GinsengBenchmark::EntityManager db;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<GinsengBenchmark::Entity> created_entities (_10M);

        ctx->start_timer();
        for (size_t c = 0; c < _10M; c++) {
            auto entity = db.create_entity();
            created_entities.emplace_back(entity);
        }
        ctx->stop_timer();

        // cleanup memory to avoid full memory 
        for (auto entity : created_entities) {
            db.destroy_entity(entity);
        }
    }
})

BENCHMARK("[2] ginseng     Destroying 10M entities", [](benchpress::context* ctx) {
    GinsengBenchmark::EntityManager db;
    
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<GinsengBenchmark::Entity> created_entities (_10M);

        for (size_t c = 0; c < _10M; c++) {
            auto entity = db.create_entity();
            created_entities.emplace_back(entity);
        }
        
        ctx->start_timer();
        for (auto entity : created_entities) {
            db.destroy_entity(entity);
        }
        ctx->stop_timer();
    }
})

BENCHMARK("[3] ginseng     Iterating over 10M entities, unpacking one component", [](benchpress::context* ctx) {
    GinsengBenchmark::EntityManager db;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = db.create_entity();
        db.create_component(entity, GinsengBenchmark::PositionComponent{});
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        db.visit([&](GinsengBenchmark::PositionComponent& position){
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(&position);
        });
    }
})

BENCHMARK("[4] ginseng     Iterating over 10M entities, unpacking two components", [](benchpress::context* ctx) {
    GinsengBenchmark::EntityManager db;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = db.create_entity();
        db.create_component(entity, GinsengBenchmark::PositionComponent{});
        db.create_component(entity, GinsengBenchmark::DirectionComponent{});
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        db.visit([&](GinsengBenchmark::PositionComponent& position, GinsengBenchmark::DirectionComponent& velocity){
            DISABLE_REDUNDANT_CODE_OPT();
            benchpress::escape(&position);
            benchpress::escape(&velocity);
        });
    }
})

BENCHMARK("ginseng     create destroy entity with components", [](benchpress::context* ctx) {
    GinsengBenchmark::EntityManager db;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = db.create_entity();

        db.create_component(entity, GinsengBenchmark::PositionComponent{});
        db.create_component(entity, GinsengBenchmark::DirectionComponent{});
        db.create_component(entity, GinsengBenchmark::ComflabulationComponent{});

        db.destroy_entity(entity);
    }
})

inline void init_entities(GinsengBenchmark::EntityManager& db, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
        auto entity = db.create_entity();

        db.create_component(entity, GinsengBenchmark::PositionComponent{});
        db.create_component(entity, GinsengBenchmark::DirectionComponent{});

        if (i % 2) {
            db.create_component(entity, GinsengBenchmark::ComflabulationComponent{});
        }
    }
}

inline void runEntitiesSystemsGinsengBenchmark(benchpress::context* ctx, size_t nentities) {
    GinsengBenchmark::Application app;
    auto& db = app.getEntityManager();

    init_entities(db, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(GinsengBenchmark::fakeDeltaTime);
    }
}



class BenchmarksGinseng {
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
                runEntitiesSystemsGinsengBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksGinseng(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksGinseng::ENTITIES = {
    10, 25, 50,
    100, 200, 400, 800,
    1600, 3200, 5000,
    10'000, 30'000,
    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000,
    10'000'000, 20'000'000
};

BenchmarksGinseng ginsengbenchmarks("ginseng");


} // namespace ginseng_benchmark
