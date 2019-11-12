#ifndef ENTITYX2BENCHMARK_H_
#define ENTITYX2BENCHMARK_H_

#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <entityx/entityx.hh>

namespace entityx2_benchmark {

struct PositionComponent {
  double x = 0.0f;
  double y = 0.0f;
};

struct DirectionComponent {
  double x = 0.0f;
  double y = 0.0f;
};

struct ComflabulationComponent {
  double thingy = 0.0;
  int dingy = 0;
  bool mingy = false;
  std::string stringy;
};

using EntityManager =
    entityx::EntityX<entityx::DefaultStorage, 0, PositionComponent,
                     DirectionComponent, ComflabulationComponent>;

template <typename C> using Component = C *;

using Entity = EntityManager::Entity;

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

  void update(EntityManager &es, TimeDelta dt) override;
};

class ComflabSystem : public System {
public:
  ComflabSystem() = default;

  void update(EntityManager &es, TimeDelta dt) override;
};

#ifdef USE_MORECOMPLEX_SYSTEM
class MoreComplexSystem : public System {
private:
  static int random(int min, int max);

public:
  MoreComplexSystem() = default;

  void update(EntityManager &es, TimeDelta dt) override;
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

class EntityX2Benchmark {
public:
  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

} // namespace entityx2_benchmark

#endif // ENTITYX2BENCHMARK_H_