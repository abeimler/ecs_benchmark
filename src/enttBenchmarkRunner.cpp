#include <string>
#include <vector>
#include <thread>
#include <memory>
#include <sstream>

#include "benchpress/benchpress.hpp"

#include "registry.hpp"

#include "EnttBenchmark.h"

namespace entt_benchmark {

constexpr size_t _10M = 10'000'000L;


BENCHMARK("entt     Creating 10M entities", [](benchpress::context* ctx) {
    EnttBenchmark::EntityManager registry;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<EnttBenchmark::Entity> created_entities (_10M);

        ctx->start_timer();
        for (size_t c = 0; c < _10M; c++) {
            auto entity = registry.create();
            created_entities.emplace_back(entity);
        }
        ctx->stop_timer();

        // cleanup memory to avoid full memory 
        for (auto entity : created_entities) {
            registry.destroy(entity);
        }
    }
})

BENCHMARK("entt     Destroying 10M entities", [](benchpress::context* ctx) {
    EnttBenchmark::EntityManager registry;
    
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        std::vector<EnttBenchmark::Entity> created_entities (_10M);

        for (size_t c = 0; c < _10M; c++) {
            auto entity = registry.create();
            created_entities.emplace_back(entity);
        }
        
        ctx->start_timer();
        for (auto entity : created_entities) {
            registry.destroy(entity);
        }
        ctx->stop_timer();
    }
})

BENCHMARK("entt     Iterating over 10M entities, unpacking one component", [](benchpress::context* ctx) {
    EnttBenchmark::EntityManager registry;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttBenchmark::PositionComponent>(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for(auto entity : registry.view<EnttBenchmark::PositionComponent>()) {
            DISABLE_REDUNDANT_CODE_OPT();
            auto& position = registry.get<EnttBenchmark::PositionComponent>(entity);

            benchpress::escape(&position);
        }
    }
})

BENCHMARK("entt     Iterating over 10M entities, unpacking two components", [](benchpress::context* ctx) {
    EnttBenchmark::EntityManager registry;

    for (size_t c = 0; c < _10M; c++) {
        auto entity = registry.create();
        registry.assign<EnttBenchmark::PositionComponent>(entity);
        registry.assign<EnttBenchmark::DirectionComponent>(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        for(auto entity : registry.view<EnttBenchmark::PositionComponent, EnttBenchmark::DirectionComponent>()) {
            DISABLE_REDUNDANT_CODE_OPT();
            auto& position = registry.get<EnttBenchmark::PositionComponent>(entity);
            auto& velocity = registry.get<EnttBenchmark::DirectionComponent>(entity);

            benchpress::escape(&position);
            benchpress::escape(&velocity);
        }
    }
})














BENCHMARK("entt     create destroy entity with components", [](benchpress::context* ctx) {
    EnttBenchmark::EntityManager registry;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = registry.create();

        registry.assign<EnttBenchmark::PositionComponent>(entity);
        registry.assign<EnttBenchmark::DirectionComponent>(entity);
        registry.assign<EnttBenchmark::ComflabulationComponent>(entity);

        registry.destroy(entity);
    }
})



inline void init_entities(EnttBenchmark::EntityManager& registry, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
        auto entity = registry.create();

        registry.assign<EnttBenchmark::PositionComponent>(entity);
        registry.assign<EnttBenchmark::DirectionComponent>(entity);


        if (i % 2) {
            registry.assign<EnttBenchmark::ComflabulationComponent>(entity);
        }
    }
}

inline void runEntitiesSystemsEnttBenchmark(benchpress::context* ctx, size_t nentities) {
    EnttBenchmark::Application app;
    auto& registry = app.getEntityManager();

    init_entities(registry, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EnttBenchmark::fakeDeltaTime);
    }
}



class BenchmarksEntt {
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
                runEntitiesSystemsEnttBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEntt(std::string name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEntt::ENTITIES = {
    10, 25, 50,
    100, 200, 400, 800,
    1600, 3200, 5000,
    10'000, 30'000,
    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000,
    10'000'000
};

BenchmarksEntt enttbenchmarks("entt");


} // namespace entt_benchmark
