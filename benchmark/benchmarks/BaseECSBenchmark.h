#ifndef ECS_BENCHMARKS_BASEECSBENCHMARK_H_
#define ECS_BENCHMARKS_BASEECSBENCHMARK_H_

#include "basic.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace ecs::benchmarks::base {

template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasAddComponentsFeatures = requires(EntityFactory entity_factory, EntityManager entity_manager, Entity entity) {
  entity_factory.addComponentOne(entity_manager, entity);
  entity_factory.addComponentTwo(entity_manager, entity);
  entity_factory.addComponentThree(entity_manager, entity);
};
template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasRemoveComponentsFeatures = requires(EntityFactory entity_factory, EntityManager entity_manager,
                                               Entity entity) {
  entity_factory.removeComponentOne(entity_manager, entity);
  entity_factory.removeComponentTwo(entity_manager, entity);
  entity_factory.removeComponentThree(entity_manager, entity);
};
template <class EntityFactory, class EntityManager = typename EntityFactory::EntityManager,
          class Entity = typename EntityFactory::Entity>
concept HasComponentsFeatures = HasAddComponentsFeatures<EntityFactory, EntityManager, Entity> &&
    HasRemoveComponentsFeatures<EntityFactory, EntityManager, Entity>;


template <class EntityFactory>
class BaseECSBenchmark {
public:
  using EntityManager = typename EntityFactory::EntityManager;
  using Entity = typename EntityFactory::Entity;

protected:
  BaseECSBenchmark() = default;
  ~BaseECSBenchmark() = default;
  BaseECSBenchmark(const BaseECSBenchmark&) = default;
  BaseECSBenchmark& operator=(const BaseECSBenchmark&) = default;
  BaseECSBenchmark(BaseECSBenchmark&&) noexcept = default;
  BaseECSBenchmark& operator=(BaseECSBenchmark&&) noexcept = default;


  void setCounters(benchmark::State& state, const std::vector<Entity>& entities,
                   const ComponentsCounter& components_counter) {
    state.counters["entities"] = static_cast<double>(entities.size());
    state.counters["components_one"] = static_cast<double>(components_counter.component_one_count);
    state.counters["components_two"] = static_cast<double>(components_counter.component_two_count);
    state.counters["components_three"] = static_cast<double>(components_counter.component_three_count);
  }


  ComponentsCounter createEntities(EntityManager& registry, size_t nentities) {
    ComponentsCounter components_counter;
    for (size_t i = 0; i < nentities; i++) {
      m_entities_factory.create(registry);
      components_counter.component_one_count++;
      components_counter.component_two_count++;
      components_counter.component_three_count++;
    }
    return components_counter;
  }

  ComponentsCounter createEntities(EntityManager& registry, size_t nentities, std::vector<Entity>& out) {
    ComponentsCounter components_counter;
    out.clear();
    out.reserve(nentities);
    for (size_t i = 0; i < nentities; i++) {
      out.emplace_back(m_entities_factory.create(registry));
      components_counter.component_one_count++;
      components_counter.component_two_count++;
      components_counter.component_three_count++;
    }
    return components_counter;
  }


  ComponentsCounter createEntitiesWithHalfComponents(EntityManager& registry, size_t nentities) {
    ComponentsCounter components_counter;
    for (size_t i = 0; i < nentities; i++) {
      if ((i % 2) == 0) {
        m_entities_factory.create(registry);
        components_counter.component_one_count++;
        components_counter.component_two_count++;
        components_counter.component_three_count++;
      } else {
        m_entities_factory.createMinimal(registry);
        components_counter.component_one_count++;
        components_counter.component_two_count++;
      }
    }
    return components_counter;
  }

  ComponentsCounter createEntitiesWithHalfComponents(EntityManager& registry, size_t nentities,
                                                     std::vector<Entity>& out) {
    ComponentsCounter components_counter;
    out.clear();
    out.reserve(nentities);
    for (size_t i = 0; i < nentities; i++) {
      if ((i % 2) == 0) {
        out.emplace_back(m_entities_factory.create(registry));
        components_counter.component_one_count++;
        components_counter.component_two_count++;
        components_counter.component_three_count++;
      } else {
        m_entities_factory.createMinimal(registry);
        components_counter.component_one_count++;
        components_counter.component_two_count++;
      }
    }
    return components_counter;
  }


