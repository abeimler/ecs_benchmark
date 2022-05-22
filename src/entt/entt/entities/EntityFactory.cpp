#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::entt::entities {

    EntityFactory::Entity EntityFactory::create(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::DirectionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::ComflabulationComponent>(ret);
        return ret;
    }

    void EntityFactory::createBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        for (auto &entity: out) {
            registry.emplace<ecs::benchmarks::base::components::PositionComponent>(entity);
            registry.emplace<ecs::benchmarks::base::components::DirectionComponent>(entity);
            registry.emplace<ecs::benchmarks::base::components::ComflabulationComponent>(entity);
        }
    }

    EntityFactory::Entity EntityFactory::createMinimal(EntityManager &registry) {
        auto ret = registry.create();
        registry.emplace<ecs::benchmarks::base::components::PositionComponent>(ret);
        registry.emplace<ecs::benchmarks::base::components::DirectionComponent>(ret);
        return ret;
    }

    void EntityFactory::createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) {
        registry.create(out.begin(), out.end());
        for (auto &entity: out) {
            registry.emplace<ecs::benchmarks::base::components::PositionComponent>(entity);
            registry.emplace<ecs::benchmarks::base::components::DirectionComponent>(entity);
        }
    }

    void EntityFactory::destory(EntityManager &registry, Entity entity) {
        registry.destroy(entity);
    }

    void EntityFactory::destoryBulk(EntityManager &registry, std::vector<Entity> &in) {
        registry.destroy(in.begin(), in.end());
    }

    void EntityFactory::clear(EntityManager &registry) {
        registry.clear();
    }
}
