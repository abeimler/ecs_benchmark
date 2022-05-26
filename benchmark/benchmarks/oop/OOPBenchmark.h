#ifndef ECS_BENCHMARKS_OOPBENCHMARK_H_
#define ECS_BENCHMARKS_OOPBENCHMARK_H_

#include "ECSBenchmark.h"

#include "oop/entities/EntityFactory.h"
#include "oop/OOPApplication.h"
#include "oop/entities/MovableDataObject.h"
#include "oop/entities/ComplexMovableDataObject.h"

namespace ecs::benchmarks::oop {

    class OOPBenchmark {
    public:
        const float fakeTimeDelta{1.0F / 60.0F};

        OOPBenchmark() {
            benchmark::AddCustomContext("framework.name", m_name);
            benchmark::AddCustomContext("options.add_more_complex_system",
                                        m_options.add_more_complex_system ? "true" : "false");
            if (m_options.version.has_value()) {
                benchmark::AddCustomContext("framework.version", m_options.version.value());
            }
        }

        explicit OOPBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : m_options(std::move(options)) {
            benchmark::AddCustomContext("framework.name", m_name);
            benchmark::AddCustomContext("options.add_more_complex_system",
                                        m_options.add_more_complex_system ? "true" : "false");
            if (m_options.version.has_value()) {
                benchmark::AddCustomContext("framework.version", m_options.version.value());
            }
        }

        ~OOPBenchmark() = default;

        OOPBenchmark(const OOPBenchmark &) = default;

        OOPBenchmark &operator=(const OOPBenchmark &) = default;

        OOPBenchmark(OOPBenchmark &&) = default;

        OOPBenchmark &operator=(OOPBenchmark &&) = default;

        [[nodiscard]] static inline const char *name() noexcept { return m_name; }

        [[nodiscard]] inline auto framework_version() const { return m_options.version; }

        void BM_CreateEntities(benchmark::State &state) {
            OOPApplication app;
            initApplication(app);
            for (auto _: state) {
                state.PauseTiming();
                entity_factory.clear(app.getEntities());
                state.ResumeTiming();
                for (int i = 0; i < state.range(0); ++i) {
                    entity_factory.createMinimal(app.getEntities());
                }
                benchmark::DoNotOptimize(app.getEntities());
                benchmark::ClobberMemory();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(state.range(0));
            uninitApplication(app);
            entity_factory.clear(app.getEntities());
        }


        void BM_DestroyEntities(benchmark::State &state) {
            std::vector<entities::EntityFactory::Entity> entities;
            OOPApplication app;
            initApplicationWithEntities(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                state.PauseTiming();
                entities.clear();
                entities.reserve(static_cast<size_t>(state.range(0)));
                for (size_t i = 0; i < static_cast<size_t>(state.range(0)); i++) {
                    entities.push_back(entity_factory.createMinimal(app.getEntities()));
                }
                state.ResumeTiming();
                for (auto &entity: entities) {
                    entity_factory.destroy(app.getEntities(), entity);
                }
                benchmark::DoNotOptimize(entities);
                benchmark::DoNotOptimize(app.getEntities());
                benchmark::ClobberMemory();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entity_factory.clear(app.getEntities());
        }

        void BM_UnpackOneComponent(benchmark::State &state) {
            std::vector<entities::EntityFactory::Entity> entities;
            OOPApplication app;
            initApplicationWithEntities(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                for (auto &entity: entities) {
                    benchmark::DoNotOptimize(entity_factory.getComponentOne(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entity_factory.clear(app.getEntities());
        }

        void BM_UnpackTwoComponents(benchmark::State &state) {
            std::vector<entities::EntityFactory::Entity> entities;
            OOPApplication app;
            initApplicationWithEntities(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                for (auto &entity: entities) {
                    benchmark::DoNotOptimize(entity_factory.getComponentOne(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                    benchmark::DoNotOptimize(entity_factory.getComponentTwo(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            afterBenchmark(app);
            uninitApplication(app);
            entities.clear();
            entity_factory.clear(app.getEntities());
        }

        void BM_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
            std::vector<entities::EntityFactory::Entity> entities;
            OOPApplication app;
            initApplicationWithEntitiesAndMixedComponents(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                for (auto &entity: entities) {
                    benchmark::DoNotOptimize(entity_factory.getComponentOne(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                    benchmark::DoNotOptimize(entity_factory.getComponentTwo(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entity_factory.clear(app.getEntities());
        }

        void BM_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
            std::vector<entities::EntityFactory::Entity> entities;
            OOPApplication app(m_options.add_more_complex_system);
            initApplicationWithEntitiesAndMixedComponents(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                for (auto &entity: entities) {
                    benchmark::DoNotOptimize(entity_factory.getComponentOne(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                    benchmark::DoNotOptimize(entity_factory.getComponentTwo(app.getEntities(), *dynamic_cast<entities::MovableObject*>(entity)));
                    if (dynamic_cast<entities::ComplexMovableDataObject*>(entity) != nullptr) {
                        benchmark::DoNotOptimize(entity_factory.getOptionalComponentThree(app.getEntities(), *dynamic_cast<entities::ComplexMovableDataObject*>(entity)));
                    }
                }
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entity_factory.clear(app.getEntities());
        }

        void BM_SystemsUpdate(benchmark::State &state) {
            std::vector<entities::EntityFactory::Entity> entities;
            OOPApplication app(m_options.add_more_complex_system);
            initApplicationWithEntitiesAndMixedComponents(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                app.update(this->fakeTimeDelta);
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entity_factory.clear(app.getEntities());
        }

    protected:
        void initApplicationWithEntitiesAndMixedComponents(OOPApplication &app, size_t nentities) {
            for (size_t i = 0; i < nentities; i++) {
                if (i % 2 == 0) {
                    entity_factory.create(app.getEntities());
                } else {
                    entity_factory.createMinimal(app.getEntities());
                }
            }
            app.init();
        }

        void initApplicationWithEntitiesAndMixedComponents(OOPApplication &app, size_t nentities,
                                                           std::vector<entities::EntityFactory::Entity> &out) {
            out.clear();
            for (size_t i = 0; i < nentities; i++) {
                if (i % 2 == 0) {
                    out.push_back(entity_factory.create(app.getEntities()));
                } else {
                    out.push_back(entity_factory.createMinimal(app.getEntities()));
                }
            }
            app.init();
        }

        static void initApplication(OOPApplication &app) { app.init(); }

        void initApplicationWithEntities(OOPApplication app, size_t nentities) {
            for (size_t i = 0; i < nentities; i++) {
                entity_factory.createMinimal(app.getEntities());
            }
            app.init();
        }

        void initApplicationWithEntities(OOPApplication &app, size_t nentities,
                                         std::vector<entities::EntityFactory::Entity> &out) {
            out.clear();
            out.reserve(nentities);
            for (size_t i = 0; i < nentities; i++) {
                out.push_back(entity_factory.createMinimal(app.getEntities()));
            }
            app.init();
        }


        void uninitApplication(OOPApplication &app) {
            afterBenchmark(app);
            app.uninit();
        }

        inline static constexpr auto m_name = "oop";
        const ecs::benchmarks::base::ESCBenchmarkOptions m_options;
        std::vector<std::string> m_benchmark_names;
        entities::EntityFactory entity_factory;

        void afterBenchmark(OOPApplication & /*app*/) {}
    };

}

#endif //ECS_BENCHMARKS_OOPBENCHMARK_H_
