#include "base.h"
#include "pico_ecs/entities/EntityFactory.h"
#include "pico_ecs/PicoEcsApplication.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace ecs::benchmarks::pico_ecs {

SCENARIO("Test Application, Update System for pico_ecs", "[template][pico_ecs][application]") {
  GIVEN("Application") {
    ecs::benchmarks::Application_Fixture<ecs::benchmarks::pico_ecs::PicoEcsApplication, ecs::benchmarks::pico_ecs::entities::EntityFactory> application_fixture;
    //auto& entity_factory = entity_factory_fixture.m_entity_factory;

    ecs::benchmarks::pico_ecs::PicoEcsApplication app;
    app.init();

    WHEN ("update system") {
      application_fixture.testUpdateSystem(app);
    }

    app.uninit();
  }
}

}