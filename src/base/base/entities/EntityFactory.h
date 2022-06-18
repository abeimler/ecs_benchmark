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
        EntityFactory(EntityFactory &&) noexcept = default;
        EntityFactory &operator=(EntityFactory &&) noexcept = default;

        virtual Entity createEmpty(EntityManager &registry) = 0;
        virtual void createEmptyBulk(EntityManager &registry, std::vector<Entity> &out) = 0;

        virtual Entity createSingle(EntityManager &registry) = 0;
        virtual void createSingleBulk(EntityManager &registry, std::vector<Entity> &out) = 0;

        virtual Entity create(EntityManager &registry) = 0;
        virtual void createBulk(EntityManager &registry, std::vector<Entity> &out) = 0;

        virtual Entity createMinimal(EntityManager &registry) = 0;
        virtual void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out) = 0;

        virtual void destroy(EntityManager &registry, Entity entity) = 0;
        virtual void destroyBulk(EntityManager &registry, std::vector<Entity> &entities) = 0;


        virtual const ComponentOne &getComponentOneConst(EntityManager &registry, Entity entity) = 0;
        virtual const ComponentTwo &getComponentTwoConst(EntityManager &registry, Entity entity) = 0;

        virtual ComponentOne &getComponentOne(EntityManager &registry, Entity entity) = 0;
        virtual ComponentTwo &getComponentTwo(EntityManager &registry, Entity entity) = 0;
        virtual ComponentThree *getOptionalComponentThree(EntityManager &registry, Entity entity) = 0;

        virtual void removeComponentOne(EntityManager &registry, Entity entity) = 0;
        virtual void removeComponentTwo(EntityManager &registry, Entity entity) = 0;
        virtual void removeComponentThree(EntityManager &registry, Entity entity) = 0;

        virtual void addComponentOne(EntityManager &registry, Entity entity) = 0;
    };

}

#endif