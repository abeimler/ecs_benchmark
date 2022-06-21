#ifndef ECS_BENCHMARKS_MOREECSBENCHMARK_H_
#define ECS_BENCHMARKS_MOREECSBENCHMARK_H_

#include<concepts>

#include <benchmark/benchmark.h>

#include "ECSBenchmark.h"

namespace ecs::benchmarks::base {

    template<typename Iterable, typename Func>
    concept HasEach = requires (Iterable it, Func func) {
        it.each(func);
    };
    template<typename Iterable, typename Func>
    concept HasForEach = requires (Iterable it, Func func) {
        it.for_each(func);
    };
    template<typename Iterable, typename Func>
    concept HasVisit = requires (Iterable it, Func func) {
        it.visit(func);
    };

    template<StringLiteral Name, class Application, class EntityFactory, bool include_entity_benchmarks = false>
    class ExtendedECSBenchmark : public ECSBenchmark<Name, Application, EntityFactory, include_entity_benchmarks> {
    private:
        inline static constexpr auto default_initializable_entity_manager = std::default_initializable<typename EntityFactory::EntityManager>;

    public:
        using EntityManager = typename EntityFactory::EntityManager;
        using Entity = typename EntityFactory::Entity;

        ExtendedECSBenchmark() = default;
        explicit ExtendedECSBenchmark(ESCBenchmarkOptions options) : ECSBenchmark<Name, Application, EntityFactory>(std::move(options)) {}
        virtual ~ExtendedECSBenchmark() = default;
        ExtendedECSBenchmark(const ExtendedECSBenchmark &) = default;
        ExtendedECSBenchmark &operator=(const ExtendedECSBenchmark &) = default;
        ExtendedECSBenchmark(ExtendedECSBenchmark &&) noexcept = default;
        ExtendedECSBenchmark &operator=(ExtendedECSBenchmark &&) noexcept = default;

