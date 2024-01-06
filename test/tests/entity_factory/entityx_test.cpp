#include "base.h"
#include "entityx/entities/EntityFactory.h"
#include "entityx/entities/HeroMonsterEntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::entityx {

TEMPLATE_TEST_CASE_METHOD(ecs::benchmarks::EntityFactory_Fixture, "Test EntityFactory for entityx",
                          "[template][entityx][entity_factory]", ecs::benchmarks::entityx::entities::EntityFactory) {
  GIVEN("EntityFactory") {
    ecs::benchmarks::EntityFactory_Fixture<TestType> entity_factory_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;
    ::entityx::EntityX world;

    WHEN("create entity") {
      entity_factory_fixture.testCreateEntity(world.entities);
    }
    WHEN("create minimal entity") {
      entity_factory_fixture.testCreateMinimalEntity(world.entities);
    }
    WHEN("create single entity") {
      entity_factory_fixture.testCreateSingleEntity(world.entities);
    }

    WHEN("destroy entity") {
      entity_factory_fixture.testDestroyEntity(world.entities);
    }

    WHEN("get one component") {
      entity_factory_fixture.testGetComponentOne(world.entities);
    }
  }
}

TEMPLATE_TEST_CASE_METHOD(ecs::benchmarks::HeroMonsterEntityFactory_Fixture,
                          "Test HeroMonsterEntityFactory for entityx",
                          "[template][entityx][entity_factory][hero][monster]",
                          ecs::benchmarks::entityx::entities::HeroMonsterEntityFactory) {
  GIVEN("HeroMonsterEntityFactory") {
    ecs::benchmarks::HeroMonsterEntityFactory_Fixture<TestType> entity_factory_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;
    ::entityx::EntityX world;

    WHEN("create entity") {
      entity_factory_fixture.testCreateEntity(world.entities);
    }

    WHEN("get one component") {
      entity_factory_fixture.testGetPlayerComponent(world.entities);
    }
  }
}

} // namespace ecs::benchmarks::entityx