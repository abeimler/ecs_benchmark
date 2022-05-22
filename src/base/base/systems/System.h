#ifndef ECS_BENCHMARKS_BASE_SYSTEM_H_
#define ECS_BENCHMARKS_BASE_SYSTEM_H_

namespace ecs::benchmarks::base::systems {

    template<class tEntityManager, typename tTimeDelta>
    class System {
    public:
        using TimeDelta = tTimeDelta;
        using EntityManager = tEntityManager;

        // virtual dtor and the rule of 6
        System() = default;

        virtual ~System() = default;

        System(const System &) = delete;

        System &operator=(const System &) = delete;

        System(System &&) = default;

        System &operator=(System &&) = default;

        virtual void update(EntityManager &es, TimeDelta dt) = 0;
    };

}

#endif