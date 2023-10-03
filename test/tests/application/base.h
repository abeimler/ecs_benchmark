#ifndef ECS_BENCHMARK_TESTS_APPLICATION_BASE_H
#define ECS_BENCHMARK_TESTS_APPLICATION_BASE_H

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace ecs::benchmarks {

template <class Application, class EntityFactory>
struct Application_Fixture {
  using EntityManager = EntityFactory::EntityManager;
  using Entity = EntityFactory::Entity;

  EntityFactory m_entity_factory;
  inline static constexpr float fakeTimeDelta{1.0F / 60.0F};

  void testUpdateSystem(Application& app) {
    GIVEN("one entity") {
      auto entity = m_entity_factory.create(app.getEntities());
      REQUIRE(m_entity_factory.getEntitiesCount(app.getEntities()) == 1);
      REQUIRE(app.getEntities().valid(entity));

      THEN("component is init") {
        const auto& comp = m_entity_factory.getComponentOne(app.getEntities(), entity);

        AND_THEN("component.x is set") {
          REQUIRE(comp.x == Catch::Approx(0));
        }
      }

      WHEN("update system") {
        app.update(fakeTimeDelta);

        AND_WHEN("get component") {
          const auto& comp = m_entity_factory.getComponentOne(app.getEntities(), entity);

          AND_THEN("component.x is updated") {
            REQUIRE(comp.x > 0.0);
          }
        }
      }
    }
  }
};

} // namespace ecs::benchmarks

#endif // ECS_BENCHMARK_TESTS_APPLICATION_BASE_H
