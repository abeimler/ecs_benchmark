#ifndef ARTEMISBENCHMARK_H_
#define ARTEMISBENCHMARK_H_

#include <functional>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <Artemis/Artemis.h>

class ArtemisBenchmark {
public:
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

#ifdef USE_MORECOMPLEX_SYSTEM
  class MoreComplexSystem : public artemis::EntityProcessingSystem {
  private:
    artemis::ComponentMapper<PositionComponent> positionMapper_;
    artemis::ComponentMapper<DirectionComponent> directionMapper_;
    artemis::ComponentMapper<ComflabulationComponent> comflabulationMapper_;

    int random(int min, int max) {
      // Seed with a real random value, if available
      static std::random_device r;

      // Choose a random mean between min and max
      static std::default_random_engine e1(r());

      std::uniform_int_distribution<int> uniform_dist(min, max);

      return uniform_dist(e1);
    }

  public:
    virtual ~MoreComplexSystem() = default;
    MoreComplexSystem(const MoreComplexSystem &) = default;
    MoreComplexSystem &operator=(const MoreComplexSystem &) = default;
    MoreComplexSystem(MoreComplexSystem &&) = default;
    MoreComplexSystem &operator=(MoreComplexSystem &&) = default;

    MoreComplexSystem() {
      addComponentType<PositionComponent>();
      addComponentType<DirectionComponent>();
      addComponentType<ComflabulationComponent>();
    };

    virtual void initialize() {
      positionMapper_.init(*world);
      directionMapper_.init(*world);
      comflabulationMapper_.init(*world);
    };

    virtual void processEntity(artemis::Entity &e) {
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
  };
#endif

  class Application : public artemis::World {
  public:
    Application() {
      auto systemmanager = this->getSystemManager();

      this->movement_system_ =
          (MovementSystem *)systemmanager->setSystem(new MovementSystem());
      this->comflab_system_ =
          (ComflabSystem *)systemmanager->setSystem(new ComflabSystem());
#ifdef USE_MORECOMPLEX_SYSTEM
      this->more_complex_system_ =
          (MoreComplexSystem *)systemmanager->setSystem(
              new MoreComplexSystem());
#endif

      systemmanager->initializeAll();
    }

    void update(TimeDelta dt) {
      this->loopStart();
      this->setDelta(dt);

      this->movement_system_->process();
      this->comflab_system_->process();
#ifdef USE_MORECOMPLEX_SYSTEM
      this->more_complex_system_->process();
#endif
    }

  private:
    MovementSystem *movement_system_;
    ComflabSystem *comflab_system_;
#ifdef USE_MORECOMPLEX_SYSTEM
    MoreComplexSystem *more_complex_system_;
#endif
  };

  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

#endif // ARTEMISBENCHMARK_H_