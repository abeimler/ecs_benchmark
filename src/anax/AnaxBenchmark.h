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

class AnaxBenchmark {
public:
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
    ComflabulationComponent &
    operator=(const ComflabulationComponent &) = default;
    ComflabulationComponent(ComflabulationComponent &&) = default;
    ComflabulationComponent &operator=(ComflabulationComponent &&) = default;
#endif // ANAX_VIRTUAL_DTORS_IN_COMPONENT
  };

  using TimeDelta = double;

  class MovementSystem
      : public anax::System<
            anax::Requires<PositionComponent, DirectionComponent>> {
  public:
    MovementSystem() = default;

    void update(TimeDelta dt) {
      auto entities = getEntities();
      for (auto &entity : entities) {
        auto &position = entity.getComponent<PositionComponent>();
        auto &direction = entity.getComponent<DirectionComponent>();

        position.x += direction.x * dt;
        position.y += direction.y * dt;
      }
    }
  };

  class ComflabSystem
      : public anax::System<anax::Requires<ComflabulationComponent>> {
  public:
    ComflabSystem() = default;

    void update(TimeDelta dt) {

      auto entities = getEntities();
      for (auto &entity : entities) {
        auto &comflab = entity.getComponent<ComflabulationComponent>();

        comflab.thingy *= 1.000001f;
        comflab.mingy = !comflab.mingy;
        comflab.dingy++;
        // comflab.stringy = std::to_string(comflab.dingy);
      }
    }
  };

#ifdef USE_MORECOMPLEX_SYSTEM
  class MoreComplexSystem
      : public anax::System<anax::Requires<
            PositionComponent, DirectionComponent, ComflabulationComponent>> {
  private:
    static int random(int min, int max) {
      // Seed with a real random value, if available
      static std::random_device r;

      // Choose a random mean between min and max
      static std::default_random_engine e1(r());

      std::uniform_int_distribution<int> uniform_dist(min, max);

      return uniform_dist(e1);
    }

  public:
    MoreComplexSystem() = default;

    void update(TimeDelta dt) {

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
  };
#endif

  class Application : public anax::World {
  public:
    Application() {
      this->addSystem(this->movement_system_);
      this->addSystem(this->comflab_system_);
#ifdef USE_MORECOMPLEX_SYSTEM
      this->addSystem(this->morecomplex_system_);
#endif
    }

    void update(double dt) {
      this->refresh();

      this->movement_system_.update(dt);
      this->comflab_system_.update(dt);
#ifdef USE_MORECOMPLEX_SYSTEM
      this->morecomplex_system_.update(dt);
#endif
    }

  private:
    MovementSystem movement_system_;
    ComflabSystem comflab_system_;
#ifdef USE_MORECOMPLEX_SYSTEM
    MoreComplexSystem morecomplex_system_;
#endif
  };

  static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};

#endif // ANAXBENCHMARK_H_