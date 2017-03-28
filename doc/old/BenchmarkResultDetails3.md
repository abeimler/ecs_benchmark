
# Benchmark

Benchmark EventBus.

[entityx](https://github.com/alecthomas/entityx) vs. [eventpp](https://github.com/skypjack/eventpp)



## Candidates

### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. 
> The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.
> 
> EntityX is an EC system that uses C++11 features to provide type-safe component management, event delivery, etc. 
> It was built during the creation of a 2D space shooter.

Version: 1.x


### eventpp by @skypjack

> Minimal C++ message system aimed to work as an event bus for the application.
> 
> This class is not meant as a drop-in replacement for the std:function. That is not the purpose of these classes nor the expectation is to get better performance.
> This is meant as an event bus, nothing more.

Version: 1.x


### Environment

 - OS: Linux Ubuntu 16.04 LTS 64-Bit Version
 - CPU: Intel® Core™ i7-3770K CPU @ 3.50GHz × 4 
 - RAM: 8 GB




### Result

```bash
$ /usr/bin/time ./ecs_benchmark --bench .*entityx.*eventbus.* --bench .*eventpp.*eventbus.*

        entityx      eventbus listen to EventA publish EventA                                          100000000                14 ns/op
        entityx      eventbus listen to EventA publish EventA and EventB                                50000000                24 ns/op
        entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB              50000000                38 ns/op
[   10] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB               5000000               292 ns/op
[   50] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB               1000000              1460 ns/op
[  100] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB                500000              3039 ns/op
[  300] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB                200000              8849 ns/op
[ 1000] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB                 50000             29262 ns/op
[ 5000] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB                 10000            147345 ns/op
[10000] entityx      eventbus listen to EventA EventB and EventC publish EventA and EventB                  5000            306186 ns/op

        eventpp      eventbus listen to EventA publish EventA                                           50000000                21 ns/op
        eventpp      eventbus listen to EventA publish EventA and EventB                                50000000                24 ns/op
        eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB              20000000                64 ns/op
[   10] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB               2000000               642 ns/op
[   50] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB                500000              3215 ns/op
[  100] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB                200000              6425 ns/op
[  300] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB                100000             19273 ns/op
[ 1000] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB                 20000             62125 ns/op
[ 5000] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB                  5000            321193 ns/op
[10000] eventpp      eventbus listen to EventA EventB and EventC publish EventA and EventB                  2000            641016 ns/op

./ecs_benchmark 53.942s
53.78user 0.02system 0:53.95elapsed 99%CPU (0avgtext+0avgdata 3812maxresident)k
0inputs+0outputs (0major+154minor)pagefaults 0swaps

```




