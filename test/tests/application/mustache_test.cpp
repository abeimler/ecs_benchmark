#include "base.h"
#include "mustache/MustacheApplication.h"
#include "mustache/entities/EntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::mustache {

SCENARIO("Test Application, Update System for mustache", "[template][mustache][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::mustache::MustacheApplication,
                                         ecs::benchmarks::mustache::entities::EntityFactory>
        application_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::mustache::MustacheApplication app;
    app.init();

    WHEN("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

} // namespace ecs::benchmarks::entt