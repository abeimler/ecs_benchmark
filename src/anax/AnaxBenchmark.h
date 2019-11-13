#ifndef ANAXBENCHMARK_H_
#define ANAXBENCHMARK_H_

#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <anax/Component.hpp>
#include <anax/System.hpp>
#include <anax/anax.hpp>

namespace anax_benchmark {

struct PositionComponent : anax::Component {
  double x = 0.0f;
  double y = 0.0f;

#ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
  PositionComponent() = default;
  virtual ~PositionComponent() = default;
  PositionComponent(const PositionComponent &) = default;
  PositionComponent &operator=(const PositionComponent &) = default;
  PositionComponent(PositionComponent &&) = default;
  PositionComponent &operator=(PositionComponent &&) = default;
#endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
};

struct DirectionComponent : anax::Component {
  double x = 0.0f;
  double y = 0.0f;

#ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
  DirectionComponent() = default;
  virtual ~DirectionComponent() = default;
  DirectionComponent(const DirectionComponent &) = default;
  DirectionComponent &operator=(const DirectionComponent &) = default;
  DirectionComponent(DirectionComponent &&) = default;
  DirectionComponent &operator=(DirectionComponent &&) = default;
#endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
};

struct ComflabulationComponent : anax::Component {
  double thingy = 0.0;
  int dingy = 0;
  bool mingy = false;
  std::string stringy;

#ifdef ANAX_VIRTUAL_DTORS_IN_COMPONENT
  ComflabulationComponent() = default;
  virtual ~ComflabulationComponent() = default;
  ComflabulationComponent(const ComflabulationComponent &) = default;
  ComflabulationComponent &operator=(const ComflabulationComponent &) = default;
  ComflabulationComponent(ComflabulationComponent &&) = default;
  ComflabulationComponent &operator=(ComflabulationComponent &&) = default;
#endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
};

using EntityManager = anax::World;
using Entity = anax::Entity;
using TimeDelta = double;

class MovementSystem
    : public anax::System<
          anax::Requires<PositionComponent, DirectionComponent>> {
public:
  MovementSystem() = default;

  void update(TimeDelta dt);
};

class ComflabSystem
    : public anax::System<anax::Requires<ComflabulationComponent>> {
public:
  ComflabSystem() = default;

  void update(TimeDelta dt);
};

class MoreComplexSystem
    : public anax::System<anax::Requires<PositionComponent, DirectionComponent,
                                         ComflabulationComponent>> {
private:
  static int random(int min, int max);

public:
  MoreComplexSystem() = default;

  void update(TimeDelta dt);
};

class Application : public anax::World {
public:
  Application(bool addmorecomplexsystem = false);

  void update(TimeDelta dt);

  EntityManager &getEntityManager() { return *this; }
  const EntityManager &getEntityManager() const { return *this; }

private:
  MovementSystem movement_system_;
  ComflabSystem comflab_system_;
  MoreComplexSystem morecomplex_system_;
  bool addmorecomplexsystem_;
};

class AnaxBenchmark {
public:
  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

} // namespace anax_benchmark

#endif // ANAXBENCHMARK_H_