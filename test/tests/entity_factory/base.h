#ifndef ECS_BENCHMARK_TESTS_ENTITY_FACTORY_BASE_H
#define ECS_BENCHMARK_TESTS_ENTITY_FACTORY_BASE_H

#include "base/components/DataComponent.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace ecs::benchmarks {

template <class EntityFactory>
struct EntityFactory_Fixture {
  using EntityManager = EntityFactory::EntityManager;
  using Entity = EntityFactory::Entity;

  EntityFactory m_entity_factory;

  void testCreateEmptyEntity(EntityManager& registry) {
    [[maybe_unused]] auto entity = m_entity_factory.createEmpty(registry);

    THEN("registry is not empty") {
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                    registry) == 1);
      } else {
        REQUIRE(registry.valid(entity));
      }
    }
  }

  void testCreateSingleEntity(EntityManager& registry) {
    [[maybe_unused]] auto entity = m_entity_factory.createSingle(registry);

    THEN("registry is not empty") {
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                    registry) == 1);
      } else {
        REQUIRE(registry.valid(entity));
      }
    }
  }

  void testCreateEntity(EntityManager& registry) {
    [[maybe_unused]] auto entity = m_entity_factory.create(registry);

    THEN("registry is not empty") {
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                    registry) == 1);
      } else {
        REQUIRE(registry.valid(entity));
      }
    }
  }

  void testCreateMinimalEntity(EntityManager& registry) {
    [[maybe_unused]] auto entity = m_entity_factory.createMinimal(registry);

    THEN("registry is not empty") {
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                    registry) == 1);
      } else {
        REQUIRE(registry.valid(entity));
      }
    }
  }

  void testDestroyEntity(EntityManager& registry) {
    GIVEN("one entity") {
      auto entity = m_entity_factory.create(registry);
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                    registry) == 1);
      } else {
        REQUIRE(registry.valid(entity));
      }

      WHEN("destroy") {
        m_entity_factory.destroy(registry, entity);

        THEN("entity is not valid, anymore") {
          if constexpr (requires(EntityFactory ef, EntityManager em, Entity e) { em.valid(e); }) {
            REQUIRE_FALSE(registry.valid(entity));
          } else if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
            REQUIRE(m_entity_factory.getEntitiesCount(registry) == 0);
          } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                                 ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                                     em);
                               }) {
            REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                        registry) == 0);
          }
        }
      }
    }
  }


  void testGetComponentOne(EntityManager& registry) {
    GIVEN("one entity") {
      auto entity = m_entity_factory.create(registry);
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PositionComponent>(
                    registry) == 1);
      } else {
        REQUIRE(registry.valid(entity));
      }

      WHEN("get component one") {
        const auto& comp = m_entity_factory.getComponentOne(registry, entity);

        THEN("component.x is set") {
          REQUIRE(comp.x == Catch::Approx(0));
        }
      }
    }
  }
};

template <class EntityFactory>
struct HeroMonsterEntityFactory_Fixture {
  using EntityManager = EntityFactory::EntityManager;
  using Entity = EntityFactory::Entity;

  EntityFactory m_entity_factory;

  void testCreateEntity(EntityManager& registry) {
    [[maybe_unused]] auto entity = m_entity_factory.createRandom(registry);

    THEN("valid entity") {
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PlayerComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PlayerComponent>(
                    registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em, Entity e) { ef.valid(em, e); }) {
        REQUIRE(m_entity_factory.valid(registry, entity));
      } else {
        REQUIRE(registry.valid(entity));
      }
    }
  }


  void testGetPlayerComponent(EntityManager& registry) {
    GIVEN("one entity") {
      auto entity = m_entity_factory.createRandom(registry);
      if constexpr (requires(EntityFactory ef, EntityManager em) { ef.getEntitiesCount(em); }) {
        REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em) {
                             ef.template getComponentCount<ecs::benchmarks::base::components::PlayerComponent>(em);
                           }) {
        REQUIRE(m_entity_factory.template getComponentCount<ecs::benchmarks::base::components::PlayerComponent>(
                    registry) == 1);
      } else if constexpr (requires(EntityFactory ef, EntityManager em, Entity e) { ef.valid(em, e); }) {
        REQUIRE(m_entity_factory.valid(registry, entity));
      } else {
        REQUIRE(registry.valid(entity));
      }

      WHEN("get player component") {
        const auto& player = m_entity_factory.getPlayerComponent(registry, entity);

        THEN("got player component") {
          ((void)player);
          // REQUIRE(player);
        }
      }
    }
  }
};

} // namespace ecs::benchmarks

#endif // ECS_BENCHMARK_TESTS_ENTITY_FACTORY_BASE_H
