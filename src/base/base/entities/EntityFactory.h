#ifndef ECS_BENCHMARKS_BASE_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_BASE_ENTITYFACTORY_H_

#include <vector>

namespace ecs::benchmarks::base::entities {

    template<class tEntityManager, typename tEntity, class ComponentOne, class ComponentTwo, class ComponentThree>
    class EntityFactory {
    public:
        using EntityManager = tEntityManager;
        using Entity = tEntity;

        // virtual dtor and the rule of 6
        EntityFactory() = default;

        virtual ~EntityFactory() = default;

        EntityFactory(const EntityFactory &) = default;

        EntityFactory &operator=(const EntityFactory &) = default;

        EntityFactory(EntityFactory &&) = default;

        EntityFactory &operator=(EntityFactory &&) = default;

        virtual Entity create(EntityManager &registry) = 0;

        virtual void createBulk(EntityManager &registry, std::vector<Entity> &out) = 0;

        virtual Entity createMinimal(EntityManager &registry) = 0;

        virtual void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) = 0;

        virtual void destory(EntityManager &registry, Entity entity) = 0;

        virtual void destoryBulk(EntityManager &registry, std::vector<Entity> &in) = 0;

        virtual void clear(EntityManager &registry) = 0;

        virtual ComponentOne &getComponentOne(EntityManager &registry, Entity entity) = 0;

        virtual ComponentTwo &getComponentTwo(EntityManager &registry, Entity entity) = 0;

        virtual ComponentThree *getOptionalComponentThree(EntityManager &registry, Entity entity) = 0;
    };

}

#endif