#include "ECSBenchmark.h"
ECS_TYPE_IMPLEMENTATION;

namespace ecs_benchmark {

ECS_DEFINE_TYPE(PositionComponent);
ECS_DEFINE_TYPE(DirectionComponent);
ECS_DEFINE_TYPE(ComflabulationComponent);

void MovementSystem::tick(EntityManager *world, float dt) {
  world->each<PositionComponent, DirectionComponent>(
      [&](Entity *ent, PositionComponentHandle position,
          DirectionComponentHandle direction) {
        position->x += float(direction->x * dt);
        position->y += float(direction->y * dt);
      });
}

void ComflabSystem::tick(EntityManager *world, float dt) {
  world->each<ComflabulationComponent>(
      [&](Entity *ent, ComflabulationComponentHandle comflab) {
        comflab->thingy *= 1.000001f;
        comflab->mingy = !comflab->mingy;
        comflab->dingy++;
        // comflab.stringy = std::to_string(comflab.dingy);
      });
}

#ifdef USE_MORECOMPLEX_SYSTEM

static int MoreComplexSystem::random(int min, int max) {
  // Seed with a real random value, if available
  static std::random_device r;

  // Choose a random mean between min and max
  static std::default_random_engine e1(r());

  std::uniform_int_distribution<int> uniform_dist(min, max);

  return uniform_dist(e1);
}

void MoreComplexSystem::tick(EntityManager *world, float dt) {
  world->each<PositionComponent, DirectionComponent>(
      [&](Entity *ent, PositionComponentHandle position,
          DirectionComponentHandle direction,
          ComflabulationComponentHandle comflab) {
        std::vector<double> vec;
        for (size_t i = 0; i < comflab->dingy && i < 100; i++) {
          vec.push_back(i * comflab->thingy);
        }

        int sum = std::accumulate(std::begin(vec), std::end(vec), 0.0);
        int product = std::accumulate(std::begin(vec), std::end(vec), 1,
                                      std::multiplies<double>());

        comflab->stringy = std::to_string(comflab->dingy);

        if (comflab->dingy % 10000 == 0) {
          if (position->x > position->y) {
            direction->x = random(0, 5);
            direction->y = random(0, 10);
          } else {
            direction->x = random(0, 10);
            direction->y = random(0, 5);
          }
        }
      });
}
#endif

Application::Application() {
  this->entities_ = ECS::World::createWorld();

  this->systems_.emplace_back(entities_->registerSystem(new MovementSystem()));
  this->systems_.emplace_back(entities_->registerSystem(new ComflabSystem()));
#ifdef USE_MORECOMPLEX_SYSTEM
  this->systems_.emplace_back(
      entities_->registerSystem(new MoreComplexSystem()));
#endif
}

} // namespace ecs_benchmark