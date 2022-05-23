#ifndef ECS_BENCHMARKS_ECSBENCHMARK_H_
#define ECS_BENCHMARKS_ECSBENCHMARK_H_

#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <optional>

#include <fmt/core.h>

#include <benchmark/benchmark.h>

namespace ecs::benchmarks::base {

    template<size_t N>
    struct StringLiteral {
        /*implicit*/ constexpr StringLiteral(const char (&str)[N]) {
            std::copy_n(str, N, value);
            value[N] = '\0';
        }

        char value[N+1];
    };

    struct ESCBenchmarkOptions {
        bool add_more_complex_system{false};
        std::optional<std::string> version;
    };

    template<StringLiteral Name, class Application, class EntityFactory>
    class ESCBenchmark {
    public:
        using Entity = typename EntityFactory::Entity;

        const float fakeTimeDelta{1.0F / 60.0F};

        constexpr ESCBenchmark() {
            benchmark::AddCustomContext("framework.name", m_name);
            benchmark::AddCustomContext("options.add_more_complex_system",  m_options.add_more_complex_system ? "true" : "false");
            if (m_options.version.has_value()) {
                benchmark::AddCustomContext("framework.version", m_options.version.value());
            }
        }
        explicit ESCBenchmark(ESCBenchmarkOptions options) : m_options(std::move(options)) {
            benchmark::AddCustomContext("framework.name", m_name);
            benchmark::AddCustomContext("options.add_more_complex_system",  m_options.add_more_complex_system ? "true" : "false");
            if (m_options.version.has_value()) {
                benchmark::AddCustomContext("framework.version", m_options.version.value());
            }
        }

        virtual ~ESCBenchmark() = default;
        ESCBenchmark(const ESCBenchmark &) = default;
        ESCBenchmark &operator=(const ESCBenchmark &) = default;
        ESCBenchmark(ESCBenchmark &&) = default;
        ESCBenchmark &operator=(ESCBenchmark &&) = default;

        inline const char* name() const noexcept {
            return m_name;
        }
        inline auto framework_version() const {
            return m_options.version;
        }

        void BM_CreateEntities(benchmark::State& state) {
            Application app;
            this->initApplication(app);
            for (auto _ : state) {
                state.PauseTiming();
                entities_factory.clear(app.getEntities());
                state.ResumeTiming();
                for (int i = 0; i < state.range(0); ++i) {
                    entities_factory.createMinimal(app.getEntities());
                }
                benchmark::DoNotOptimize(app.getEntities());
                benchmark::ClobberMemory();
            }
            state.PauseTiming();
            state.counters["entities"] = state.range(0);
            this->uninitApplication(app);
            entities_factory.clear(app.getEntities());
        }


        void BM_DestroyEntities(benchmark::State& state) {
            std::vector<Entity> entities;
            Application app;
            this->initApplicationWithEntities(app, state.range(0), entities);
            for (auto _ : state) {
                state.PauseTiming();
                entities.clear();
                entities.reserve(state.range(0));
                for (size_t i = 0; i < state.range(0); i++) {
                    entities.push_back(entities_factory.createMinimal(app.getEntities()));
                }
                state.ResumeTiming();
                for (auto& entity : entities) {
                    entities_factory.destory(app.getEntities(), entity);
                }
                benchmark::DoNotOptimize(entities);
                benchmark::DoNotOptimize(app.getEntities());
                benchmark::ClobberMemory();
            }
            state.PauseTiming();
            state.counters["entities"] = entities.size();
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_factory.clear(app.getEntities());
        }