  template <class tEntityFactory, class tEntityManager = typename tEntityFactory::EntityManager,
            bool destory_entites = false>
  requires HasRemoveComponentsFeatures<tEntityFactory> ComponentsCounter
  createEntitiesWithMixedComponents(tEntityManager& registry, size_t nentities, std::vector<Entity>& out) {
    ComponentsCounter components_counter;
    out.clear();
    out.reserve(nentities);
    // inspired from EnTT benchmark "pathological",
    // https://github.com/skypjack/entt/blob/de0e5862dd02fa669325a0a06b7936af4d2a841d/test/benchmark/benchmark.cpp#L44
    for (size_t i = 0, j = 0; i < nentities; i++) {
      out.emplace_back(m_entities_factory.create(registry));
      components_counter.component_one_count++;
      components_counter.component_two_count++;
      components_counter.component_three_count++;
      if (nentities < 100 || (i >= 2 * nentities / 4 && i <= 3 * nentities / 4)) {
        if (nentities < 100 || (j % 10) == 0U) {
          if ((i % 7) == 0U) {
            m_entities_factory.removeComponentOne(registry, out.back());
            components_counter.component_one_count--;
          }
          if ((i % 11) == 0U) {
            m_entities_factory.removeComponentTwo(registry, out.back());
            components_counter.component_two_count--;
          }
          if ((i % 13) == 0U) {
            m_entities_factory.removeComponentThree(registry, out.back());
            components_counter.component_three_count--;
          }
          if constexpr (destory_entites) {
            if ((i % 17) == 0U) {
              m_entities_factory.destroy(registry, out.back());
              components_counter.component_one_count++;
              components_counter.component_two_count++;
              components_counter.component_three_count++;
            }
          }
        }
        j++;
      }
    }
    return components_counter;
  }
  template <class tEntityFactory, class tEntityManager = typename tEntityFactory::EntityManager>
  requires HasRemoveComponentsFeatures<tEntityFactory>
  inline ComponentsCounter createEntitiesWithMixedComponentsAndDestroyedEntitites(tEntityManager& registry,
                                                                                  size_t nentities,
                                                                                  std::vector<Entity>& out) {
    return createEntitiesWithMixedComponents<tEntityManager, true>(registry, nentities, out);
  }

  template <class tEntityFactory, class tEntityManager = typename tEntityFactory::EntityManager,
            bool destory_entites = false>
  requires HasAddComponentsFeatures<tEntityFactory> ComponentsCounter
  createEntitiesWithMixedComponentsFromEmpty(tEntityManager& registry, size_t nentities, std::vector<Entity>& out) {
    ComponentsCounter components_counter;
    out.clear();
    out.reserve(nentities);
    // inspired from EnTT benchmark "pathological",
    // https://github.com/skypjack/entt/blob/de0e5862dd02fa669325a0a06b7936af4d2a841d/test/benchmark/benchmark.cpp#L44
    for (size_t i = 0, j = 0; i < nentities; i++) {
      out.emplace_back(m_entities_factory.createEmpty(registry));
      bool added = false;
      if (nentities < 100 || (i >= 2 * nentities / 4 && i <= 3 * nentities / 4)) {
        if (nentities < 100 || (j % 10) == 0U) {
          if ((i % 7) == 0U) {
            m_entities_factory.addComponentTwo(registry, out.back());
            m_entities_factory.addComponentThree(registry, out.back());
            components_counter.component_one_count++;
            components_counter.component_three_count++;
            added = true;
          }
          if ((i % 11) == 0U) {
            m_entities_factory.addComponentOne(registry, out.back());
            m_entities_factory.addComponentThree(registry, out.back());
            components_counter.component_one_count++;
            components_counter.component_three_count++;
            added = true;
          }
          if ((i % 13) == 0U) {
            m_entities_factory.addComponentOne(registry, out.back());
            m_entities_factory.addComponentTwo(registry, out.back());
            components_counter.component_one_count++;
            components_counter.component_two_count++;
            added = true;
          }
          if constexpr (destory_entites) {
            if ((i % 17) == 0U) {
              m_entities_factory.destroy(registry, out.back());
              added = true;
            }
          }
        }
        j++;
      }
      if (!added) {
        m_entities_factory.addComponentOne(registry, out.back());
        m_entities_factory.addComponentTwo(registry, out.back());
        m_entities_factory.addComponentThree(registry, out.back());
        components_counter.component_one_count++;
        components_counter.component_two_count++;
        components_counter.component_three_count++;
      }
    }
    return components_counter;
  }
  template <class tEntityFactory = EntityFactory, class tEntityManager = typename tEntityFactory::EntityManager>
  requires HasAddComponentsFeatures<tEntityFactory>
  inline ComponentsCounter createEntitiesWithMixedComponentsAndDestroyedEntitiesFromEmpty(tEntityManager& registry,
                                                                                          size_t nentities,
                                                                                          std::vector<Entity>& out) {
    return createEntitiesWithMixedComponentsFromEmpty<tEntityManager, true>(nentities, nentities, out);
  }

  ComponentsCounter createEntitiesWithMinimalComponents(EntityManager& registry, size_t nentities) {
    ComponentsCounter components_counter;
    for (size_t i = 0; i < nentities; i++) {
      m_entities_factory.createMinimal(registry);
      components_counter.component_one_count++;
      components_counter.component_two_count++;
    }
    return components_counter;
  }
  ComponentsCounter createEntitiesWithMinimalComponents(EntityManager& registry, size_t nentities,
                                                        std::vector<Entity>& out) {
    ComponentsCounter components_counter;
    out.clear();
    out.reserve(nentities);
    for (size_t i = 0; i < nentities; i++) {
      out.emplace_back(m_entities_factory.createMinimal(registry));
      components_counter.component_one_count++;
      components_counter.component_two_count++;
    }
    return components_counter;
  }

  ComponentsCounter createEntitiesWithSingleComponent(EntityManager& registry, size_t nentities,
                                                      std::vector<Entity>& out) {
    ComponentsCounter components_counter;
    out.clear();
    out.reserve(nentities);
    for (size_t i = 0; i < nentities; i++) {
      out.emplace_back(m_entities_factory.createSingle(registry));
      components_counter.component_one_count++;
    }
    return components_counter;
  }

  EntityFactory m_entities_factory;
};
} // namespace ecs::benchmarks::base

#endif // ECS_BENCHMARKS_BASEECSBENCHMARK_H_
