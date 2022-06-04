#include "EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::flecs::entities {

    void EntityFactory::createBulk(EntityManager &entities, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = entities.entity()
                    .add<ecs::benchmarks::base::components::PositionComponent>()
                    .add<ecs::benchmarks::base::components::DirectionComponent>()
                    .add<ecs::benchmarks::base::components::DataComponent>();
        }
    }


    void EntityFactory::createMinimalBulk(EntityManager &entities, std::vector<Entity> &out) {
        for (auto &entity: out) {
            entity = entities.entity()
                    .add<ecs::benchmarks::base::components::PositionComponent>()
                    .add<ecs::benchmarks::base::components::DirectionComponent>();
        }
    }

    void EntityFactory::destroy(EntityManager &/*entities*/, Entity entity) {
        entity.destruct();
    }

    void EntityFactory::destroyBulk(EntityManager &/*entities*/, std::vector<Entity> &in) {
        for (auto &entity: in) {
            entity.destruct();
        }
    }

    void EntityFactory::clear(EntityManager &entities) {
        /// @TODO: better reset
        entities.each([](Entity entity) {
            entity.destruct();
        });
    }
}
