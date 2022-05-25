#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityx::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &entities) {
        auto ret = entities.create();
        ret.assign<ecs::benchmarks::base::components::PositionComponent>();
        ret.assign<ecs::benchmarks::base::components::DirectionComponent>();
        ret.assign<ecs::benchmarks::base::components::DataComponent>();
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &entities, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = entities.create();
            entity.assign<ecs::benchmarks::base::components::PositionComponent>();
            entity.assign<ecs::benchmarks::base::components::DirectionComponent>();
            entity.assign<ecs::benchmarks::base::components::DataComponent>();
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &entities) {
        auto ret = entities.create();
        ret.assign<ecs::benchmarks::base::components::PositionComponent>();
        ret.assign<ecs::benchmarks::base::components::DirectionComponent>();
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &entities, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = entities.create();
            entity.assign<ecs::benchmarks::base::components::PositionComponent>();
            entity.assign<ecs::benchmarks::base::components::DirectionComponent>();
        }
    }

    void EntityFactory::destory(EntityManager &entities, Entity entity) {
        entities.destroy(entity.id());
    }

    void EntityFactory::destoryBulk(EntityManager &entities, std::vector<Entity> &in) {
        for (auto &entity: in) {
            entities.destroy(entity.id());
        }
    }

    void EntityFactory::clear(EntityManager &entities) {
        entities.reset();
    }
}
