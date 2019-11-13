#ifndef ECSBENCHMARK_H_
#define ECSBENCHMARK_H_

#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#define ECS_NO_RTTI 1
#include <ECS.h>

namespace ecs_benchmark {

struct PositionComponent {
  ECS_DECLARE_TYPE;

  float x = 0.0f;
  float y = 0.0f;
};

struct DirectionComponent {
  ECS_DECLARE_TYPE;

  float x = 0.0f;
  float y = 0.0f;
};

struct ComflabulationComponent {
  ECS_DECLARE_TYPE;

  float thingy = 0.0;
  int dingy = 0;
  bool mingy = false;
  std::string stringy;
};

using PositionComponentHandle = ECS::ComponentHandle<PositionComponent>;
using DirectionComponentHandle = ECS::ComponentHandle<DirectionComponent>;
using ComflabulationComponentHandle =
    ECS::ComponentHandle<ComflabulationComponent>;

using EntityManager = ECS::World;

using Entity = ECS::Entity;

using TimeDelta = float;

class System : public ECS::EntitySystem {
public:
  // virtual dtor and the rule of 6
  System() = default;
  virtual ~System() = default;
  System(const System &) = default;
  System &operator=(const System &) = default;
  System(System &&) = default;
  System &operator=(System &&) = default;

  virtual void configure(EntityManager *world) override {}

  virtual void unconfigure(EntityManager *world) override {
    world->unsubscribeAll(this);
  }
};

class MovementSystem : public System {
public:
  MovementSystem() = default;

  void tick(EntityManager *world, float dt) override;
};

class ComflabSystem : public System {
public:
  ComflabSystem() = default;

  void tick(EntityManager *world, float dt) override;
};

class MoreComplexSystem : public System {
private:
  static int random(int min, int max);

public:
  MoreComplexSystem() = default;

  void tick(EntityManager *world, float dt) override;
};

class Application {
public:
  Application(bool addmorecomplexsystem = false);
  virtual ~Application();

  void update(TimeDelta dt) { this->entities_->tick(dt); }

  EntityManager &getEntityManager() { return *this->entities_; }
  const EntityManager &getEntityManager() const { return *this->entities_; }

private:
  EntityManager *entities_;
  std::vector<ECS::EntitySystem *> systems_;
  bool addmorecomplexsystem_;
};

class ECSBenchmark {
public:
static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

} // namespace ecs_benchmark

#endif // ECSBENCHMARK_H_
