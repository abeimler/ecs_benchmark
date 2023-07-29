#include "base.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace ecs::benchmarks::pico_ecs {

TEMPLATE_TEST_CASE_METHOD(ecs::benchmarks::EntityFactory_Fixture,
                          "Test EntityFactory for pico_ecs",
                          "[template][pico_ecs][entity_factory]",
                          ecs::benchmarks::pico_ecs::entities::EntityFactory) {
  GIVEN("EntityFactory") {
    ecs::benchmarks::EntityFactory_Fixture<TestType> entity_factory_fixture;
    //auto& entity_factory = entity_factory_fixture.m_entity_factory;
    ecs::benchmarks::pico_ecs::entities::details::EntityManager registry;

    WHEN ("create entity") {
      entity_factory_fixture.testCreateEntity(registry);
    }
    WHEN ("create empty entity") {
      entity_factory_fixture.testCreateEmptyEntity(registry);
    }
    WHEN ("create minimal entity") {
      entity_factory_fixture.testCreateMinimalEntity(registry);
    }
    WHEN ("create single entity") {
      entity_factory_fixture.testCreateSingleEntity(registry);
    }

    WHEN ("destroy entity") {
      entity_factory_fixture.testDestroyEntity(registry);
    }

    WHEN ("get one component") {
      entity_factory_fixture.testGetComponentOne(registry);
    }
  }
}

}