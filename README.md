# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

Simple Benchmarks of common ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [flecs](https://github.com/SanderMertens/flecs)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [OpenEcs](https://github.com/Gronis/OpenEcs)

## TL;DR Results

### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 Systems | 3079ns   | 3532ns           | 3071ns         | 3049ns          | 3038ns    | 109686ns   | 3950ns   |
| Update    64 entities with 3 Systems | 13343ns  | 15044ns          | 12928ns        | 13200ns         | 13240ns   | 123189ns   | 13788ns  |
| Update   256 entities with 3 Systems | 56497ns  | 66276ns          | 54816ns        | 55144ns         | 57302ns   | 164310ns   | 55377ns  |
| Update   ~1K entities with 3 Systems | 221343ns | 254158ns         | 213543ns       | 221857ns        | 225112ns  | 333359ns   | 216402ns |
| Update   ~4K entities with 3 Systems | 865816ns | 980152ns         | 838812ns       | 855028ns        | 878029ns  | 990964ns   | 843319ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 4ms        | 3ms     |
| Update  ~65K entities with 3 Systems | 13ms   | 15ms             | 13ms           | 13ms            | 13ms      | 14ms       | 13ms    |
| Update  262K entities with 3 Systems | 58ms   | 65ms             | 57ms           | 55ms            | 56ms      | 55ms       | 54ms    |
| Update   ~1M entities with 3 Systems | 227ms  | 271ms            | 270ms          | 226ms           | 241ms     | 225ms      | 217ms   |
| Update   ~2M entities with 3 Systems | 460ms  | 546ms            | 648ms          | 449ms           | 462ms     | 447ms      | 445ms   |




This is a very little Benchmark with three simple components and three small systems. In wild Entity-Component-Systems can have hundreds of components and a lot of systems and even more complex systems.
So always benchmarks YOUR special cases and systems, when needed and compare.

Some frameworks are faster in adding/removing components, others in creating or destroying entities, it always depends on what you need the most.
Always choose an ECS-Framework by features, for example EnTT has some great features like a 
[resource-management](https://github.com/skypjack/entt/wiki/Crash-Course:-resource-management) or [events](https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between), 
flecs has some nice [add-ons](https://github.com/SanderMertens/flecs#addons) and EntityX has a build-in [world/system-manager](https://github.com/alecthomas/entityx#manager-tying-it-all-together=).

Pick and evaluate a framework you like and have a look at the examples and API design.


## Details

### Features

All benchmarks are located in [`benchmark/benchmarks/`](benchmark/benchmarks/) and are written with [google/benchmark](https://github.com/google/benchmark).
Each benchmark must implement the template [ECSBenchmark.h](benchmark/benchmarks/ECSBenchmark.h).

Each framework has a sub-project in [`src/`](src) and must implement certain features (see [`src/base`](src/base)).

#### Components

1. `PositionComponent` with `x` and `y` coord.
2. `VelocityComponent` with `x` and `y` for movement.
3. `DataComponent` with some nonsense data.

#### Systems

1. `MovementSystem`: updates `PositionComponent` with (const) `VelocityComponent`
2. `DataSystem`: updates `DataComponent` with nonsense
3. `MoreComplexSystem`: updates Components with random data and nonsense



## More Benchmarks

Benchmarks of more common features, like "Creating entities", "Add and remove components", etc.

### Features tested

* Create Entities
* Destroy Entities
* Get Component(s)
* Remove and add component
* Systems (for-each entities)


### Environment

* **OS:** Linux
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 15.55GB
* **Compiler:** gcc (GCC) 12.2.0


### Create entities

![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|
| Create    16 entities with two Components | 2705ns    | 2780ns   | 10489ns   | 3017ns     | 647804ns  |
| Create    64 entities with two Components | 6604ns    | 4384ns   | 11785ns   | 5918ns     | 678278ns  |
| Create   256 entities with two Components | 22568ns   | 10298ns  | 16342ns   | 16843ns    | 728388ns  |
| Create   ~1K entities with two Components | 82047ns   | 33338ns  | 32435ns   | 58821ns    | 864475ns  |
| Create   ~4K entities with two Components | 320203ns  | 142728ns | 97306ns   | 232100ns   | 1502095ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 0ms        | 4ms     |
| Create  ~65K entities with two Components | 5ms       | 2ms    | 3ms       | 4ms        | 14ms    |
| Create  262K entities with two Components | 22ms      | 13ms   | 14ms      | 18ms       | 54ms    |
| Create   ~1M entities with two Components | 92ms      | 49ms   | 57ms      | 73ms       | 214ms   |
| Create   ~2M entities with two Components | 182ms     | 94ms   | 123ms     | 151ms      | 424ms   |



### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Destroy    16 entities with two components | 1434ns    | 1094ns   | 2008ns    | 691ns      | 406558ns |
| Destroy    64 entities with two components | 3525ns    | 2573ns   | 5476ns    | 809ns      | 413393ns |
| Destroy   256 entities with two components | 11711ns   | 8549ns   | 19353ns   | 1396ns     | 416789ns |
| Destroy   ~1K entities with two components | 46069ns   | 33002ns  | 75269ns   | 3092ns     | 448173ns |
| Destroy   ~4K entities with two components | 190462ns  | 128606ns | 296553ns  | 10125ns    | 534664ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 0ms        | 0ms     |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 4ms       | 0ms        | 2ms     |
| Destroy  262K entities with two components | 13ms      | 8ms    | 19ms      | 0ms        | 8ms     |
| Destroy   ~1M entities with two components | 59ms      | 36ms   | 85ms      | 6ms        | 35ms    |
| Destroy   ~2M entities with two components | 129ms     | 71ms   | 168ms     | 12ms       | 78ms    |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Unpack one component in    16 entities | 23ns      | 45ns    | 27ns      | 195ns      | 358ns   |
| Unpack one component in    64 entities | 97ns      | 186ns   | 114ns     | 745ns      | 1406ns  |
| Unpack one component in   256 entities | 369ns     | 731ns   | 444ns     | 3181ns     | 5930ns  |
| Unpack one component in   ~1K entities | 1488ns    | 2913ns  | 1786ns    | 11372ns    | 22456ns |
| Unpack one component in   ~4K entities | 5875ns    | 11817ns | 7047ns    | 64636ns    | 89483ns |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack one component in  262K entities | 0ms       | 0ms    | 0ms       | 3ms        | 5ms     |
| Unpack one component in   ~1M entities | 1ms       | 3ms    | 2ms       | 16ms       | 23ms    |
| Unpack one component in   ~2M entities | 3ms       | 6ms    | 4ms       | 27ms       | 46ms    |

**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Get one (const) component in    16 entities | 24ns      | 48ns    | 27ns      | 94ns       | 252ns   |
| Get one (const) component in    64 entities | 98ns      | 195ns   | 112ns     | 363ns      | 994ns   |
| Get one (const) component in   256 entities | 369ns     | 756ns   | 444ns     | 1431ns     | 4006ns  |
| Get one (const) component in   ~1K entities | 1460ns    | 3022ns  | 1752ns    | 5788ns     | 15951ns |
| Get one (const) component in   ~4K entities | 5873ns    | 12015ns | 7032ns    | 22924ns    | 63629ns |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Get one (const) component in  262K entities | 0ms       | 0ms    | 0ms       | 1ms        | 4ms     |
| Get one (const) component in   ~1M entities | 1ms       | 3ms    | 1ms       | 5ms        | 17ms    |
| Get one (const) component in   ~2M entities | 3ms       | 6ms    | 4ms       | 11ms       | 34ms    |



**Note:**
* Get one const component
  1. `const PositionComponent`


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack two components in    16 entities | 42ns      | 94ns    | 55ns      | 260ns      | 631ns    |
| Unpack two components in    64 entities | 174ns     | 366ns   | 222ns     | 1038ns     | 2473ns   |
| Unpack two components in   256 entities | 678ns     | 1472ns  | 901ns     | 4119ns     | 9978ns   |
| Unpack two components in   ~1K entities | 2696ns    | 5856ns  | 3562ns    | 16465ns    | 40428ns  |
| Unpack two components in   ~4K entities | 11199ns   | 24818ns | 14072ns   | 91426ns    | 160084ns |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 2ms     |
| Unpack two components in  262K entities | 0ms       | 1ms    | 0ms       | 4ms        | 10ms    |
| Unpack two components in   ~1M entities | 2ms       | 6ms    | 3ms       | 17ms       | 40ms    |
| Unpack two components in   ~2M entities | 5ms       | 12ms   | 7ms       | 35ms       | 82ms    |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack three components in     8 entities | 33ns      | 74ns    | 47ns      | 130ns      | 500ns    |
| Unpack three components in    32 entities | 141ns     | 298ns   | 193ns     | 508ns      | 1986ns   |
| Unpack three components in   128 entities | 528ns     | 1185ns  | 759ns     | 2016ns     | 7830ns   |
| Unpack three components in   512 entities | 2094ns    | 4760ns  | 3012ns    | 8146ns     | 31481ns  |
| Unpack three components in   ~2K entities | 8339ns    | 19090ns | 12160ns   | 43308ns    | 126626ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack three components in  131K entities | 0ms       | 1ms    | 0ms       | 2ms        | 8ms     |
| Unpack three components in  524K entities | 2ms       | 5ms    | 3ms       | 8ms        | 32ms    |
| Unpack three components in   ~1M entities | 4ms       | 10ms   | 7ms       | 17ms       | 64ms    |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Remove and Add a Component in    16 entities | 300ns     | 431ns    | 190ns     | 879ns      | 2699ns   |
| Remove and Add a Component in    64 entities | 1183ns    | 1698ns   | 741ns     | 3530ns     | 10796ns  |
| Remove and Add a Component in   256 entities | 4728ns    | 6756ns   | 2964ns    | 14022ns    | 43023ns  |
| Remove and Add a Component in   ~1K entities | 18785ns   | 27265ns  | 12030ns   | 55457ns    | 172341ns |
| Remove and Add a Component in   ~4K entities | 76651ns   | 118302ns | 48292ns   | 222988ns   | 695987ns |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 3ms        | 11ms    |
| Remove and Add a Component in  262K entities | 4ms       | 7ms    | 3ms       | 15ms       | 43ms    |
| Remove and Add a Component in   ~1M entities | 19ms      | 28ms   | 12ms      | 64ms       | 175ms   |
| Remove and Add a Component in   ~2M entities | 39ms      | 56ms   | 25ms      | 140ms      | 350ms   |




**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Update    16 entities with 2 systems | 3798ns    | 3404ns   | 3471ns    | 76504ns    | 4094ns   |
| Update    64 entities with 2 systems | 15164ns   | 14255ns  | 14168ns   | 84203ns    | 14250ns  |
| Update   256 entities with 2 systems | 60211ns   | 55233ns  | 59233ns   | 133661ns   | 54277ns  |
| Update   ~1K entities with 2 systems | 237322ns  | 216540ns | 219575ns  | 288724ns   | 212363ns |
| Update   ~4K entities with 2 systems | 928476ns  | 856659ns | 892006ns  | 927829ns   | 831053ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 3ms       | 3ms    | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 2 systems | 14ms      | 13ms   | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 2 systems | 60ms      | 55ms   | 58ms      | 53ms       | 55ms    |
| Update   ~1M entities with 2 systems | 243ms     | 224ms  | 233ms     | 215ms      | 218ms   |
| Update   ~2M entities with 2 systems | 492ms     | 452ms  | 471ms     | 438ms      | 441ms   |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Update    16 entities with 2 systems | 3332ns    | 2945ns   | 2994ns    | 72328ns    | 3793ns   |
| Update    64 entities with 2 systems | 14120ns   | 12932ns  | 12943ns   | 89130ns    | 13435ns  |
| Update   256 entities with 2 systems | 60551ns   | 56316ns  | 55472ns   | 124859ns   | 54465ns  |
| Update   ~1K entities with 2 systems | 236554ns  | 216347ns | 219053ns  | 287184ns   | 213520ns |
| Update   ~4K entities with 2 systems | 942157ns  | 848617ns | 855123ns  | 913719ns   | 831644ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 3ms       | 3ms    | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 2 systems | 15ms      | 13ms   | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 2 systems | 61ms      | 55ms   | 57ms      | 53ms       | 54ms    |
| Update   ~1M entities with 2 systems | 249ms     | 226ms  | 228ms     | 216ms      | 212ms   |
| Update   ~2M entities with 2 systems | 499ms     | 449ms  | 459ms     | 440ms      | 434ms   |




**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 systems | 3600ns   | 4131ns           | 3533ns         | 3522ns          | 3499ns    | 108932ns   | 4267ns   |
| Update    64 entities with 3 systems | 14414ns  | 16651ns          | 13922ns        | 14102ns         | 14379ns   | 123669ns   | 14832ns  |
| Update   256 entities with 3 systems | 56833ns  | 65143ns          | 54822ns        | 55162ns         | 56664ns   | 165416ns   | 57278ns  |
| Update   ~1K entities with 3 systems | 222303ns | 254598ns         | 218143ns       | 220602ns        | 224301ns  | 340339ns   | 246044ns |
| Update   ~4K entities with 3 systems | 867155ns | 1049113ns        | 850514ns       | 852281ns        | 866459ns  | 997046ns   | 864552ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 systems | 3ms    | 4ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 systems | 13ms   | 16ms             | 13ms           | 13ms            | 13ms      | 13ms       | 14ms    |
| Update  262K entities with 3 systems | 56ms   | 66ms             | 58ms           | 56ms            | 57ms      | 56ms       | 54ms    |
| Update   ~1M entities with 3 systems | 226ms  | 268ms            | 265ms          | 225ms           | 228ms     | 224ms      | 220ms   |
| Update   ~2M entities with 3 systems | 453ms  | 540ms            | 614ms          | 446ms           | 463ms     | 448ms      | 445ms   |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)




### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 Systems | 3079ns   | 3532ns           | 3071ns         | 3049ns          | 3038ns    | 109686ns   | 3950ns   |
| Update    64 entities with 3 Systems | 13343ns  | 15044ns          | 12928ns        | 13200ns         | 13240ns   | 123189ns   | 13788ns  |
| Update   256 entities with 3 Systems | 56497ns  | 66276ns          | 54816ns        | 55144ns         | 57302ns   | 164310ns   | 55377ns  |
| Update   ~1K entities with 3 Systems | 221343ns | 254158ns         | 213543ns       | 221857ns        | 225112ns  | 333359ns   | 216402ns |
| Update   ~4K entities with 3 Systems | 865816ns | 980152ns         | 838812ns       | 855028ns        | 878029ns  | 990964ns   | 843319ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 4ms        | 3ms     |
| Update  ~65K entities with 3 Systems | 13ms   | 15ms             | 13ms           | 13ms            | 13ms      | 14ms       | 13ms    |
| Update  262K entities with 3 Systems | 58ms   | 65ms             | 57ms           | 55ms            | 56ms      | 55ms       | 54ms    |
| Update   ~1M entities with 3 Systems | 227ms  | 271ms            | 270ms          | 226ms           | 241ms     | 225ms      | 217ms   |
| Update   ~2M entities with 3 Systems | 460ms  | 546ms            | 648ms          | 449ms           | 462ms     | 447ms      | 445ms   |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* Not every entity has all three components, some got removed
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)



### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with two components | 9ns                        | 17ns                      | 9ns                           |
| Iterate over    64 entities with two components | 46ns                       | 82ns                      | 45ns                          |
| Iterate over   256 entities with two components | 146ns                      | 333ns                     | 147ns                         |
| Iterate over   ~1K entities with two components | 546ns                      | 1330ns                    | 548ns                         |
| Iterate over   ~4K entities with two components | 2142ns                     | 4903ns                    | 2136ns                        |

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with two components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with two components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with two components | 4ms                        | 14ms                      | 4ms                           |

**Notes:**
* pre create views/query when possible
* \* EnTT Full-owning group, `registry.group<PositionComponent, VelocityComponent>()`
* \** EnTT Non-owning group, `registry.group(entt::get<<PositionComponent, VelocityComponent>>)`
* \*** EnTT Partial-owning group, `registry.group<PositionComponent>(entt::get<VelocityComponent>)`
* \**** EnTT uses `registry.view` and a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** flecs Frameworks, iterate components via [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.png)

_(lower is better)_

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with three components | 6ns                        | 13ns                      | 6ns                           |
| Iterate over    64 entities with three components | 34ns                       | 51ns                      | 33ns                          |
| Iterate over   256 entities with three components | 145ns                      | 327ns                     | 146ns                         |
| Iterate over   ~1K entities with three components | 542ns                      | 1227ns                    | 540ns                         |
| Iterate over   ~4K entities with three components | 2146ns                     | 4861ns                    | 2173ns                        |

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with three components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with three components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with three components | 4ms                        | 14ms                      | 4ms                           |


**Notes:**
* Not every entity has all three components, some got removed
* pre create views/query when possible
* \* EnTT Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \** EnTT Non-owning group, `registry.group(entt::get<<PositionComponent, VelocityComponent, DataComponent>>)`
* \*** EnTT Partial-owning group, `registry.group<PositionComponent, VelocityComponent>(entt::get<DataComponent>)`
* \**** EnTT uses `registry.view` and a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** flecs Frameworks, iterate components via [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)



## Contributing

I try to implement the ECS-examples as good as possible for each framework, if you have any improvements, feel free to make a PR or open an issue.

You can find the frameworks example(s) in [`src/`](src/) and benchmark [`benchmarks/`](benchmarks/benchmarks/) for more details.  
Also you can write tests for the framework example :)
and add some metadata in [info.json](info.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

### Using [Taskfile](https://taskfile.dev/installation/)

1. `git submodule update --init --recursive`
2. Build: `task build`
3. Run (All) Benchmarks: `task benchmark`
4. Plot Graphs: `task plot:all`

You can now find you benchmarks results in [`reports/`](reports/).

_You need python and some dependencies to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting)_

### ~~Step-by-Step~~

1. Configure and build benchmarks, see [Building Details](doc/README_building.md):
   1. `git submodule update --init --recursive` 
   2. `cmake -S . -B ./build`
   3. `cmake --build ./build`
2. Run benchmark(s), with [`run-benchmarks.sh`](run-benchmarks.sh) or each:
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt` _(console output)_ _(optional)_
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json` _(write json report)_
3. Plot Reports, after generating json reports, see [`plot-results.sh`](plot-results.sh):
   1. `python3 ./scripts/gen-benchmark-report -i ./info.json gen-plot ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate graphs)_
   2. `python3 ./scripts/gen-benchmark-report -i ./info.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate full report)_


## Links and More

* [Dependency Setup](doc/README_dependencies.md)
* [Building Details](doc/README_building.md)
* Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
* [Google benchmark](https://github.com/google/benchmark)
* https://github.com/SanderMertens/ecs-faq
* https://github.com/jslee02/awesome-entity-component-system


### Candidates

#### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: 3.11.1

#### Ginseng by @apples

> Ginseng is an entity-component-system (ECS) library designed for use in games.  
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.  
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev

> A fast, modern C++ Entity Component System

Version: 0.2 (Feb 2022)

#### OpenEcs by @Gronis

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v2.4.8 (Mai 2022)


#### _Deprecated_

I removed [anax](https://github.com/miguelmartin75/anax) and [Artemis-Cpp](https://github.com/matachi/Artemis-Cpp), they are out-of-date and didn't receive any updates in the last time.  
You can still checkout the old versions and branches.
