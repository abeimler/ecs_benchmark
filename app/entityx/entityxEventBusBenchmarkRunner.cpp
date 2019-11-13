#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <entityx/EntityXBenchmark.h>
#include <entityx/entityx.h>

#include <bus.hpp>
#include <event.hpp>
#include <signal.hpp>

#include <benchpress/benchpress.hpp>

namespace eventpp_benchmark {
struct EventA {
  int value;

  EventA(int p_x, int p_y) : value(p_x + p_y) {}
};

struct EventB {
  entityx1_benchmark::Entity target;

  EventB(entityx1_benchmark::Entity p_target) : target(p_target) {}
};

struct EventC {
  EventC() = default;
};

class TestListenerEventA {
private:
  int a_ = 0;

public:
  TestListenerEventA() = default;

  void receive(const EventA &) { a_++; }

  void reset() { a_ = 0; }
};

class TestListenerEventB {
private:
  int b_ = 0;

public:
  TestListenerEventB() = default;

  void receive(const EventB &) { b_++; }

  void reset() { b_ = 0; }
};

class TestListenerEventC {
private:
  int c_ = 0;

public:
  TestListenerEventC() = default;

  void receive(const EventC &) { c_++; }

  void reset() { c_ = 0; }
};

using Bus = eventpp::Bus<EventA, EventB, EventC>;

static void runPublishEventsBenchmark(Bus &bus, entityx::Entity &entity,
                                      size_t nemits) {
  for (size_t i = 0; i < nemits; ++i) {
    const int x = 40;
    const int y = 2;
    bus.publish<EventA>(x, y);
    bus.publish<EventB>(entity);
    bus.publish<EventC>();
  }
}
} // namespace eventpp_benchmark

namespace entityx1_benchmark {
struct EventA {
  int value;

  EventA(int p_x, int p_y) : value(p_x + p_y) {}
};

struct EventB {
  Entity target;

  EventB(Entity p_target) : target(p_target) {}
};

struct EventC {
  EventC() = default;
};

class TestListenerEventA : public entityx::System<TestListenerEventA>,
                           public entityx::Receiver<TestListenerEventA> {
private:
  int a_ = 0;

public:
  TestListenerEventA() = default;

  void configure(entityx::EventManager &events) override {
    events.subscribe<EventA>(*this);
  }

  void update(entityx::EntityManager &entities, entityx::EventManager &events,
              entityx::TimeDelta dt) override {}

  void receive(const EventA &) { a_++; }

  void reset() { a_ = 0; }
};

class TestListenerEventB : public entityx::System<TestListenerEventB>,
                           public entityx::Receiver<TestListenerEventB> {
private:
  int b_ = 0;

public:
  TestListenerEventB() = default;

  void configure(entityx::EventManager &events) override {
    events.subscribe<EventB>(*this);
  }

  void update(entityx::EntityManager &entities, entityx::EventManager &events,
              entityx::TimeDelta dt) override {}

  void receive(const EventB &) { b_++; }

  void reset() { b_ = 0; }
};

class TestListenerEventC : public entityx::System<TestListenerEventB>,
                           public entityx::Receiver<TestListenerEventC> {
private:
  int c_ = 0;

public:
  TestListenerEventC() = default;

  void configure(entityx::EventManager &events) override {
    events.subscribe<EventC>(*this);
  }

  void update(entityx::EntityManager &entities, entityx::EventManager &events,
              entityx::TimeDelta dt) override {}

  void receive(const EventC &) { c_++; }

  void reset() { c_ = 0; }
};

class ApplicationEventAEventBEventC : public entityx::EntityX {
public:
  ApplicationEventAEventBEventC() {
    systems.add<TestListenerEventA>();
    systems.add<TestListenerEventB>();
    systems.add<TestListenerEventC>();
    systems.configure();
  }

  void update(entityx::TimeDelta dt) {
    systems.update<TestListenerEventA>(dt);
    systems.update<TestListenerEventB>(dt);
    systems.update<TestListenerEventC>(dt);
  }
};

class ApplicationEventA : public entityx::EntityX {
public:
  ApplicationEventA() {
    systems.add<TestListenerEventA>();
    systems.configure();
  }

  void update(entityx::TimeDelta dt) { systems.update<TestListenerEventA>(dt); }
};

class ApplicationEventAEventB : public entityx::EntityX {
public:
  ApplicationEventAEventB() {
    systems.add<TestListenerEventA>();
    systems.add<TestListenerEventB>();
    systems.configure();
  }

  void update(entityx::TimeDelta dt) {
    systems.update<TestListenerEventA>(dt);
    systems.update<TestListenerEventB>(dt);
  }
};

static void runPublishEventsBenchmark(entityx::EventManager &events,
                                      entityx::Entity &entity, size_t nemits) {
  for (size_t i = 0; i < nemits; ++i) {
    const int x = 42;
    const int y = 2;
    events.emit<EventA>(x, y);
    events.emit<EventB>(entity);
    events.emit<EventC>();
  }
}

BENCHMARK("        eventpp eventbus listen to EventA publish EventA",
          [](benchpress::context *ctx) {
            auto eventa_listener =
                std::make_shared<eventpp_benchmark::TestListenerEventA>();
            eventpp_benchmark::Bus bus;

            bus.reg(eventa_listener);

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              bus.publish<eventpp_benchmark::EventA>(40, 2);
            }
          })

