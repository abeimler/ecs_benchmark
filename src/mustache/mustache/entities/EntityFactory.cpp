#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::mustache::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        return registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>();
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>();
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        return registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent>();
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent>();
        }
    }

    void EntityFactory::destroy(EntityManager &registry, Entity entity) {
        registry.destroyNow(entity);
    }

    void EntityFactory::destroyBulk(EntityManager &registry, std::vector<Entity> &in) {
        for (auto &entity: in) {
            registry.destroyNow(entity);
        }
    }

    void EntityFactory::clear(EntityManager &registry) {
        registry.clear();
    }
}
