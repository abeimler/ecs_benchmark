#include "base.h"
#include "flecs/FlecsApplication.h"
#include "flecs/entities/EntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::flecs {

SCENARIO("Test Application, Update System for flecs", "[template][flecs][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::flecs::FlecsApplication,
                                         ecs::benchmarks::flecs::entities::EntityFactory>
        application_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::flecs::FlecsApplication app;
    app.init();

    WHEN("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

} // namespace ecs::benchmarks::entt