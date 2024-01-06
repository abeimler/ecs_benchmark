#include "base.h"
#include "ginseng/GinsengApplication.h"
#include "ginseng/entities/EntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::ginseng {

SCENARIO("Test Application, Update System for ginseng", "[template][ginseng][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::ginseng::GinsengApplication,
                                         ecs::benchmarks::ginseng::entities::EntityFactory>
        application_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::ginseng::GinsengApplication app;
    app.init();

    WHEN("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

} // namespace ecs::benchmarks::entt