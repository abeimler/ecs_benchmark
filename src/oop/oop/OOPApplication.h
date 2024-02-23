#ifndef ECS_BENCHMARKS_OOP_APPLICATION_H_
#define ECS_BENCHMARKS_OOP_APPLICATION_H_

#include "base/Application.h"
#include "entities/EntityFactory.h"

namespace ecs::benchmarks::oop {

class OOPApplication {
public:
  using EntityManager = entities::EntityFactory::EntityManager;
  using TimeDelta = float;

  OOPApplication() = default;
  explicit OOPApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system) {}
  ~OOPApplication() = default;
  OOPApplication(const OOPApplication&) = delete;
  OOPApplication& operator=(const OOPApplication&) = delete;
  OOPApplication(OOPApplication&&) = default;
  OOPApplication& operator=(OOPApplication&&) = default;

  inline EntityManager& getEntities() noexcept { return m_entities; }

  void init();
  void uninit();

  void update(TimeDelta dt);

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseBasicSystems};
  entities::EntityFactory m_entityFactory;
  EntityManager m_entities;
};

} // namespace ecs::benchmarks::oop

#endif // ECS_BENCHMARKS_OOP_APPLICATION_H_
