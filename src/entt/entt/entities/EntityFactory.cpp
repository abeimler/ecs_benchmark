#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::VelocityComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::DataComponent>(ret);
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        for (auto &entity: out) {
            registry.emplace<ecs::benchmarks::base::components::PositionComponent>(entity);
            registry.emplace<ecs::benchmarks::base::components::VelocityComponent>(entity);
            registry.emplace<ecs::benchmarks::base::components::DataComponent>(entity);
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::VelocityComponent>(ret);
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        for (auto &entity: out) {
            registry.emplace<ecs::benchmarks::base::components::PositionComponent>(entity);
            registry.emplace<ecs::benchmarks::base::components::VelocityComponent>(entity);
        }
    }

    void EntityFactory::destroy(EntityManager &registry, Entity entity) {
        registry.destroy(entity);
    }

    void EntityFactory::destroyBulk(EntityManager &registry, std::vector<Entity> &in) {
        registry.destroy(in.begin(), in.end());
    }

    void EntityFactory::clear(EntityManager &registry) {
        registry.clear();
    }
}
