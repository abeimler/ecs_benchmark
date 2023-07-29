#include "base.h"
#include "entt/entities/EntityFactory.h"
#include "entt/EnttApplication.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace ecs::benchmarks::entt {

SCENARIO("Test Application, Update System for entt", "[template][entt][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::entt::EnttApplication, ecs::benchmarks::entt::entities::EntityFactory> application_fixture;
    //auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::entt::EnttApplication app;
    app.init();

    WHEN ("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

}