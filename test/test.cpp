#include <gtest/gtest.h>
#include <bus.hpp>
#include <event.hpp>
#include <signal.hpp>

using namespace eventpp;

struct EventA: public Event<EventA>
{
    EventA(int x, int y): value{x+y} { }
    int value;
};

struct EventB: public Event<EventB>
{ };

struct EventC: public Event<EventC>
{ };

struct MyListener
{
    void receive(const EventA &) { A++; }
    void listen(const EventB &) { B++; }
    void receive(const EventC &) { C++; }
    void reset() { A = 0; B = 0; C = 0; }
    int A{0};
    int B{0};
    int C{0};
};

using MyBus = Bus<EventA, EventB, EventC>;

#define TEST_CASE_LABEL EVENTPP

TEST(TEST_CASE_LABEL, ADD_REMOVE_EMIT) {
    std::shared_ptr<MyListener> listener = std::make_shared<MyListener>();
    MyBus bus{};

    listener->reset();
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))0);
    ASSERT_EQ(listener->A, 0);
    ASSERT_EQ(listener->B, 0);

    listener->reset();
    bus.add<EventA>(listener);
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))1);
    ASSERT_EQ(listener->A, 1);
    ASSERT_EQ(listener->B, 0);

    listener->reset();
    bus.remove<EventA>(listener);
    bus.add<EventA>(listener);
    bus.add<EventA>(listener);
    bus.add<EventA>(listener);
    bus.add<EventA>(listener);
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))1);
    ASSERT_EQ(listener->A, 1);
    ASSERT_EQ(listener->B, 0);

    listener->reset();
    bus.add<EventB, MyListener, &MyListener::listen>(listener);
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))2);
    ASSERT_EQ(listener->A, 1);
    ASSERT_EQ(listener->B, 1);

    listener->reset();
    bus.remove<EventA>(listener);
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))1);
    ASSERT_EQ(listener->A, 0);
    ASSERT_EQ(listener->B, 1);

    listener->reset();
    bus.remove<EventB, MyListener, &MyListener::listen>(listener);
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))0);
    ASSERT_EQ(listener->A, 0);
    ASSERT_EQ(listener->B, 0);
}

TEST(TEST_CASE_LABEL, REG_UNREG_EMIT) {
    std::shared_ptr<MyListener> listener = std::make_shared<MyListener>();
    MyBus bus{};

    listener->reset();
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();
    bus.publish<EventC>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))0);
    ASSERT_EQ(listener->A, 0);
    ASSERT_EQ(listener->B, 0);
    ASSERT_EQ(listener->C, 0);

    bus.reg(listener);

    listener->reset();
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();
    bus.publish<EventC>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))2);
    ASSERT_EQ(listener->A, 1);
    ASSERT_EQ(listener->B, 0);
    ASSERT_EQ(listener->C, 1);

    bus.unreg(listener);

    listener->reset();
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();
    bus.publish<EventC>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))0);
    ASSERT_EQ(listener->A, 0);
    ASSERT_EQ(listener->B, 0);
    ASSERT_EQ(listener->C, 0);
}

TEST(TEST_CASE_LABEL, EXPIRED_LISTENERS) {
    std::shared_ptr<MyListener> listener = std::make_shared<MyListener>();
    MyBus bus{};

    listener->reset();
    bus.add<EventA>(listener);
    bus.publish<EventA>(40, 2);
    bus.publish<EventB>();

    ASSERT_EQ(bus.size(), (decltype(bus.size()))1);
    ASSERT_EQ(listener->A, 1);
    ASSERT_EQ(listener->B, 0);

    listener->reset();
    listener = nullptr;

    ASSERT_EQ(bus.size(), (decltype(bus.size()))1);

    EXPECT_NO_THROW(bus.publish<EventA>(40, 2));
    EXPECT_NO_THROW(bus.publish<EventB>());

    ASSERT_EQ(bus.size(), (decltype(bus.size()))0);
}
