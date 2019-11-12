#include "GinsengBenchmark.h"

namespace ginseng_benchmark {

void MovementSystem::update(EntityManager &db, TimeDelta dt) {
  db.visit([&](PositionComponent &position, DirectionComponent &direction) {
    position.x += float(direction.x * dt);
    position.y += float(direction.y * dt);
  });
}

void ComflabSystem::update(EntityManager &db, TimeDelta) {
  db.visit([&](ComflabulationComponent &comflab) {
    comflab.thingy *= 1.000001f;
    comflab.mingy = !comflab.mingy;
    comflab.dingy++;
    // comflab.stringy = std::to_string(comflab.dingy);
  });
}

int MoreComplexSystem::random(int min, int max) {
  // Seed with a real random value, if available
  static std::random_device r;

  // Choose a random mean between min and max
  static std::default_random_engine e1(r());

  std::uniform_int_distribution<int> uniform_dist(min, max);

  return uniform_dist(e1);
}

void MoreComplexSystem::update(EntityManager &db, TimeDelta dt) {
  db.visit([&](PositionComponent &position, DirectionComponent &direction,
               ComflabulationComponent &comflab) {
    std::vector<double> vec;
    for (size_t i = 0; i < comflab.dingy && i < 100; i++) {
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
  });
}

Application::Application(bool addmorecomplexsystem) : addmorecomplexsystem_(addmorecomplexsystem) {
  this->systems_.emplace_back(std::make_unique<MovementSystem>());
  this->systems_.emplace_back(std::make_unique<ComflabSystem>());
  if (this->addmorecomplexsystem_) {
    this->systems_.emplace_back(std::make_unique<MoreComplexSystem>());
  }
}

void Application::update(TimeDelta dt) {
  for (auto &system : this->systems_) {
    system->update(this->entities_, dt);
  }
}

} // namespace ginseng_benchmark