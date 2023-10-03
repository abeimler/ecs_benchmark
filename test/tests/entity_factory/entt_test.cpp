#include "base.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::entt {

TEMPLATE_TEST_CASE_METHOD(ecs::benchmarks::EntityFactory_Fixture, "Test EntityFactory for entt",
                          "[template][entt][entity_factory]", ecs::benchmarks::entt::entities::EntityFactory) {
  GIVEN("EntityFactory") {
    ecs::benchmarks::EntityFactory_Fixture<TestType> entity_factory_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;
    ::entt::registry registry;

    WHEN("create entity") {
      entity_factory_fixture.testCreateEntity(registry);
    }
    WHEN("create empty entity") {
      entity_factory_fixture.testCreateEmptyEntity(registry);
    }
    WHEN("create minimal entity") {
      entity_factory_fixture.testCreateMinimalEntity(registry);
    }
    WHEN("create single entity") {
      entity_factory_fixture.testCreateSingleEntity(registry);
    }

    WHEN("destroy entity") {
      entity_factory_fixture.testDestroyEntity(registry);
    }

    WHEN("get one component") {
      entity_factory_fixture.testGetComponentOne(registry);
    }
  }
}

TEMPLATE_TEST_CASE_METHOD(ecs::benchmarks::HeroMonsterEntityFactory_Fixture, "Test HeroMonsterEntityFactory for entt",
                          "[template][entt][entity_factory][hero][monster]",
                          ecs::benchmarks::entt::entities::HeroMonsterEntityFactory) {
  GIVEN("HeroMonsterEntityFactory") {
    ecs::benchmarks::HeroMonsterEntityFactory_Fixture<TestType> entity_factory_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;
    ::entt::registry registry;

    WHEN("create entity") {
      entity_factory_fixture.testCreateEntity(registry);
    }

    WHEN("get one component") {
      entity_factory_fixture.testGetPlayerComponent(registry);
    }
  }
}

} // namespace ecs::benchmarks::entt