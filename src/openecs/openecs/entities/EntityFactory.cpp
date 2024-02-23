#include "EntityFactory.h"

namespace ecs::benchmarks::openecs::entities {

void EntityFactory::destroy(EntityManager& /*entities*/, Entity entity) {
  entity.destroy();
}

} // namespace ecs::benchmarks::openecs::entities
