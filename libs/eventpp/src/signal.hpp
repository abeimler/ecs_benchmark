#pragma once

#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

namespace eventpp {

template<typename E>
class Signal {
    using InstanceType = std::weak_ptr<void>;
    using CallType = bool(*)(std::weak_ptr<void> &, const E &);

    template<void(*F)(const E &)>
    static bool stub(std::weak_ptr<void> &, const E &event) {
        F(event);
        return true;
    }

    template<class C, void(C::*M)(const E &) = &C::receive>
    static bool stub(std::weak_ptr<void> &wptr, const E &event) {
        bool ret = false;

        std::shared_ptr<C> ptr = std::static_pointer_cast<C>(wptr.lock());
        if(ptr) {
            (ptr.get()->*M)(event);
            ret = true;
        }

        return ret;
    }

    struct Call {
        InstanceType instance;
        CallType call;

        Call(InstanceType i, CallType c)
            : instance{std::move(i)}, call{std::move(c)}
        { }

        bool operator==(const Call &other) const noexcept {
            return instance.lock() == other.instance.lock() &&
                    call == other.call;
        }
    };

public:
    template<void(*F)(const E &)>
    void add() {
        remove<F>();
        calls.emplace_back(std::weak_ptr<void>{}, &stub<F>);
    }

    template<class C, void(C::*M)(const E &)>
    void add(std::weak_ptr<C> ptr) {
        remove<C, M>(ptr);
        calls.emplace_back(std::move(ptr), &stub<C, M>);
    }

    template<class C, void(C::*M)(const E &)>
    void add(std::shared_ptr<C> ptr) {
        add(std::weak_ptr<C>{ptr});
    }

    template<void(*F)(const E &)>
    void remove() {
        Call call = { std::weak_ptr<void>{}, &stub<F> };
        calls.erase(std::remove(calls.begin(), calls.end(), call), calls.end());
    }

    template<class C, void(C::*M)(const E &)>
    void remove(std::weak_ptr<C> ptr) {
        Call call = { std::move(ptr), &stub<C, M> };
        calls.erase(std::remove(calls.begin(), calls.end(), call), calls.end());
    }

    template<class C, void(C::*M)(const E &)>
    void remove(std::shared_ptr<C> ptr) {
        remove(std::weak_ptr<C>{ptr});
    }

    void publish(const E &event) {
        for(auto it = calls.rbegin(), end = calls.rend(); it != end; it++) {
            bool valid = (it->call)(it->instance, event);

            if(!valid) {
                calls.erase(std::next(it).base());
            }
        }
    }

    std::size_t size() const noexcept {
        return calls.size();
    }

private:
    std::vector<Call> calls;
};

}
