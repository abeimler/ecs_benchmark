#include "base.h"
#include "gaia-ecs/GaiaEcsApplication.h"
#include "gaia-ecs/entities/EntityFactory.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace ecs::benchmarks::gaia_ecs {

SCENARIO("Test Application, Update System for gaia-ecs", "[template][gaia][gaia-ecs][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::gaia_ecs::GaiaEcsApplication,
                                         ecs::benchmarks::gaia_ecs::entities::EntityFactory>
        application_fixture;
    // auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::gaia_ecs::GaiaEcsApplication app;
    app.init();

    WHEN("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

} // namespace ecs::benchmarks::gaia_ecs