#pragma once

namespace eventpp {

struct BaseEvent {
    virtual ~BaseEvent() = 0;
};

inline BaseEvent::~BaseEvent() { }

template<class D>
struct Event: private BaseEvent
{ };

}
