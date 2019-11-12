#ifndef ARTEMISBENCHMARK_H_
#define ARTEMISBENCHMARK_H_

#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <Artemis/Artemis.h>

namespace artemis_benchmark {

struct PositionComponent : artemis::Component {
  double x = 0.0f;
  double y = 0.0f;
};

struct DirectionComponent : artemis::Component {
  double x = 0.0f;
  double y = 0.0f;
};

struct ComflabulationComponent : artemis::Component {
  double thingy = 0.0;
  int dingy = 0;
  bool mingy = false;
  std::string stringy;
};

using System = artemis::EntityProcessingSystem;
using Entity = artemis::Entity;
using EntityManager = artemis::EntityManager;

using TimeDelta = double;

class MovementSystem : public artemis::EntityProcessingSystem {
private:
  artemis::ComponentMapper<PositionComponent> positionMapper_;
  artemis::ComponentMapper<DirectionComponent> directionMapper_;

public:
  ~MovementSystem() override = default;
  MovementSystem(const MovementSystem &) = default;
  MovementSystem &operator=(const MovementSystem &) = default;
  MovementSystem(MovementSystem &&) = default;
  MovementSystem &operator=(MovementSystem &&) = default;

  MovementSystem();

  void initialize() override;

  void processEntity(artemis::Entity &e) override;
};

class ComflabSystem : public artemis::EntityProcessingSystem {
private:
  artemis::ComponentMapper<ComflabulationComponent> comflabulationMapper_;

public:
  ~ComflabSystem() override = default;
  ComflabSystem(const ComflabSystem &) = default;
  ComflabSystem &operator=(const ComflabSystem &) = default;
  ComflabSystem(ComflabSystem &&) = default;
  ComflabSystem &operator=(ComflabSystem &&) = default;

  ComflabSystem();

  void initialize() override;

  void processEntity(artemis::Entity &e) override;
};

class MoreComplexSystem : public artemis::EntityProcessingSystem {
private:
  artemis::ComponentMapper<PositionComponent> positionMapper_;
  artemis::ComponentMapper<DirectionComponent> directionMapper_;
  artemis::ComponentMapper<ComflabulationComponent> comflabulationMapper_;

  static int random(int min, int max);

public:
  virtual ~MoreComplexSystem() = default;
  MoreComplexSystem(const MoreComplexSystem &) = default;
  MoreComplexSystem &operator=(const MoreComplexSystem &) = default;
  MoreComplexSystem(MoreComplexSystem &&) = default;
  MoreComplexSystem &operator=(MoreComplexSystem &&) = default;

  MoreComplexSystem();

  virtual void initialize() override;

  virtual void processEntity(artemis::Entity &e) override;
};

class Application : public artemis::World {
public:
  Application(bool addmorecomplexsystem = false);

  void update(TimeDelta dt);

private:
  MovementSystem *movement_system_;
  ComflabSystem *comflab_system_;
  MoreComplexSystem *more_complex_system_;
  bool addmorecomplexsystem_;
};

class ArtemisBenchmark {
public:
  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

} // namespace artemis_benchmark

#endif // ARTEMISBENCHMARK_H_