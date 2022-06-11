#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::openecs::entities {


    void EntityFactory::createBulk(EntityManager &entities, std::vector<Entity> &out) {
        out = entities.create(out.size());
        for (auto &entity: out) {
            entity.add<ecs::benchmarks::base::components::PositionComponent>();
            entity.add<ecs::benchmarks::base::components::VelocityComponent>();
            entity.add<ecs::benchmarks::base::components::DataComponent>();
        }
    }


    void EntityFactory::createMinimalBulk(EntityManager &entities, std::vector<Entity> &out) {
        out = entities.create(out.size());
        for (auto &entity: out) {
            entity.add<ecs::benchmarks::base::components::PositionComponent>();
            entity.add<ecs::benchmarks::base::components::VelocityComponent>();
            entity.add<ecs::benchmarks::base::components::DataComponent>();
        }
    }

    void EntityFactory::destroy(EntityManager &/*entities*/, Entity entity) {
        entity.destroy();
    }

    void EntityFactory::destroyBulk(EntityManager &/*entities*/, std::vector<Entity> &in) {
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
