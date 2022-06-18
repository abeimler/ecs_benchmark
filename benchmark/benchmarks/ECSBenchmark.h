#ifndef ECS_BENCHMARKS_ECSBENCHMARK_H_
#define ECS_BENCHMARKS_ECSBENCHMARK_H_

#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <optional>
#include <concepts>

#include <benchmark/benchmark.h>

#include "basic.h"
#include "BaseECSBenchmark.h"
#include "EntityBenchmark.h"

namespace ecs::benchmarks::base {

    template<StringLiteral Name, class Application, class EntityFactory, bool include_entity_benchmarks = false>
    class ECSBenchmark : protected BaseECSBenchmark<EntityFactory> {
    public:
        using EntityManager = typename EntityFactory::EntityManager;
        using Entity = typename EntityFactory::Entity;

        const float fakeTimeDelta{1.0F / 60.0F};

        ECSBenchmark() {
            benchmark::AddCustomContext("framework.name", m_name);
            benchmark::AddCustomContext("options.add_more_complex_system",
                                        m_options.add_more_complex_system ? "true" : "false");
            if (m_options.version.has_value()) {
                benchmark::AddCustomContext("framework.version", m_options.version.value());
            }
        }
        explicit ECSBenchmark(ESCBenchmarkOptions options) : m_options(std::move(options)) {
            benchmark::AddCustomContext("framework.name", m_name);
            benchmark::AddCustomContext("options.add_more_complex_system",
                                        m_options.add_more_complex_system ? "true" : "false");
            if (m_options.version.has_value()) {
                benchmark::AddCustomContext("framework.version", m_options.version.value());
            }
        }
        virtual ~ECSBenchmark() = default;
        ECSBenchmark(const ECSBenchmark &) = default;
        ECSBenchmark &operator=(const ECSBenchmark &) = default;
        ECSBenchmark(ECSBenchmark &&) noexcept = default;
        ECSBenchmark &operator=(ECSBenchmark &&) noexcept = default;

        [[nodiscard]] inline const char *name() const noexcept {
            return m_name;
        }

        [[nodiscard]] inline auto framework_version() const {
            return m_options.version;
        }


