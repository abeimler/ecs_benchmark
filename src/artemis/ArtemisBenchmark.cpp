#include "ArtemisBenchmark.h"

namespace artemis_benchmark {

MovementSystem::MovementSystem() {
  addComponentType<PositionComponent>();
  addComponentType<DirectionComponent>();
};

void MovementSystem::initialize() {
  positionMapper_.init(*world);
  directionMapper_.init(*world);
};

void MovementSystem::processEntity(artemis::Entity &e) {
  auto dt = world->getDelta();

  auto position = positionMapper_.get(e);
  auto direction = directionMapper_.get(e);

  position->x += direction->x * dt;
  position->y += direction->y * dt;
};

ComflabSystem::ComflabSystem() { addComponentType<ComflabulationComponent>(); };

void ComflabSystem::initialize() { comflabulationMapper_.init(*world); };

void ComflabSystem::processEntity(artemis::Entity &e) {
  auto dt = world->getDelta();

  auto comflab = comflabulationMapper_.get(e);

  comflab->thingy *= 1.000001f;
  comflab->mingy = !comflab->mingy;
  comflab->dingy++;
  // comflab.stringy = std::to_string(comflab.dingy);
}

int MoreComplexSystem::random(int min, int max) {
  // Seed with a real random value, if available
  static std::random_device r;

  // Choose a random mean between min and max
  static std::default_random_engine e1(r());

  std::uniform_int_distribution<int> uniform_dist(min, max);

  return uniform_dist(e1);
}

MoreComplexSystem::MoreComplexSystem() {
  addComponentType<PositionComponent>();
  addComponentType<DirectionComponent>();
  addComponentType<ComflabulationComponent>();
};

void MoreComplexSystem::initialize() {
  positionMapper_.init(*world);
  directionMapper_.init(*world);
  comflabulationMapper_.init(*world);
};

void MoreComplexSystem::processEntity(artemis::Entity &e) {
  auto dt = world->getDelta();

  auto position = positionMapper_.get(e);
  auto direction = directionMapper_.get(e);
  auto comflab = comflabulationMapper_.get(e);

  if (comflab) {
    std::vector<double> vec;
    for (size_t i = 0; i < comflab->dingy && i < 100; i++) {
      vec.push_back(i * comflab->thingy);
    }

    int sum = std::accumulate(std::begin(vec), std::end(vec), 0.0);
    int product = std::accumulate(std::begin(vec), std::end(vec), 1,
                                  std::multiplies<double>());

    comflab->stringy = std::to_string(comflab->dingy);

    if (position && direction && comflab->dingy % 10000 == 0) {
      if (position->x > position->y) {
        direction->x = random(0, 5);
        direction->y = random(0, 10);
      } else {
        direction->x = random(0, 10);
        direction->y = random(0, 5);
      }
    }
  }
}

Application::Application(bool addmorecomplexsystem)
    : addmorecomplexsystem_(addmorecomplexsystem) {
  auto systemmanager = this->getSystemManager();

  this->movement_system_ =
      (MovementSystem *)systemmanager->setSystem(new MovementSystem());
  this->comflab_system_ =
      (ComflabSystem *)systemmanager->setSystem(new ComflabSystem());

  if (this->addmorecomplexsystem_) {
    this->more_complex_system_ =
        (MoreComplexSystem *)systemmanager->setSystem(new MoreComplexSystem());
  }

  systemmanager->initializeAll();
}

void Application::update(TimeDelta dt) {
  this->loopStart();
  this->setDelta(dt);

  this->movement_system_->process();
  this->comflab_system_->process();
  if (this->addmorecomplexsystem_) {
    this->more_complex_system_->process();
  }
}

} // namespace artemis_benchmark