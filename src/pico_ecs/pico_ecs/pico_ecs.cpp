#define PICO_ECS_IMPLEMENTATION
#include <pico_ecs.h>

#undef PICO_ECS_IMPLEMENTATION
#include "entities/EntityFactory.h"
namespace ecs::benchmarks::pico_ecs::entities {
size_t EntityFactory::getEntitiesCount(details::EntityManager& registry) {
  return registry.ecs->entity_pool.capacity - registry.ecs->entity_pool.size;
}
} // namespace ecs::benchmarks::pico_ecs::entities