        void BM_UnpackOneComponent(benchmark::State& state) {
            std::vector<Entity> entities;
            Application app;
            this->initApplicationWithEntities(app, state.range(0), entities);
            for (auto _ : state) {
                for (auto& entity : entities) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getEntities(), entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = entities.size();
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_factory.clear(app.getEntities());
        }

        void BM_UnpackTwoComponents(benchmark::State& state) {
            std::vector<Entity> entities;
            Application app;
            this->initApplicationWithEntities(app, state.range(0), entities);
            for (auto _ : state) {
                for (auto& entity : entities) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getEntities(), entity));
                    benchmark::DoNotOptimize(entities_factory.getComponentTwo(app.getEntities(), entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = entities.size();
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_factory.clear(app.getEntities());
        }

        void BM_UnpackTwoComponentsFromMixedEntities(benchmark::State& state) {
            std::vector<Entity> entities;
            std::vector<Entity> entities_minimal;
            Application app;
            this->initApplicationWithEntitiesAndMixedComponents(app, state.range(0), entities, entities_minimal);
            for (auto _ : state) {
                for (auto& entity : entities) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getEntities(), entity));
                    benchmark::DoNotOptimize(entities_factory.getComponentTwo(app.getEntities(), entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = entities.size();
            state.counters["entities_minimal"] = entities_minimal.size();
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_minimal.clear();
            entities_factory.clear(app.getEntities());
        }

        void BM_UnpackThreeComponentsFromMixedEntities(benchmark::State& state) {
            std::vector<Entity> entities;
            std::vector<Entity> entities_minimal;
            Application app (m_options.add_more_complex_system);
            this->initApplicationWithEntitiesAndMixedComponents(app, state.range(0), entities, entities_minimal);
            for (auto _ : state) {
                for (auto& entity : entities) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getEntities(), entity));
                    benchmark::DoNotOptimize(entities_factory.getComponentTwo(app.getEntities(), entity));
                    benchmark::DoNotOptimize(entities_factory.getOptionalComponentThree(app.getEntities(), entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = entities.size();
            state.counters["entities_minimal"] = entities_minimal.size();
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_minimal.clear();
            entities_factory.clear(app.getEntities());
        }

        void BM_SystemsUpdate(benchmark::State& state) {
            std::vector<Entity> entities;
            std::vector<Entity> entities_minimal;
            Application app (m_options.add_more_complex_system);
            this->initApplicationWithEntitiesAndMixedComponents(app, state.range(0), entities, entities_minimal);
            for (auto _ : state) {
                app.update(this->fakeTimeDelta);
            }
            state.PauseTiming();
            state.counters["entities"] = entities.size();
            state.counters["entities_minimal"] = entities_minimal.size();
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_minimal.clear();
            entities_factory.clear(app.getEntities());
        }

    protected:
        void initApplicationWithEntitiesAndMixedComponents(Application& app, size_t nentities) {
            for (size_t i = 0; i < nentities; i++) {
                if (i % 2 == 0) {
                    entities_factory.create(app.getEntities());
                } else {
                    entities_factory.createMinimal(app.getEntities());
                }
            }
            app.init();
        }
        void initApplicationWithEntitiesAndMixedComponents(Application& app, size_t nentities, std::vector<Entity>& out_all, std::vector<Entity>& out_minimal) {
            out_all.clear();
            out_minimal.clear();
            for (size_t i = 0; i < nentities; i++) {
                if (i % 2 == 0) {
                    out_all.push_back(entities_factory.create(app.getEntities()));
                } else {
                    const auto entity = entities_factory.createMinimal(app.getEntities());
                    out_minimal.push_back(entity);
                    out_all.push_back(entity);
                }
            }
            app.init();
        }

        void initApplication(Application& app) {
            app.init();
        }

        void initApplicationWithEntities(Application app, size_t nentities) {
            for (size_t i = 0; i < nentities; i++) {
                entities_factory.createMinimal(app.entities());
            }
            app.init();
        }

        void initApplicationWithEntities(Application& app, size_t nentities, std::vector<Entity>& out) {
            out.clear();
            out.reserve(nentities);
            for (size_t i = 0; i < nentities; i++) {
                out.push_back(entities_factory.createMinimal(app.getEntities()));
            }
            app.init();
        }

        void uninitApplication(Application& app) {
            this->afterBenchmark(app);
            app.uninit();
        }

        inline static constexpr auto m_name{Name.value};
        const ESCBenchmarkOptions m_options;
        std::vector<std::string> m_benchmark_names;
        EntityFactory entities_factory;

        virtual void afterBenchmark(Application &) {}
    };
}

#endif //ECS_BENCHMARKS_ECSBENCHMARK_H_
