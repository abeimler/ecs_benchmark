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

  MovementSystem() {
    addComponentType<PositionComponent>();
    addComponentType<DirectionComponent>();
  };

  void initialize() override {
    positionMapper_.init(*world);
    directionMapper_.init(*world);
  };

  void processEntity(artemis::Entity &e) override {
    auto dt = world->getDelta();

    auto position = positionMapper_.get(e);
    auto direction = directionMapper_.get(e);

    position->x += direction->x * dt;
    position->y += direction->y * dt;
  };
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

  ComflabSystem() { addComponentType<ComflabulationComponent>(); };

  void initialize() override { comflabulationMapper_.init(*world); };

  void processEntity(artemis::Entity &e) override {
    auto dt = world->getDelta();

    auto comflab = comflabulationMapper_.get(e);

    comflab->thingy *= 1.000001f;
    comflab->mingy = !comflab->mingy;
    comflab->dingy++;
    // comflab.stringy = std::to_string(comflab.dingy);
  }
};

class Application : public artemis::World {
public:
  Application() {
    auto systemmanager = this->getSystemManager();

    this->movement_system_ =
        (MovementSystem *)systemmanager->setSystem(new MovementSystem());
    this->comflab_system_ =
        (ComflabSystem *)systemmanager->setSystem(new ComflabSystem());

    systemmanager->initializeAll();
  }

  void update(TimeDelta dt) {
    this->loopStart();
    this->setDelta(dt);

    this->movement_system_->process();
    this->comflab_system_->process();
  }

private:
  MovementSystem *movement_system_;
  ComflabSystem *comflab_system_;
};

} // namespace artemis_benchmark

#endif // ARTEMISBENCHMARK_H_