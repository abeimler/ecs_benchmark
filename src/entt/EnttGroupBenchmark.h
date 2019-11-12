#ifndef ENTTGROUPBENCHMARK_H_
#define ENTTGROUPBENCHMARK_H_

#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <entt/entt.hpp>

namespace enttgroup_benchmark {

  struct PositionComponent {
    float x = 0.0f;
    float y = 0.0f;
  };

  struct DirectionComponent {
    float x = 0.0f;
    float y = 0.0f;
  };

  struct ComflabulationComponent {
    float thingy = 0.0;
    int dingy = 0;
    bool mingy = false;
    std::string stringy;
  };

  using EntityManager = entt::registry;

  // template <typename C>
  // using Component = C;

  using Entity = EntityManager::entity_type;

  using TimeDelta = double;

  class System {
  public:
    // virtual dtor and the rule of 6
    System() = default;
    virtual ~System() = default;
    System(const System &) = default;
    System &operator=(const System &) = default;
    System(System &&) = default;
    System &operator=(System &&) = default;

    virtual void update(EntityManager &es, TimeDelta dt) = 0;
  };

  class MovementSystem : public System {
  public:
    MovementSystem() = default;

    void update(EntityManager &registry, TimeDelta dt) override;
  };

  class ComflabSystem : public System {
  public:
    ComflabSystem() = default;

    void update(EntityManager &registry, TimeDelta dt) override;
  };

#ifdef USE_MORECOMPLEX_SYSTEM
  class MoreComplexSystem : public System {
  private:
    static int random(int min, int max);

  public:
    MoreComplexSystem() = default;

    void update(EntityManager &registry, TimeDelta dt) override;
  };
#endif

  class Application {
  public:
    Application();

    void update(TimeDelta dt);

    EntityManager &getEntityManager() { return this->entities_; }
    const EntityManager &getEntityManager() const { return this->entities_; }

  private:
    EntityManager entities_;
    std::vector<std::unique_ptr<System>> systems_;
  };

class EnttGroupBenchmark {
public:
  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

} // namespace enttgroup_benchmark

#endif // ENTTGROUPBENCHMARK_H_
