#ifndef GINSENGBENCHMARK_H_
#define GINSENGBENCHMARK_H_

#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <ginseng/ginseng.hpp>

namespace ginseng_benchmark {

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

using EntityManager = ginseng::database;

using Entity = EntityManager::ent_id;

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

  void update(EntityManager &db, TimeDelta dt) override;
};

class ComflabSystem : public System {
public:
  ComflabSystem() = default;

  void update(EntityManager &db, TimeDelta) override;
};

class MoreComplexSystem : public System {
private:
  static int random(int min, int max);

public:
  MoreComplexSystem() = default;

  void update(EntityManager &db, TimeDelta dt) override;
};

class Application {
public:
  Application(bool addmorecomplexsystem = false);

  void update(TimeDelta dt);

  EntityManager &getEntityManager() { return this->entities_; }
  const EntityManager &getEntityManager() const { return this->entities_; }

private:
  EntityManager entities_;
  std::vector<std::unique_ptr<System>> systems_;
  bool addmorecomplexsystem_;
};

class GinsengBenchmark {
public:
  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

} // namespace ginseng_benchmark

#endif // GINSENGBENCHMARK_H_
