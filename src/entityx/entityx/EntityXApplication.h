#ifndef ECS_BENCHMARKS_ENTITYX_APPLICATION_H_
#define ECS_BENCHMARKS_ENTITYX_APPLICATION_H_

#include "base/Application.h"
#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx {

class EntityXApplication final : public ::entityx::EntityX {
public:
  using EntityManager = ::entityx::EntityManager;
  using TimeDelta = ::entityx::TimeDelta;

  EntityXApplication() = default;

  explicit EntityXApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}

  inline EntityManager& getEntities() { return this->entities; }

  inline const EntityManager& getEntities() const { return this->entities; }

  void init();

  void uninit();

  void update(TimeDelta dt);

private:
  bool m_add_more_complex_system{false};
};

} // namespace ecs::benchmarks::entityx

#endif // ECS_BENCHMARKS_ENTITYX_APPLICATION_H_