    protected:
        template<typename GetView, typename Func>
        void BM_IterateSingleComponentWithPreCreatedView(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry,
                                                                                                     nentities,
                                                                                                     entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename Comp, typename GetView, typename Func>
        void BM_IterateSingleComponentWithPreCreatedView(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry,
                                                                                                     nentities,
                                                                                                     entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each<Comp>(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each<Comp>(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView>
        void BM_IterateSingleComponentWithPreCreatedView(benchmark::State &state, GetView view) {
            BM_IterateSingleComponentWithPreCreatedView(state, view, [](auto &...comp) {
                dummy_each(comp...);
            });
        }

        template<typename GetView, typename Func>
        void BM_IterateSingleComponent(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry,
                                                                                                     nentities,
                                                                                                     entities);
                for (auto _: state) {
                    generic_each(get_view(registry), func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename Func>
        void BM_IterateSingleComponentCustom(benchmark::State &state, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry,
                                                                                                     nentities,
                                                                                                     entities);
                for (auto _: state) {
                    func(registry);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry, nentities, entities);
                for (auto _: state) {
                    func(registry);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename Comp, typename GetView, typename Func>
        void BM_IterateSingleComponent(benchmark::State &state, GetView get_view, Func func) {
            BM_IterateSingleComponentCustom(state, [&](auto& registry){
                generic_each_comps<Comp>(get_view(registry), func);
            });
        }
        template<typename GetView>
        void BM_IterateSingleComponent(benchmark::State &state, GetView view) {
            BM_IterateSingleComponent(state, view, [](auto &...comp) {
                dummy_each(comp...);
            });
        }

        template<typename GetView, typename Func>
        void BM_IterateTwoComponentsWithPreCreatedView(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry,
                                                                                                       nentities,
                                                                                                       entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView>
        void BM_IterateTwoComponentsWithPreCreatedView(benchmark::State &state, GetView view) {
            BM_IterateTwoComponentsWithPreCreatedView(state, view, [](auto &...comp) {
                dummy_each(comp...);
            });
        }
        template<typename Func>
        void BM_IterateTwoComponentsCustom(benchmark::State &state, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry,
                                                                                                       nentities,
                                                                                                       entities);
                for (auto _: state) {
                    func(registry);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities, entities);
                for (auto _: state) {
                    func(registry);
                }
                state.PauseTiming();
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView, typename Func>
        void BM_IterateTwoComponents(benchmark::State &state, GetView get_view, Func func) {
            BM_IterateTwoComponentsCustom(state, [&](auto& registry){
                generic_each(get_view(registry), func);
            });
        }
        template<typename GetView>
        void BM_IterateTwoComponents(benchmark::State &state, GetView view) {
            BM_IterateTwoComponents(state, view, [](auto &...comp) {
                dummy_each(comp...);
            });
        }

        template<typename GetView, typename Func>
        void BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMixedComponents(registry,
                                                                                                     nentities,
                                                                                                     entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMixedComponents(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    generic_each(view, func);
                }
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView>
        void BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(benchmark::State &state, GetView view) {
            BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, view, [](auto &...comp) {
                dummy_each(comp...);
            });
        }
        template<typename Func>
        void BM_IterateThreeComponentsWithMixedEntitiesCustom(benchmark::State &state, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMixedComponents(registry,
                                                                                                     nentities,
                                                                                                     entities);
                for (auto _: state) {
                    func(registry);
                }
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMixedComponents(registry, nentities, entities);
                for (auto _: state) {
                    func(registry);
                }
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView, typename Func>
        void BM_IterateThreeComponentsWithMixedEntities(benchmark::State &state, GetView get_view, Func func) {
            BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [&](auto& registry) {
                generic_each(get_view(registry), func);
            });
        }
        template<typename GetView>
        void BM_IterateThreeComponentsWithMixedEntities(benchmark::State &state, GetView view) {
            BM_IterateThreeComponentsWithMixedEntities(state, view, [](auto &...comp) {
                dummy_each(comp...);
            });
        }



        template<typename GetView, typename Func>
        void BM_IterateSingleComponentWithPreCreatedViewCustom(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry,
                                                                                                     nentities,
                                                                                                     entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    func(registry, view);
                }
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithSingleComponent(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    func(registry, view);
                }
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView, typename Func>
        void BM_IterateTwoComponentsWithPreCreatedViewCustom(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry,
                                                                                                       nentities,
                                                                                                       entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    func(registry, view);
                }
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMinimalComponents(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    func(registry, view);
                }
                this->setCounters(state, entities, components_counter);
            }
        }
        template<typename GetView, typename Func>
        void BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedViewCustom(benchmark::State &state, GetView get_view, Func func) {
            const auto nentities = static_cast<size_t>(state.range(0));
            if constexpr (default_initializable_entity_manager) {
                EntityManager registry;
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMixedComponents(registry,
                                                                                                     nentities,
                                                                                                     entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    func(registry, view);
                }
                this->setCounters(state, entities, components_counter);
            } else {
                Application app(this->m_options.add_more_complex_system);
                EntityManager& registry = app.getEntities();
                std::vector<Entity> entities;
                const ComponentsCounter components_counter = this->createEntitiesWithMixedComponents(registry, nentities, entities);
                auto view = get_view(registry);
                for (auto _: state) {
                    func(registry, view);
                }
                this->setCounters(state, entities, components_counter);
            }
        }

    public:

        template<class Comp, class... Args>
        inline static void dummy_each(Comp& comp, Args&&... /*args*/) {
            ((comp.x = {}));
        }

        template<typename Iterable, typename Func>
        requires HasEach<Iterable, Func>
        inline static void generic_each(Iterable &&iterable, Func func) {
            std::forward<Iterable>(iterable).each(func);
        }
        template<typename Iterable, typename Func>
        requires HasForEach<Iterable, Func>
        inline static void generic(Iterable &&iterable, Func func) {
            std::forward<Iterable>(iterable).for_each(func);
        }
        template<typename Iterable, typename Func>
        requires HasVisit<Iterable, Func>
        inline static void generic(Iterable &&iterable, Func func) {
            std::forward<Iterable>(iterable).visit(func);
        }
    };
}

#define ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite) \
    static void BM_IterateSingleComponent(benchmark::State &state) {\
        benchmark_suite.BM_IterateSingleComponent(state);\
    }\
    BENCHMARK(BM_IterateSingleComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);\
    static void BM_IterateTwoComponents(benchmark::State &state) {\
        benchmark_suite.BM_IterateTwoComponents(state);\
    }\
    BENCHMARK(BM_IterateTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);\
    static void BM_IterateThreeComponentsWithMixedEntities(benchmark::State &state) {\
        benchmark_suite.BM_IterateThreeComponentsWithMixedEntities(state);\
    }\
    BENCHMARK(BM_IterateThreeComponentsWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

#endif //ECS_BENCHMARKS_MOREECSBENCHMARK_H_
