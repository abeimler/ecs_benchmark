#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::entities {

    EntityFactory::Entity EntityFactory::createEmpty(EntityManager &registry) {
        return registry.create();
    }

    void EntityFactory::createEmptyBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
    }

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::VelocityComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::DataComponent>(ret);
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        registry.insert<ecs::benchmarks::base::components::PositionComponent>(out.begin(), out.end());
        registry.insert<ecs::benchmarks::base::components::VelocityComponent>(out.begin(), out.end());
        registry.insert<ecs::benchmarks::base::components::DataComponent>(out.begin(), out.end());
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::VelocityComponent>(ret);
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        registry.insert<ecs::benchmarks::base::components::PositionComponent>(out.begin(), out.end());
        registry.insert<ecs::benchmarks::base::components::VelocityComponent>(out.begin(), out.end());
    }

    EntityFactory::Entity EntityFactory::createSingle(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        return ret;
    }

    void EntityFactory::createSingleBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        registry.insert<ecs::benchmarks::base::components::PositionComponent>(out.begin(), out.end());
    }

    void EntityFactory::destroy(EntityManager &registry, Entity entity) {
        registry.destroy(entity);
    }

    void EntityFactory::destroyBulk(EntityManager &registry, std::vector<Entity> &entities) {
        registry.destroy(entities.begin(), entities.end());
    }
}
