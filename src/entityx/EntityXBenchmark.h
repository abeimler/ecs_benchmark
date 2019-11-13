#ifndef ENTITYXBENCHMARK_H_
#define ENTITYXBENCHMARK_H_

#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <entityx/entityx.h>

namespace entityx1_benchmark {

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

// Convenience types for our entity system.
using Entity = entityx::Entity;
using EntityManager = entityx::EntityManager;
using EventManager = entityx::EventManager;

template <typename C> using Component = entityx::ComponentHandle<C>;

template <class S> using System = entityx::System<S>;

using TimeDelta = entityx::TimeDelta;

class MovementSystem : public System<MovementSystem> {
public:
  MovementSystem() = default;

  void update(entityx::EntityManager &es, entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};

class ComflabSystem : public System<ComflabSystem> {
public:
  ComflabSystem() = default;

  void update(entityx::EntityManager &es, entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};

class MoreComplexSystem : public System<MoreComplexSystem> {
private:
  static int random(int min, int max);

public:
  MoreComplexSystem() = default;

  void update(entityx::EntityManager &es, entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};

class Application : public entityx::EntityX {
public:
  Application(bool addmorecomplexsystem = false);

  void update(TimeDelta dt);

  EntityManager &getEntityManager() { return this->entities; }
  const EntityManager &getEntityManager() const { return this->entities; }

private:
  bool addmorecomplexsystem_;
};

} // namespace entityx1_benchmark

#endif // ENTITYXBENCHMARK_H_