#ifndef ECS_BENCHMARKS_OOPBENCHMARK_H_
#define ECS_BENCHMARKS_OOPBENCHMARK_H_

#include "ECSBenchmark.h"

#include "oop/systems/DataSystem.h"
#include "oop/systems/MoreComplexSystem.h"
#include "oop/systems/MovementSystem.h"
#include "oop/entities/EntityFactory.h"
#include "oop/OOPApplication.h"

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
                entities_factory.clear(app.getMOEntities());
                state.ResumeTiming();
                for (int i = 0; i < state.range(0); ++i) {
                    entities_factory.createMinimal(app.getMOEntities());
                }
                benchmark::DoNotOptimize(app.getMOEntities());
                benchmark::ClobberMemory();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(state.range(0));
            uninitApplication(app);
            entities_factory.clear(app.getMOEntities());
        }


        void BM_DestroyEntities(benchmark::State &state) {
            std::vector<entities::EntityFactory::EntityMO> entities;
            OOPApplication app;
            initApplicationWithEntities(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                state.PauseTiming();
                entities.clear();
                entities.reserve(static_cast<size_t>(state.range(0)));
                for (size_t i = 0; i < static_cast<size_t>(state.range(0)); i++) {
                    entities.push_back(entities_factory.createMinimal(app.getMOEntities()));
                }
                state.ResumeTiming();
                for (auto &entity: entities) {
                    entities_factory.destroy(app.getMOEntities(), entity);
                }
                benchmark::DoNotOptimize(entities);
                benchmark::DoNotOptimize(app.getMOEntities());
                benchmark::ClobberMemory();
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_factory.clear(app.getMOEntities());
        }

        void BM_UnpackOneComponent(benchmark::State &state) {
            std::vector<entities::EntityFactory::EntityMO> entities;
            OOPApplication app;
            initApplicationWithEntities(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                for (auto &entity: entities) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getMOEntities(), *entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities.clear();
            entities_factory.clear(app.getMOEntities());
        }

        void BM_UnpackTwoComponents(benchmark::State &state) {
            std::vector<entities::EntityFactory::EntityMO> entities;
            OOPApplication app;
            initApplicationWithEntities(app, static_cast<size_t>(state.range(0)), entities);
            for (auto _: state) {
                for (auto &entity: entities) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getMOEntities(), *entity));
                    benchmark::DoNotOptimize(entities_factory.getComponentTwo(app.getMOEntities(), *entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] = static_cast<double>(entities.size());
            afterBenchmark(app);
            uninitApplication(app);
            entities.clear();
            entities_factory.clear(app.getMOEntities());
        }

        void BM_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
            std::vector<entities::EntityFactory::EntityMDO> entities_mdo;
            std::vector<entities::EntityFactory::EntityMO> entities_mo;
            OOPApplication app;
            initApplicationWithEntitiesAndMixedComponents(app, static_cast<size_t>(state.range(0)), entities_mdo,
                                                          entities_mo);
            for (auto _: state) {
                for (auto &entity: entities_mo) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getMOEntities(), *entity));
                    benchmark::DoNotOptimize(entities_factory.getComponentTwo(app.getMOEntities(), *entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] =
                    static_cast<double>(entities_mdo.size()) + static_cast<double>(entities_mo.size());
            state.counters["entities_mo"] = static_cast<double>(entities_mdo.size());
            state.counters["entities_mdo"] = static_cast<double>(entities_mo.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities_mdo.clear();
            entities_mo.clear();
            entities_factory.clear(app.getMOEntities());
            entities_factory.clear(app.getMDOEntities());
        }

        void BM_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
            std::vector<entities::EntityFactory::EntityMDO> entities_mdo;
            std::vector<entities::EntityFactory::EntityMO> entities_mo;
            OOPApplication app(m_options.add_more_complex_system);
            initApplicationWithEntitiesAndMixedComponents(app, static_cast<size_t>(state.range(0)), entities_mdo,
                                                          entities_mo);
            for (auto _: state) {
                for (auto &entity: entities_mo) {
                    benchmark::DoNotOptimize(entities_factory.getComponentOne(app.getMOEntities(), *entity));
                    benchmark::DoNotOptimize(entities_factory.getComponentTwo(app.getMOEntities(), *entity));
                }
                for (auto &entity: entities_mdo) {
                    benchmark::DoNotOptimize(entities_factory.getOptionalComponentThree(app.getMDOEntities(), *entity));
                }
            }
            state.PauseTiming();
            state.counters["entities"] =
                    static_cast<double>(entities_mdo.size()) + static_cast<double>(entities_mo.size());
            state.counters["entities_mo"] = static_cast<double>(entities_mdo.size());
            state.counters["entities_mdo"] = static_cast<double>(entities_mo.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities_mdo.clear();
            entities_mo.clear();
            entities_factory.clear(app.getMOEntities());
            entities_factory.clear(app.getMDOEntities());
        }

        void BM_SystemsUpdate(benchmark::State &state) {
            std::vector<entities::EntityFactory::EntityMDO> entities_mdo;
            std::vector<entities::EntityFactory::EntityMO> entities_mo;
            OOPApplication app(m_options.add_more_complex_system);
            initApplicationWithEntitiesAndMixedComponents(app, static_cast<size_t>(state.range(0)), entities_mdo,
                                                          entities_mo);
            for (auto _: state) {
                app.update(this->fakeTimeDelta);
            }
            state.PauseTiming();
            state.counters["entities"] =
                    static_cast<double>(entities_mdo.size()) + static_cast<double>(entities_mo.size());
            state.counters["entities_mo"] = static_cast<double>(entities_mdo.size());
            state.counters["entities_mdo"] = static_cast<double>(entities_mo.size());
            this->afterBenchmark(app);
            this->uninitApplication(app);
            entities_mdo.clear();
            entities_mo.clear();
            entities_factory.clear(app.getMOEntities());
            entities_factory.clear(app.getMDOEntities());
        }

    protected:
        void initApplicationWithEntitiesAndMixedComponents(OOPApplication &app, size_t nentities) {
            for (size_t i = 0; i < nentities; i++) {
                if (i % 2 == 0) {
                    entities_factory.create(app.getMDOEntities());
                } else {
                    entities_factory.createMinimal(app.getMOEntities());
                }
            }
            app.init();
        }

        void initApplicationWithEntitiesAndMixedComponents(OOPApplication &app, size_t nentities,
                                                           std::vector<entities::EntityFactory::EntityMDO> &out_mdo,
                                                           std::vector<entities::EntityFactory::EntityMO> &out_mo) {
            out_mdo.clear();
            out_mo.clear();
            for (size_t i = 0; i < nentities; i++) {
                if (i % 2 == 0) {
                    out_mdo.push_back(entities_factory.create(app.getMDOEntities()));
                } else {
                    out_mo.push_back(entities_factory.createMinimal(app.getMOEntities()));
                }
            }
            app.init();
        }

        static void initApplication(OOPApplication &app) { app.init(); }

        void initApplicationWithEntities(OOPApplication app, size_t nentities) {
            for (size_t i = 0; i < nentities; i++) {
                entities_factory.createMinimal(app.getMOEntities());
            }
            app.init();
        }

        void initApplicationWithEntities(OOPApplication &app, size_t nentities,
                                         std::vector<entities::EntityFactory::EntityMO> &out) {
            out.clear();
            out.reserve(nentities);
            for (size_t i = 0; i < nentities; i++) {
                out.push_back(entities_factory.createMinimal(app.getMOEntities()));
            }
            app.init();
        }

        void initApplicationWithEntities(OOPApplication &app, size_t nentities,
                                         std::vector<entities::EntityFactory::EntityMDO> &out) {
            out.clear();
            out.reserve(nentities);
            for (size_t i = 0; i < nentities; i++) {
                out.push_back(entities_factory.create(app.getMDOEntities()));
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
        entities::EntityFactory entities_factory;

        void afterBenchmark(OOPApplication & /*app*/) {}
    };

}

#endif //ECS_BENCHMARKS_OOPBENCHMARK_H_
