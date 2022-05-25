#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::ginseng::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        auto ret = registry.create_entity();
        registry.add_component(ret, ecs::benchmarks::base::components::PositionComponent{});
        registry.add_component(ret, ecs::benchmarks::base::components::DirectionComponent{});
        registry.add_component(ret, ecs::benchmarks::base::components::DataComponent{});
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = registry.create_entity();
            registry.add_component(entity, ecs::benchmarks::base::components::PositionComponent{});
            registry.add_component(entity, ecs::benchmarks::base::components::DirectionComponent{});
            registry.add_component(entity, ecs::benchmarks::base::components::DataComponent{});
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        auto ret = registry.create_entity();
        registry.add_component(ret, ecs::benchmarks::base::components::PositionComponent{});
        registry.add_component(ret, ecs::benchmarks::base::components::DirectionComponent{});
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = registry.create_entity();
            registry.add_component(entity, ecs::benchmarks::base::components::PositionComponent{});
            registry.add_component(entity, ecs::benchmarks::base::components::DirectionComponent{});
        }
    }

    void EntityFactory::destroy(EntityManager &registry, Entity entity) {
        registry.destroy_entity(entity);
    }

    void EntityFactory::destroyBulk(EntityManager &registry, std::vector<Entity> &in) {
        for (auto &entity: in) {
            registry.destroy_entity(entity);
        }
    }

    void EntityFactory::clear(EntityManager &registry) {
        /// TODO: better reset
        registry = ::ginseng::database();
    }
}
