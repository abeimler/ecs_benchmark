#include <ecs/ECSBenchmark.h>

#include <BaseBenchmark.h>

#include <benchpress/benchpress.hpp>

namespace ecs_benchmark {
struct EventA {
  ECS_DECLARE_TYPE;

  int value;

  EventA(int p_x, int p_y) : value(p_x + p_y) {}
};
ECS_DEFINE_TYPE(EventA);

struct EventB {
  ECS_DECLARE_TYPE;

  Entity *target;

  EventB(Entity *p_target) : target(p_target) {}
};
ECS_DEFINE_TYPE(EventB);

struct EventC {
  ECS_DECLARE_TYPE;

  EventC() = default;
};
ECS_DEFINE_TYPE(EventC);

class EventAEventBEventCSystem : public ECS::EntitySystem,
                                 public ECS::EventSubscriber<EventA>,
                                 public ECS::EventSubscriber<EventB>,
                                 public ECS::EventSubscriber<EventC> {
private:
  int a_ = 0;
  int b_ = 0;
  int c_ = 0;

public:
  EventAEventBEventCSystem() = default;
  ~EventAEventBEventCSystem() override {}

  void configure(class ECS::World *world) override {
    world->subscribe<EventA>(this);
    world->subscribe<EventB>(this);
    world->subscribe<EventC>(this);
  }

  void unconfigure(class ECS::World *world) override {
    world->unsubscribeAll(this);
  }

  void tick(class ECS::World *world, float deltaTime) override {}

  void receive(class ECS::World * /*world*/,
               const EventA & /*event*/) override {
    this->a_++;
  }
  void receive(class ECS::World * /*world*/,
               const EventB & /*event*/) override {
    this->b_++;
  }
  void receive(class ECS::World * /*world*/,
               const EventC & /*event*/) override {
    this->b_++;
  }
};

class EventAEventBSystem : public ECS::EntitySystem,
                           public ECS::EventSubscriber<EventA>,
                           public ECS::EventSubscriber<EventB> {
private:
  int a_ = 0;
  int b_ = 0;

public:
  EventAEventBSystem() = default;
  ~EventAEventBSystem() override {}

  void configure(class ECS::World *world) override {
    world->subscribe<EventA>(this);
    world->subscribe<EventB>(this);
  }

  void unconfigure(class ECS::World *world) override {
    world->unsubscribeAll(this);
  }

  void tick(class ECS::World *world, float deltaTime) override {}

  void receive(class ECS::World * /*world*/,
               const EventA & /*event*/) override {
    this->a_++;
  }
  void receive(class ECS::World * /*world*/,
               const EventB & /*event*/) override {
    this->b_++;
  }
};

class EventASystem : public ECS::EntitySystem,
                     public ECS::EventSubscriber<EventA> {
private:
  int a_ = 0;

public:
  EventASystem() = default;
  ~EventASystem() override {}

  void configure(class ECS::World *world) override {
    world->subscribe<EventA>(this);
  }

  void unconfigure(class ECS::World *world) override {
    world->unsubscribeAll(this);
  }

  void tick(class ECS::World *world, float deltaTime) override {}

  void receive(class ECS::World * /*world*/,
               const EventA & /*event*/) override {
    this->a_++;
  }
};

static void runPublishEventsBenchmark(ECS::World *world, Entity *entity,
                                      size_t nemits) {
  for (size_t i = 0; i < nemits; ++i) {
    const int x = 42;
    const int y = 2;
    world->emit<EventA>({x, y});
    world->emit<EventB>({entity});
    world->emit<EventC>({});
  }
}

BENCHMARK("        ecs eventbus listen to EventA publish EventA",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus = world->registerSystem(new EventASystem());

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              world->emit<EventA>({40, 2});
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK(
    "        ecs eventbus listen to EventA publish EventA and EventB       "
    "           ",
    [](benchpress::context *ctx) {
      ECS::World *world = ECS::World::createWorld();

      ECS::EntitySystem *bus = world->registerSystem(new EventASystem());

      ECS::Entity *entity = world->create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        world->emit<EventA>({40, 2});
        world->emit<EventB>({entity});
      }

      ctx->stop_timer();
      world->destroyWorld();
    })

BENCHMARK("        ecs eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              world->emit<EventA>({40, 2});
              world->emit<EventB>({entity});
              world->emit<EventC>({});
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("    [10] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 10);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("    [50] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 50);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("   [100] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 100);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("   [300] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 300);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("  [1000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 1000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("  [5000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 5000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK(" [10000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 10000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK(" [20000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 20000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK(" [50000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 50000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("[100000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 100000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("[200000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 200000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

BENCHMARK("[500000] ecs-eventbus listen to EventA EventB and EventC publish "
          "EventA, EventB and EventC",
          [](benchpress::context *ctx) {
            ECS::World *world = ECS::World::createWorld();

            ECS::EntitySystem *bus =
                world->registerSystem(new EventAEventBEventCSystem());

            ECS::Entity *entity = world->create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              runPublishEventsBenchmark(world, entity, 500000);
            }

            ctx->stop_timer();
            world->destroyWorld();
          })

} // namespace ecs_benchmark