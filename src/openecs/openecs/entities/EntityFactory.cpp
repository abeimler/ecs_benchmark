#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::openecs::entities {


    void EntityFactory::createBulk(EntityManager &entities, std::vector<Entity> &out) {
        out = entities.create(out.size());
        for (auto &entity: out) {
            entity.add<ecs::benchmarks::base::components::PositionComponent>();
            entity.add<ecs::benchmarks::base::components::DirectionComponent>();
            entity.add<ecs::benchmarks::base::components::ComflabulationComponent>();
        }
    }


    void EntityFactory::createMinimalBulk(EntityManager &entities, std::vector<Entity> &out) {
        out = entities.create(out.size());
        for (auto &entity: out) {
            entity.add<ecs::benchmarks::base::components::PositionComponent>();
            entity.add<ecs::benchmarks::base::components::DirectionComponent>();
            entity.add<ecs::benchmarks::base::components::ComflabulationComponent>();
        }
    }

    void EntityFactory::destory(EntityManager &/*entities*/, Entity entity) {
        entity.destroy();
    }

    void EntityFactory::destoryBulk(EntityManager &/*entities*/, std::vector<Entity> &in) {
        for (auto &entity: in) {
            entity.destroy();
        }
    }

    void EntityFactory::clear(EntityManager &entities) {
        /// @TODO: better reset
        entities.with([](Entity entity) {
            entity.destroy();
        });
    }
}
