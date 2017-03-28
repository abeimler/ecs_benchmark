## Synopsis

Minimal C++ message system aimed to work as an event bus for the application.

This class is not meant as a drop-in replacement for the `std:function`. That is
not the purpose of these classes nor the expectation is to get better
performance.<br/>
This is meant as an *event bus*, nothing more.

## Code Example

Here is an example of use:

```
using namespace eventpp;

struct EventA: public Event<EventA> { EventA(int) { } };
struct EventB: public Event<EventB> { };
struct EventC: public Event<EventC> { };

void fn(const EventB &) { }

struct MyListener
{
    void receive(const EventA &) { }
    void listen(const EventB &) { }
    void receive(const EventC &) { }
};

using MyBus = Bus<EventA, EventB, EventC>;

// ...

std::shared_ptr<MyListener> listener = std::make_shared<MyListener>();
MyBus bus{};

// ...

// member methods named receive are automatically attached to the bus
bus.reg(listener);

// all the other member methods can be easily attached too
bus.add<EventB, MyListener, &MyListener::listen>(listener);

// also, member methods named receive can be added or removed as it follows
bus.remove<EventA>(listener);
bus.add<EventA>(listener);

// functions are accepted citizens as well
bus.add<EventB, fn>();
bus.remove<EventB, fn>();

// finally, events can be emitted with a single command
bus.publish<EventA>(42);
bus.publish<EventB>();
bus.publish<EventC>();
```

And that's all.

## Motivation

Uhm... Well, I was experimenting. What else?<br/>
I needed a minimal *event bus* for my applications, something easy to use and
with a bunch of features like auto disconnection support for the listeners and
auto registration of the member methods.

## Installation

The *eventpp* library is a header only library.<br/>
Because of that, a user is demanded simply to include it and all the
functionalities will be available at once.<br/>
Please, note that all the types are part of the `eventpp` namespace.

## Contributors

Michele Caini ([skypjack](https://github.com/skypjack))

## License

The MIT License (MIT)
=====================

Copyright © `2016` `Michele Caini`

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the “Software”), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
