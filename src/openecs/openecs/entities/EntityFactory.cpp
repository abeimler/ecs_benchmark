#include "EntityFactory.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::openecs::entities {

void EntityFactory::destroy(EntityManager& /*entities*/, Entity entity) {
  entity.destroy();
}

} // namespace ecs::benchmarks::openecs::entities
