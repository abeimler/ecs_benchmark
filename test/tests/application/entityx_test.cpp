#include "base.h"
#include "entityx/EntityXApplication.h"
#include "entityx/entities/EntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::entityx {

SCENARIO("Test Application, Update System for entityx", "[template][entityx][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::entityx::EntityXApplication,
                                         ecs::benchmarks::entityx::entities::EntityFactory>
        application_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::entityx::EntityXApplication app;
    app.init();

    WHEN("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

} // namespace ecs::benchmarks::entt