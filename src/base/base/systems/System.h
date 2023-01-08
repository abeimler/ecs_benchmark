#ifndef ECS_BENCHMARKS_BASE_SYSTEM_H_
#define ECS_BENCHMARKS_BASE_SYSTEM_H_

namespace ecs::benchmarks::base::systems {

template <class tEntityManager, typename tTimeDelta>
class System {
public:
  using TimeDelta = tTimeDelta;
  using EntityManager = tEntityManager;

  virtual void init(EntityManager& /*entities*/) {}

  // virtual dtor and the rule of 6
  System() = default;

  virtual ~System() = default;

  System(const System&) = delete;

  System& operator=(const System&) = delete;

  System(System&&) noexcept = default;

  System& operator=(System&&) noexcept = default;

  virtual void update(EntityManager& registry, TimeDelta dt) = 0;
};

} // namespace ecs::benchmarks::base::systems

#endif