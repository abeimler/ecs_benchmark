#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.h"

#include "bus.hpp"
#include "event.hpp"
#include "signal.hpp"


#include "EntityXBenchmark.h"



class EventppTest { 
    public:

    struct EventA {
        int value;

        EventA(int p_x, int p_y)
            : value (p_x + p_y) 
        {}
    };

    struct EventB { 
        EntityXBenchmark::Entity target;

        EventB(EntityXBenchmark::Entity p_target)
            : target(p_target)
        {}
    };

    struct EventC { 
        EventC() = default;
    };

    class TestListenerEventA {
        public:
        int a_ = 0;

        TestListenerEventA() = default;

        void receive(const EventA &) { a_++; }

        void reset() { a_ = 0; }
    };


    class TestListenerEventB {
        public:
        int b_ = 0;

        TestListenerEventB() = default;

        void receive(const EventB &) { b_++; }
        
        void reset() { b_ = 0; }
    };

    class TestListenerEventC {
        public:
        int c_ = 0;

        TestListenerEventC() = default;

        void receive(const EventC &) { c_++; }
        
        void reset() { c_ = 0; }
    };

    using Bus = eventpp::Bus<EventA, EventB, EventC>;

    static void runPublishEventsBenchmark(Bus &bus, entityx::Entity& entity, size_t nemits){
        for (size_t i = 0; i < nemits; ++i) {
            bus.publish<EventppTest::EventA>(40, 2);
            bus.publish<EventppTest::EventB>(entity);
            bus.publish<EventppTest::EventC>();
        }
    }

};




class EntityXEventBusTest { 
    public:

    struct EventA {
        int value;

        EventA(int p_x, int p_y)
            : value (p_x + p_y) 
        {}
    };

    struct EventB { 
        EntityXBenchmark::Entity target;

        EventB(EntityXBenchmark::Entity p_target)
            : target(p_target)
        {}
    };

    struct EventC { 
        EventC() = default;
    };



    class TestListenerEventA : public entityx::System<TestListenerEventA>, public entityx::Receiver<TestListenerEventA> {
        public:
        int a_ = 0;

        TestListenerEventA() = default;

        void configure(entityx::EventManager &events) override {
            events.subscribe<EventA>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {}

        void receive(const EventA &) { a_++; }

        void reset() { a_ = 0; }
    };


    class TestListenerEventB : public entityx::System<TestListenerEventB>, public entityx::Receiver<TestListenerEventB> {
        public:
        int b_ = 0;

        TestListenerEventB() = default;

        void configure(entityx::EventManager &events) override {
            events.subscribe<EventB>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {}

        void receive(const EventB &) { b_++; }
        
        void reset() { b_ = 0; }
    };

    class TestListenerEventC : public entityx::System<TestListenerEventB>, public entityx::Receiver<TestListenerEventC> {
        public:
        int c_ = 0;

        TestListenerEventC() = default;

        void configure(entityx::EventManager &events) override {
            events.subscribe<EventC>(*this);
        }

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {}

        void receive(const EventC &) { c_++; }
        
        void reset() { c_ = 0; }
    };

    class Application : public entityx::EntityX {
        public:
        Application() {
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

        void update(entityx::TimeDelta dt) {
            systems.update<TestListenerEventA>(dt);
        }
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

    static void runPublishEventsBenchmark(entityx::EventManager &events, entityx::Entity& entity, size_t nemits){
        for (size_t i = 0; i < nemits; ++i) {
            events.emit<EntityXEventBusTest::EventA>(40, 2);
            events.emit<EntityXEventBusTest::EventB>(entity);
            events.emit<EntityXEventBusTest::EventC>();
        }
    }
};










BENCHMARK("        eventpp      eventbus listen to EventA publish EventA", [](benchpress::context* ctx) {
    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        bus.publish<EventppTest::EventA>(40, 2);
    }
})

BENCHMARK("        eventpp      eventbus listen to EventA publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        bus.publish<EventppTest::EventA>(40, 2);
        bus.publish<EventppTest::EventB>(entity);
    }
})

BENCHMARK("        eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        bus.publish<EventppTest::EventA>(40, 2);
        bus.publish<EventppTest::EventB>(entity);
        bus.publish<EventppTest::EventC>();
    }
})






BENCHMARK("[   10] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 10);
    }
})

BENCHMARK("[   50] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 50);
    }
})

BENCHMARK("[  100] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 100);
    }
})


BENCHMARK("[  300] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 300);
    }
})


BENCHMARK("[ 1000] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 1000);
    }
})

BENCHMARK("[ 5000] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 5000);
    }
})


BENCHMARK("[10000] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    entityx::EntityX app;
    auto& entities = app.entities;
    auto entity = entities.create();

    auto eventa_listener = std::make_shared<EventppTest::TestListenerEventA>();
    auto eventb_listener = std::make_shared<EventppTest::TestListenerEventB>();
    auto eventc_listener = std::make_shared<EventppTest::TestListenerEventC>();
    EventppTest::Bus bus;

    bus.reg(eventa_listener);
    bus.reg(eventb_listener);
    bus.reg(eventc_listener);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EventppTest::runPublishEventsBenchmark(bus, entity, 10000);
    }
})











BENCHMARK("        entityx      eventbus listen to EventA publish EventA", [](benchpress::context* ctx) {
    EntityXEventBusTest::ApplicationEventA app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        events.emit<EntityXEventBusTest::EventA>(40, 2);
    }
})

BENCHMARK("        entityx      eventbus listen to EventA publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::ApplicationEventA app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        events.emit<EntityXEventBusTest::EventA>(40, 2);
        events.emit<EntityXEventBusTest::EventB>(entity);
    }
})

BENCHMARK("        entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        events.emit<EntityXEventBusTest::EventA>(40, 2);
        events.emit<EntityXEventBusTest::EventB>(entity);
        events.emit<EntityXEventBusTest::EventC>();
    }
})





BENCHMARK("[   10] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 10);
    }
})

BENCHMARK("[   50] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 50);
    }
})

BENCHMARK("[  100] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 100);
    }
})

BENCHMARK("[  300] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 300);
    }
})


BENCHMARK("[ 1000] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 1000);
    }
})





BENCHMARK("[ 5000] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 5000);
    }
})


BENCHMARK("[10000] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB", [](benchpress::context* ctx) {
    EntityXEventBusTest::Application app;
    auto& entities = app.entities;
    auto& events = app.events;
    auto entity = entities.create();

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        EntityXEventBusTest::runPublishEventsBenchmark(events, entity, 10000);
    }
})