BENCHMARK(
    "        eventpp eventbus listen to EventA publish EventA and EventB       "
    "           ",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        bus.publish<eventpp_benchmark::EventA>(40, 2);
        bus.publish<eventpp_benchmark::EventB>(entity);
      }
    })

BENCHMARK("        eventpp eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            entityx::EntityX app;
            auto &entities = app.entities;
            auto entity = entities.create();

            auto eventa_listener =
                std::make_shared<eventpp_benchmark::TestListenerEventA>();
            auto eventb_listener =
                std::make_shared<eventpp_benchmark::TestListenerEventB>();
            auto eventc_listener =
                std::make_shared<eventpp_benchmark::TestListenerEventC>();
            eventpp_benchmark::Bus bus;

            bus.reg(eventa_listener);
            bus.reg(eventb_listener);
            bus.reg(eventc_listener);

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              bus.publish<eventpp_benchmark::EventA>(40, 2);
              bus.publish<eventpp_benchmark::EventB>(entity);
              bus.publish<eventpp_benchmark::EventC>();
            }
          })

BENCHMARK(
    "    [10] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 10);
      }
    })

BENCHMARK(
    "    [50] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 50);
      }
    })

BENCHMARK(
    "   [100] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 100);
      }
    })

BENCHMARK(
    "   [300] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 300);
      }
    })

BENCHMARK(
    "  [1000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 1000);
      }
    })

BENCHMARK(
    "  [5000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 5000);
      }
    })

BENCHMARK(
    " [10000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 10000);
      }
    })

BENCHMARK(
    " [20000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 20000);
      }
    })

BENCHMARK(
    " [50000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 50000);
      }
    })

BENCHMARK(
    "[100000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 100000);
      }
    })

BENCHMARK(
    "[200000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 200000);
      }
    })

BENCHMARK(
    "[500000] eventpp-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      entityx::EntityX app;
      auto &entities = app.entities;
      auto entity = entities.create();

      auto eventa_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventA>();
      auto eventb_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventB>();
      auto eventc_listener =
          std::make_shared<eventpp_benchmark::TestListenerEventC>();
      eventpp_benchmark::Bus bus;

      bus.reg(eventa_listener);
      bus.reg(eventb_listener);
      bus.reg(eventc_listener);

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        eventpp_benchmark::runPublishEventsBenchmark(bus, entity, 500000);
      }
    })

BENCHMARK(
    "        entityx eventbus listen to EventA publish EventA                  "
    "           ",
    [](benchpress::context *ctx) {
      ApplicationEventA app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        events.emit<EventA>(40, 2);
      }
    })

BENCHMARK(
    "        entityx eventbus listen to EventA publish EventA and EventB       "
    "           ",
    [](benchpress::context *ctx) {
      ApplicationEventA app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        events.emit<EventA>(40, 2);
        events.emit<EventB>(entity);
      }
    })

BENCHMARK("        entityx eventbus listen to EventA EventB and EventC publish "
          "EventA and EventB",
          [](benchpress::context *ctx) {
            ApplicationEventAEventBEventC app;
            auto &entities = app.entities;
            auto &events = app.events;
            auto entity = entities.create();

            ctx->reset_timer();
            for (size_t i = 0; i < ctx->num_iterations(); ++i) {
              events.emit<EventA>(40, 2);
              events.emit<EventB>(entity);
              events.emit<EventC>();
            }
          })

BENCHMARK(
    "    [10] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 10);
      }
    })

BENCHMARK(
    "    [50] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 50);
      }
    })

BENCHMARK(
    "   [100] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 100);
      }
    })

BENCHMARK(
    "   [300] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 300);
      }
    })

BENCHMARK(
    "  [1000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 1000);
      }
    })

BENCHMARK(
    "  [5000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 5000);
      }
    })

BENCHMARK(
    " [10000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 10000);
      }
    })

BENCHMARK(
    " [20000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 20000);
      }
    })

BENCHMARK(
    " [50000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 50000);
      }
    })

BENCHMARK(
    "[100000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 100000);
      }
    })

BENCHMARK(
    "[200000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 200000);
      }
    })

BENCHMARK(
    "[500000] entityx-eventbus listen to EventA EventB and EventC publish "
    "EventA and EventB",
    [](benchpress::context *ctx) {
      ApplicationEventAEventBEventC app;
      auto &entities = app.entities;
      auto &events = app.events;
      auto entity = entities.create();

      ctx->reset_timer();
      for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        runPublishEventsBenchmark(events, entity, 500000);
      }
    })

} // namespace entityx1_benchmark