        void BM_SystemsUpdate(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            std::vector<Entity> entities;
            Application app(m_options.add_more_complex_system);
            const ComponentsCounter components_counter = initApplicationWithMixedComponents(app, nentities, entities);
            for (auto _: state) {
                app.update(fakeTimeDelta);
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
            afterBenchmark(app);
            uninitApplication(app);
        }

        void BM_SystemsUpdateMixedEntities(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            std::vector<Entity> entities;
            Application app(m_options.add_more_complex_system);
            const ComponentsCounter components_counter = initApplicationWithMixedComponents(app, nentities, entities);
            for (auto _: state) {
                app.update(fakeTimeDelta);
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
            afterBenchmark(app);
            uninitApplication(app);
        }






        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks
        void BM_CreateEmptyEntities(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            for (auto _: state) {
                state.PauseTiming();
                Application app(m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();

                state.ResumeTiming();
                for (size_t i = 0; i < nentities; ++i) {
                    state.PauseTiming();
                    this->m_entities_factory.createEmpty(registry);
                    state.ResumeTiming();
                }
                state.PauseTiming();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(nentities);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasBulkFeature<tEntityFactory>
        void BM_CreateEmptyEntitiesInBulk(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            for (auto _: state) {
                state.PauseTiming();
                Application app(m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                entities.resize(nentities);

                state.ResumeTiming();
                this->m_entities_factory.createEmptyBulk(registry, entities);
                state.PauseTiming();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(nentities);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks
        void BM_CreateEntities(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            for (auto _: state) {
                state.PauseTiming();
                Application app(m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();

                state.ResumeTiming();
                for (size_t i = 0; i < nentities; ++i) {
                    state.PauseTiming();
                    this->m_entities_factory.createMinimal(registry);
                    state.ResumeTiming();
                }
                state.PauseTiming();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(nentities);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasBulkFeatureWithOutput<tEntityFactory>
        void BM_CreateEntitiesInBulk(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            for (auto _: state) {
                state.PauseTiming();
                Application app(m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                entities.resize(nentities);

                state.ResumeTiming();
                this->m_entities_factory.createMinimalBulk(registry, entities);
                state.PauseTiming();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(nentities);
        }


        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasDestroyFeature<tEntityFactory>
        void BM_DestroyEntities(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            for (auto _: state) {
                state.PauseTiming();
                Application app(m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                entities.resize(nentities);
                if constexpr (HasBulkFeature<EntityFactory>) {
                    this->m_entities_factory.createMinimalBulk(registry, entities);
                } else {
                    for (auto& entity : entities) {
                        entity = this->m_entities_factory.createMinimal(registry);
                    }
                }

                state.ResumeTiming();
                for (auto &entity: entities) {
                    state.PauseTiming();
                    this->m_entities_factory.destroy(registry, entity);
                    state.ResumeTiming();
                }
                state.PauseTiming();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(nentities);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasBulkDestroyFeature<tEntityFactory>
        void BM_DestroyEntitiesInBulk(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            for (auto _: state) {
                state.PauseTiming();
                Application app(m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                entities.resize(nentities);
                this->m_entities_factory.createMinimalBulk(registry, entities);

                state.ResumeTiming();
                this->m_entities_factory.destroyBulk(registry, entities);
                state.PauseTiming();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(nentities);
        }


        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
        void BM_UnpackOneComponent(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            Application app(m_options.add_more_complex_system);
            EntityManager& registry = app.getEntities();
            std::vector<Entity> entities;
            const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities,
                                                                                                   entities);

            for (auto _: state) {
                state.PauseTiming();
                for (auto &entity: entities) {
                    state.ResumeTiming();
                    benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
                    state.PauseTiming();
                }
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
        void BM_UnpackOneConstComponent(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            Application app(m_options.add_more_complex_system);
            EntityManager& registry = app.getEntities();
            std::vector<Entity> entities;
            const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities,
                                                                                                   entities);
            for (auto _: state) {
                state.PauseTiming();
                for (auto &entity: entities) {
                    state.ResumeTiming();
                    benchmark::DoNotOptimize(this->m_entities_factory.getComponentOneConst(registry, entity));
                    state.PauseTiming();
                }
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
        void BM_UnpackTwoComponents(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            Application app(m_options.add_more_complex_system);
            EntityManager& registry = app.getEntities();
            std::vector<Entity> entities;
            const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities,
                                                                                                   entities);
            for (auto _: state) {
                state.PauseTiming();
                for (auto &entity: entities) {
                    state.ResumeTiming();
                    benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
                    benchmark::DoNotOptimize(this->m_entities_factory.getComponentTwoConst(registry, entity));
                    state.PauseTiming();
                }
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks && HasGetComponentsFeature<tEntityFactory>
        void BM_UnpackThreeComponents(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            Application app(m_options.add_more_complex_system);
            EntityManager& registry = app.getEntities();
            std::vector<Entity> entities;
            const ComponentsCounter components_counter = this->createEntitiesWithHalfComponents(registry, nentities,
                                                                                                entities);
            for (auto _: state) {
                state.PauseTiming();
                for (auto &entity: entities) {
                    state.ResumeTiming();
                    benchmark::DoNotOptimize(this->m_entities_factory.getComponentOne(registry, entity));
                    benchmark::DoNotOptimize(this->m_entities_factory.getComponentTwoConst(registry, entity));
                    benchmark::DoNotOptimize(this->m_entities_factory.getOptionalComponentThree(registry, entity));
                    state.PauseTiming();
                }
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
        }

        template<class tEntityFactory = EntityFactory>
        requires include_entity_benchmarks
        void BM_RemoveAddComponent(benchmark::State &state) {
            const auto nentities = static_cast<size_t>(state.range(0));
            Application app(m_options.add_more_complex_system);
            EntityManager& registry = app.getEntities();
            std::vector<Entity> entities;
            const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities,
                                                                                                   entities);
            for (auto _: state) {
                state.PauseTiming();
                for (auto &entity: entities) {
                    state.ResumeTiming();
                    this->m_entities_factory.removeComponentOne(registry, entity);
                    this->m_entities_factory.addComponentOne(registry, entity);
                    state.PauseTiming();
                }
            }
            state.PauseTiming();
            this->setCounters(state, entities, components_counter);
        }

    protected:
        ComponentsCounter initApplicationWithHalfComponents(Application &app, size_t nentities) {
            const auto ret = createEntitiesWithHalfComponents(app.getEntities(), nentities);
            app.init();
            return ret;
        }

        ComponentsCounter
        initApplicationWithMixedComponents(Application &app, size_t nentities, std::vector<Entity> &out) {
            const auto ret = this->createEntitiesWithMixedComponents(app.getEntities(), nentities, out);
            app.init();
            return ret;
        }

        ComponentsCounter initApplicationWithMinimalComponents(Application &app, size_t nentities, std::vector<Entity> &out) {
            const auto ret = this->createEntitiesWithMixedComponents(app.getEntities(), nentities, out);
            app.init();
            return ret;
        }

        ComponentsCounter initApplicationWithSingleComponent(Application &app, size_t nentities, std::vector<Entity> &out) {
            const auto ret = this->createEntitiesWithSingleComponent(app.getEntities(), nentities, out);
            app.init();
            return ret;
        }

        void uninitApplication(Application &app) {
            app.uninit();
        }

        virtual void afterBenchmark(Application & /*app*/) {}

        inline static constexpr auto m_name{Name.value};
        const ESCBenchmarkOptions m_options;
        EntityFactory m_entities_factory;
    };
}

#define ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite) \
    static void BM_SystemsUpdate(benchmark::State &state) {\
        benchmark_suite.BM_SystemsUpdate(state);\
    }\
    BENCHMARK(BM_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);\
    static void BM_SystemsUpdateMixedEntities(benchmark::State &state) {\
        benchmark_suite.BM_SystemsUpdateMixedEntities(state);\
    }\
    BENCHMARK(BM_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


#define ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite) \
    static void BM_ComplexSystemsUpdate(benchmark::State &state) {\
        benchmark_suite.BM_SystemsUpdate(state);\
    }\
    BENCHMARK(BM_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);\
    static void BM_ComplexSystemsUpdateMixedEntities(benchmark::State &state) {\
        benchmark_suite.BM_SystemsUpdateMixedEntities(state);\
    }\
    BENCHMARK(BM_ComplexSystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


#endif //ECS_BENCHMARKS_ECSBENCHMARK_H_
