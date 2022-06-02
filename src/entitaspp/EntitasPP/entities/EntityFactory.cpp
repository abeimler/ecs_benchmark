#include "EntityFactory.h"
#include "EntitasPP/components/PositionComponent.h"
#include "EntitasPP/components/DirectionComponent.h"
#include "EntitasPP/components/DataComponent.h"

namespace ecs::benchmarks::EntitasPP::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &pool) {
        auto ret = pool.CreateEntity();
        ret->Add<components::PositionComponent>();
        ret->Add<components::DirectionComponent>();
        ret->Add<components::DataComponent>();
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &pool, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = pool.CreateEntity();
            entity->Add<components::PositionComponent>();
            entity->Add<components::DirectionComponent>();
            entity->Add<components::DataComponent>();
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &pool) {
        auto ret = pool.CreateEntity();
        ret->Add<components::PositionComponent>();
        ret->Add<components::DirectionComponent>();
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &pool, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = pool.CreateEntity();
            entity->Add<components::PositionComponent>();
            entity->Add<components::DirectionComponent>();
        }
    }

    void EntityFactory::destroy(EntityManager &pool, Entity entity) {
        pool.DestroyEntity(entity);
    }

    void EntityFactory::destroyBulk(EntityManager &pool, std::vector<Entity> &in) {
        for (auto &entity: in) {
            pool.DestroyEntity(entity);
        }
    }

    void EntityFactory::clear(EntityManager &pool) {
        // @FIXME: Error, pool detected retained entities although all entities got destroyed. Did you release all entities?
        pool.DestroyAllEntities();
    }
}
