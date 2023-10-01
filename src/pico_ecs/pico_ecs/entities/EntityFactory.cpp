#include "EntityFactory.h"


namespace ecs::benchmarks::pico_ecs::entities {

namespace details {

void VelocityComponent_constructor(ecs_t* ecs, ecs_id_t entity_id, void* ptr, void* args) {
  (void)ecs;
  (void)entity_id;
  (void)args;

  ecs::benchmarks::base::components::VelocityComponent* comp =
      reinterpret_cast<ecs::benchmarks::base::components::VelocityComponent*>(ptr);
  comp->x = 1.0F;
  comp->y = 1.0F;
}

} // namespace details

} // namespace ecs::benchmarks::pico_ecs::entities