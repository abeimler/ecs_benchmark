#include "AnaxBenchmark.h"

namespace anax_benchmark {

void MovementSystem::update(TimeDelta dt) {
  auto entities = getEntities();
  for (auto &entity : entities) {
    auto &position = entity.getComponent<PositionComponent>();
    auto &direction = entity.getComponent<DirectionComponent>();

    position.x += direction.x * dt;
    position.y += direction.y * dt;
  }
}

void ComflabSystem::update(TimeDelta dt) {
  auto entities = getEntities();
  for (auto &entity : entities) {
    auto &comflab = entity.getComponent<ComflabulationComponent>();

    comflab.thingy *= 1.000001f;
    comflab.mingy = !comflab.mingy;
    comflab.dingy++;
    // comflab.stringy = std::to_string(comflab.dingy);
  }
}

int MoreComplexSystem::random(int min, int max) {
  // Seed with a real random value, if available
  static std::random_device r;

  // Choose a random mean between min and max
  static std::default_random_engine e1(r());

  std::uniform_int_distribution<int> uniform_dist(min, max);

  return uniform_dist(e1);
}

void MoreComplexSystem::update(TimeDelta dt) {

  auto entities = getEntities();
  for (auto &entity : entities) {
    auto &position = entity.getComponent<PositionComponent>();
    auto &direction = entity.getComponent<DirectionComponent>();
    auto &comflab = entity.getComponent<ComflabulationComponent>();

    std::vector<double> vec;
    for (int i = 0; i < comflab.dingy && i < 100; i++) {
      vec.push_back(i * comflab.thingy);
    }

    int sum = std::accumulate(std::begin(vec), std::end(vec), 0.0);
    int product = std::accumulate(std::begin(vec), std::end(vec), 1,
                                  std::multiplies<double>());

    comflab.stringy = std::to_string(comflab.dingy);

    if (comflab.dingy % 10000 == 0) {
      if (position.x > position.y) {
        direction.x = random(0, 5);
        direction.y = random(0, 10);
      } else {
        direction.x = random(0, 10);
        direction.y = random(0, 5);
      }
    }
  }
}

Application::Application(bool addmorecomplexsystem) : addmorecomplexsystem_(addmorecomplexsystem) {
  this->addSystem(this->movement_system_);
  this->addSystem(this->comflab_system_);
  if (this->addmorecomplexsystem_) {
    this->addSystem(this->morecomplex_system_);
  }
}

void Application::update(TimeDelta dt) {
  this->refresh();

  this->movement_system_.update(dt);
  this->comflab_system_.update(dt);
  if (this->addmorecomplexsystem_) {
    this->morecomplex_system_.update(dt);
  }
}

} // namespace anax_benchmark