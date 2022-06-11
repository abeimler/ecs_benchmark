#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityplus::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &entityManager) {
        auto ret = entityManager.create_entity();
        ret.add_component<ecs::benchmarks::base::components::PositionComponent>();
        ret.add_component<ecs::benchmarks::base::components::VelocityComponent>();
        ret.add_component<ecs::benchmarks::base::components::DataComponent>();
        ret.set_tag<components::OneTwoThree>(true);
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &entityManager, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = entityManager.create_entity();
            entity.add_component<ecs::benchmarks::base::components::PositionComponent>();
            entity.add_component<ecs::benchmarks::base::components::VelocityComponent>();
            entity.add_component<ecs::benchmarks::base::components::DataComponent>();
            entity.set_tag<components::OneTwoThree>(true);
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &entityManager) {
        auto ret = entityManager.create_entity();
        ret.add_component<ecs::benchmarks::base::components::PositionComponent>();
        ret.add_component<ecs::benchmarks::base::components::VelocityComponent>();
        ret.set_tag<components::OneTwo>(true);
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &entityManager, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = entityManager.create_entity();
            entity.add_component<ecs::benchmarks::base::components::PositionComponent>();
            entity.add_component<ecs::benchmarks::base::components::VelocityComponent>();
            entity.set_tag<components::OneTwo>(true);
        }
    }

    void EntityFactory::destroy(EntityManager &/*entityManager*/, Entity entity) {
        entity.destroy();
    }

    void EntityFactory::destroyBulk(EntityManager &/*entityManager*/, std::vector<Entity> &in) {
        for (auto &entity: in) {
            entity.destroy();
        }
    }

    void EntityFactory::clear(EntityManager &entityManager) {
        /// @TODO: clear entities
        /*
        entityManager.for_each<components::OneTwo>([](auto entity){
            entity.destory();
        });
        entityManager.for_each<components::OneTwoThree>([](auto entity){
            entity.destory();
        });
        */
    }
}
