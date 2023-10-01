#ifndef ECS_BENCHMARK_TESTS_ENTITY_FACTORY_BASE_H
#define ECS_BENCHMARK_TESTS_ENTITY_FACTORY_BASE_H

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
    m_entity_factory.createEmpty(registry);

    THEN("registry is not empty") {
      REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
    }
  }

  void testCreateSingleEntity(EntityManager& registry) {
    m_entity_factory.createSingle(registry);

    THEN("registry is not empty") {
      REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
    }
  }

  void testCreateEntity(EntityManager& registry) {
    m_entity_factory.create(registry);

    THEN("registry is not empty") {
      REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
    }
  }

  void testCreateMinimalEntity(EntityManager& registry) {
    m_entity_factory.createMinimal(registry);

    THEN("registry is not empty") {
      REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
    }
  }

  void testDestroyEntity(EntityManager& registry) {
    GIVEN("one entity") {
      auto entity = m_entity_factory.create(registry);
      REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      REQUIRE(registry.valid(entity));

      WHEN("destroy") {
        m_entity_factory.destroy(registry, entity);

        THEN("entity is not valid, anymore") {
          REQUIRE_FALSE(registry.valid(entity));
        }
      }
    }
  }


  void testGetComponentOne(EntityManager& registry) {
    GIVEN("one entity") {
      auto entity = m_entity_factory.create(registry);
      REQUIRE(m_entity_factory.getEntitiesCount(registry) == 1);
      REQUIRE(registry.valid(entity));

      WHEN("get component one") {
        const auto& comp = m_entity_factory.getComponentOne(registry, entity);

        THEN("component.x is set") {
          REQUIRE(comp.x == Catch::Approx(0));
        }
      }
    }
  }
};

} // namespace ecs::benchmarks

#endif // ECS_BENCHMARK_TESTS_ENTITY_FACTORY_BASE_H
