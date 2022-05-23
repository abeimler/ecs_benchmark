#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::mustache::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        return registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>();
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>();
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        return registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent>();
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = registry.create<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent>();
        }
    }

    void EntityFactory::destory(EntityManager &registry, Entity entity) {
        registry.destroyNow(entity);
    }

    void EntityFactory::destoryBulk(EntityManager &registry, std::vector<Entity> &in) {
        for (auto &entity: in) {
            registry.destroyNow(entity);
        }
    }

    void EntityFactory::clear(EntityManager &registry) {
        registry.clear();
    }
}
