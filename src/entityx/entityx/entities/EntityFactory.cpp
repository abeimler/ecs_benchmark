#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityx::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &entities) {
        auto ret = entities.create();
        ret.assign<ecs::benchmarks::base::components::PositionComponent>();
        ret.assign<ecs::benchmarks::base::components::VelocityComponent>();
        ret.assign<ecs::benchmarks::base::components::DataComponent>();
        return ret;
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &entities) {
        auto ret = entities.create();
        ret.assign<ecs::benchmarks::base::components::PositionComponent>();
        ret.assign<ecs::benchmarks::base::components::VelocityComponent>();
        return ret;
    }

    EntityFactory::Entity EntityFactory::createSingle(EntityManager &entities) {
        auto ret = entities.create();
        ret.assign<ecs::benchmarks::base::components::PositionComponent>();
        return ret;
    }

    EntityFactory::Entity EntityFactory::createEmpty(EntityManager &entities) {
        return entities.create();
    }

    void EntityFactory::destroy(EntityManager &entities, Entity entity) {
        entities.destroy(entity.id());
    }

    void EntityFactory::clear(EntityManager &entities) {
        entities.reset();
    }
}
