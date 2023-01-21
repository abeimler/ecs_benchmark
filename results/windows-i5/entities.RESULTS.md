# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is faster)_

None

None



## Benchmarks

### Create No entities

![CreateNoEntities Plot](img/CreateNoEntities.svg)

_(lower is better)_

|                    | EntityX   | EnTT   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------|:----------|:-------|:----------|:-----------|:---------|:-----------|
| Create No entities | 200ns     | 189ns  | 128ns     | 309ns      | 548466ns | 403ns      |




### Create empty entities

![CreateEmptyEntities Plot](img/CreateEmptyEntities.svg)

_(lower is better)_

|                               | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Create    16 (empty) entities | 2994ns    | 745ns   | 731ns     | 3421ns     | 569963ns | 405ns      |
| Create    64 (empty) entities | 6574ns    | 1073ns  | 1512ns    | 6909ns     | 630482ns | 550ns      |
| Create   256 (empty) entities | 18362ns   | 1713ns  | 3347ns    | 19690ns    | 582151ns | 871ns      |
| Create   ~1K (empty) entities | 63550ns   | 3012ns  | 9453ns    | 59559ns    | 601825ns | 2341ns     |
| Create   ~4K (empty) entities | 240324ns  | 15792ns | 74454ns   | 266045ns   | 680091ns | 21218ns    |

|                               | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Create  ~16K (empty) entities | 0ms       | 0ms    | 0ms       | 1ms        | 1ms     | 0ms        |
| Create  ~65K (empty) entities | 4ms       | 0ms    | 1ms       | 4ms        | 2ms     | 0ms        |
| Create  262K (empty) entities | 17ms      | 1ms    | 8ms       | 19ms       | 10ms    | 2ms        |
| Create   ~1M (empty) entities | 69ms      | 7ms    | 30ms      | 76ms       | 42ms    | 15ms       |
| Create   ~2M (empty) entities | 150ms     | 16ms   | 69ms      | 163ms      | 86ms    | 25ms       |


### Get No component from Entity

![UnpackNoComponent Plot](img/UnpackNoComponent.svg)

_(lower is better)_

|                                    | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-----------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Get No component in    16 entities | 16ns      | 70ns    | 63ns      | 16ns       | 534ns    | 16ns       |
| Get No component in    64 entities | 71ns      | 276ns   | 215ns     | 72ns       | 2203ns   | 71ns       |
| Get No component in   256 entities | 265ns     | 986ns   | 836ns     | 263ns      | 8572ns   | 264ns      |
| Get No component in   ~1K entities | 1060ns    | 4196ns  | 3350ns    | 1049ns     | 35037ns  | 1036ns     |
| Get No component in   ~4K entities | 4119ns    | 17230ns | 12490ns   | 4114ns     | 157609ns | 4223ns     |

|                                    | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-----------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Get No component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Get No component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Get No component in  262K entities | 0ms       | 1ms    | 1ms       | 0ms        | 9ms     | 0ms        |
| Get No component in   ~1M entities | 1ms       | 4ms    | 4ms       | 1ms        | 41ms    | 1ms        |
| Get No component in   ~2M entities | 2ms       | 8ms    | 8ms       | 2ms        | 94ms    | 2ms        |


### Create entities

![CreateEntities Plot](img/CreateEntities.svg)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     | pico_ecs   |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:-----------|
| Create    16 entities with two Components | 6332ns    | 6140ns   | 294456ns  | 6019ns     | 629461ns  | 610ns      |
| Create    64 entities with two Components | 14767ns   | 8871ns   | 296079ns  | 11233ns    | 634549ns  | 1237ns     |
| Create   256 entities with two Components | 48038ns   | 16905ns  | 305231ns  | 27840ns    | 670007ns  | 3848ns     |
| Create   ~1K entities with two Components | 176130ns  | 52097ns  | 333464ns  | 87853ns    | 798922ns  | 14326ns    |
| Create   ~4K entities with two Components | 698756ns  | 191650ns | 486290ns  | 344973ns   | 1333329ns | 74707ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Create  ~16K entities with two Components | 2ms       | 0ms    | 0ms       | 1ms        | 3ms     | 0ms        |
| Create  ~65K entities with two Components | 11ms      | 3ms    | 5ms       | 5ms        | 12ms    | 1ms        |
| Create  262K entities with two Components | 45ms      | 15ms   | 23ms      | 25ms       | 54ms    | 8ms        |
| Create   ~1M entities with two Components | 186ms     | 67ms   | 99ms      | 104ms      | 217ms   | 46ms       |
| Create   ~2M entities with two Components | 383ms     | 146ms  | 208ms     | 210ms      | 429ms   | 81ms       |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack one component in    16 entities | 82ns      | 69ns    | 26ns      | 204ns      | 531ns    | 21ns       |
| Unpack one component in    64 entities | 308ns     | 250ns   | 108ns     | 789ns      | 2259ns   | 93ns       |
| Unpack one component in   256 entities | 1236ns    | 999ns   | 412ns     | 2898ns     | 8737ns   | 360ns      |
| Unpack one component in   ~1K entities | 4988ns    | 4307ns  | 1629ns    | 12655ns    | 34473ns  | 1322ns     |
| Unpack one component in   ~4K entities | 19813ns   | 16222ns | 6718ns    | 50677ns    | 142606ns | 5508ns     |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Unpack one component in  262K entities | 1ms       | 1ms    | 0ms       | 3ms        | 9ms     | 0ms        |
| Unpack one component in   ~1M entities | 5ms       | 4ms    | 2ms       | 13ms       | 38ms    | 1ms        |
| Unpack one component in   ~2M entities | 11ms      | 9ms    | 4ms       | 26ms       | 76ms    | 2ms        |


### Get component from No Entity

![UnpackOneComponentNoEntities Plot](img/UnpackOneComponentNoEntities.svg)

_(lower is better)_

|                                     | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack No entities (empty entities) | 0ns       | 0ns    | 0ns       | 0ns        | 0ns     | 0ns        |




### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.svg)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:--------|:-----------|
| Get one (const) component in    16 entities | 54ns      | 69ns    | 26ns      | 152ns      | 326ns   | 21ns       |
| Get one (const) component in    64 entities | 219ns     | 255ns   | 109ns     | 561ns      | 1287ns  | 92ns       |
| Get one (const) component in   256 entities | 851ns     | 993ns   | 412ns     | 2231ns     | 5218ns  | 342ns      |
| Get one (const) component in   ~1K entities | 3199ns    | 4038ns  | 1711ns    | 8829ns     | 20393ns | 1394ns     |
| Get one (const) component in   ~4K entities | 13652ns   | 16461ns | 6867ns    | 36455ns    | 83213ns | 5426ns     |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Get one (const) component in  262K entities | 0ms       | 1ms    | 0ms       | 2ms        | 5ms     | 0ms        |
| Get one (const) component in   ~1M entities | 3ms       | 4ms    | 2ms       | 9ms        | 22ms    | 1ms        |
| Get one (const) component in   ~2M entities | 7ms       | 9ms    | 4ms       | 19ms       | 45ms    | 2ms        |


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack two components in    16 entities | 121ns     | 122ns   | 73ns      | 343ns      | 897ns    | 48ns       |
| Unpack two components in    64 entities | 433ns     | 473ns   | 267ns     | 1314ns     | 3555ns   | 197ns      |
| Unpack two components in   256 entities | 1796ns    | 1837ns  | 1063ns    | 5264ns     | 14761ns  | 781ns      |
| Unpack two components in   ~1K entities | 7289ns    | 7176ns  | 3917ns    | 19389ns    | 57018ns  | 2983ns     |
| Unpack two components in   ~4K entities | 28279ns   | 29473ns | 16615ns   | 85540ns    | 240255ns | 12652ns    |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 3ms     | 0ms        |
| Unpack two components in  262K entities | 1ms       | 1ms    | 1ms       | 4ms        | 14ms    | 0ms        |
| Unpack two components in   ~1M entities | 8ms       | 7ms    | 4ms       | 21ms       | 60ms    | 3ms        |
| Unpack two components in   ~2M entities | 15ms      | 15ms   | 9ms       | 43ms       | 120ms   | 6ms        |


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack three components in     8 entities | 97ns      | 99ns    | 67ns      | 176ns      | 714ns    | 27ns       |
| Unpack three components in    32 entities | 374ns     | 372ns   | 252ns     | 691ns      | 2880ns   | 113ns      |
| Unpack three components in   128 entities | 1395ns    | 1453ns  | 913ns     | 2776ns     | 11279ns  | 429ns      |
| Unpack three components in   512 entities | 5766ns    | 6432ns  | 4000ns    | 10938ns    | 45460ns  | 1696ns     |
| Unpack three components in   ~2K entities | 22811ns   | 24565ns | 15885ns   | 44053ns    | 186900ns | 6751ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 1ms       | 2ms        | 13ms    | 0ms        |
| Unpack three components in  524K entities | 5ms       | 7ms    | 5ms       | 11ms       | 54ms    | 2ms        |
| Unpack three components in   ~1M entities | 12ms      | 14ms   | 10ms      | 23ms       | 96ms    | 3ms        |


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.svg)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Remove and Add a Component in    16 entities | 826ns     | 1091ns   | 269ns     | 1317ns     | 2724ns   | 150ns      |
| Remove and Add a Component in    64 entities | 3205ns    | 4438ns   | 1082ns    | 5457ns     | 10871ns  | 588ns      |
| Remove and Add a Component in   256 entities | 13528ns   | 17229ns  | 3859ns    | 23570ns    | 41838ns  | 2303ns     |
| Remove and Add a Component in   ~1K entities | 53172ns   | 65571ns  | 15717ns   | 93673ns    | 174211ns | 9186ns     |
| Remove and Add a Component in   ~4K entities | 198787ns  | 275503ns | 69097ns   | 351162ns   | 705643ns | 36470ns    |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Remove and Add a Component in  ~16K entities | 0ms       | 1ms    | 0ms       | 1ms        | 2ms     | 0ms        |
| Remove and Add a Component in  ~65K entities | 3ms       | 4ms    | 1ms       | 5ms        | 11ms    | 0ms        |
| Remove and Add a Component in  262K entities | 13ms      | 18ms   | 4ms       | 23ms       | 45ms    | 2ms        |
| Remove and Add a Component in   ~1M entities | 54ms      | 74ms   | 18ms      | 91ms       | 179ms   | 11ms       |
| Remove and Add a Component in   ~2M entities | 106ms     | 146ms  | 38ms      | 221ms      | 358ms   | 19ms       |


### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.svg)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Destroy    16 entities with two components | 2905ns    | 2259ns   | 141561ns  | 1084ns     | 561675ns | 462ns      |
| Destroy    64 entities with two components | 7243ns    | 6947ns   | 146072ns  | 1335ns     | 561931ns | 618ns      |
| Destroy   256 entities with two components | 24654ns   | 25264ns  | 164814ns  | 2357ns     | 577538ns | 1201ns     |
| Destroy   ~1K entities with two components | 92630ns   | 104998ns | 241931ns  | 6291ns     | 589736ns | 3575ns     |
| Destroy   ~4K entities with two components | 374003ns  | 414174ns | 555558ns  | 22097ns    | 695424ns | 15331ns    |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Destroy  ~16K entities with two components | 1ms       | 1ms    | 1ms       | 0ms        | 1ms     | 0ms        |
| Destroy  ~65K entities with two components | 6ms       | 6ms    | 7ms       | 0ms        | 3ms     | 0ms        |
| Destroy  262K entities with two components | 27ms      | 27ms   | 32ms      | 2ms        | 11ms    | 1ms        |
| Destroy   ~1M entities with two components | 111ms     | 111ms  | 126ms     | 9ms        | 45ms    | 8ms        |
| Destroy   ~2M entities with two components | 229ms     | 222ms  | 251ms     | 17ms       | 91ms    | 15ms       |


### Create entities at once

![CreateEntitiesInBulk Plot](img/CreateEntitiesInBulk.svg)

_(lower is better)_

|                                                   | EnTT     |
|:--------------------------------------------------|:---------|
| Create    16 entities with two components at once | 5662ns   |
| Create    64 entities with two components at once | 7660ns   |
| Create   256 entities with two components at once | 12789ns  |
| Create   ~1K entities with two components at once | 31635ns  |
| Create   ~4K entities with two components at once | 111550ns |

|                                                   | EnTT   |
|:--------------------------------------------------|:-------|
| Create  ~16K entities with two components at once | 0ms    |
| Create  ~65K entities with two components at once | 1ms    |
| Create  262K entities with two components at once | 9ms    |
| Create   ~1M entities with two components at once | 42ms   |
| Create   ~2M entities with two components at once | 95ms   |


### Create empty entities at once

![CreateEmptyEntitiesInBulk Plot](img/CreateEmptyEntitiesInBulk.svg)

_(lower is better)_

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create    16 (empty) entities at once | 304ns  |
| Create    64 (empty) entities at once | 522ns  |
| Create   256 (empty) entities at once | 749ns  |
| Create   ~1K (empty) entities at once | 1819ns |
| Create   ~4K (empty) entities at once | 7267ns |

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create  ~16K (empty) entities at once | 0ms    |
| Create  ~65K (empty) entities at once | 0ms    |
| Create  262K (empty) entities at once | 1ms    |
| Create   ~1M (empty) entities at once | 5ms    |
| Create   ~2M (empty) entities at once | 11ms   |


### Destroy entities at once

![DestroyEntitiesInBulk Plot](img/DestroyEntitiesInBulk.svg)

_(lower is better)_

|                                                    | EnTT     |
|:---------------------------------------------------|:---------|
| Destroy    16 entities with two components at once | 2946ns   |
| Destroy    64 entities with two components at once | 8821ns   |
| Destroy   256 entities with two components at once | 32602ns  |
| Destroy   ~1K entities with two components at once | 130830ns |
| Destroy   ~4K entities with two components at once | 507933ns |

|                                                    | EnTT   |
|:---------------------------------------------------|:-------|
| Destroy  ~16K entities with two components at once | 2ms    |
| Destroy  ~65K entities with two components at once | 7ms    |
| Destroy  262K entities with two components at once | 33ms   |
| Destroy   ~1M entities with two components at once | 134ms  |
| Destroy   ~2M entities with two components at once | 268ms  |





### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: v3.11.1

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.

The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.

Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Aug 2022)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.1.3

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: v2.0.0




### Environment

* **OS:** Linux
* **CPU:** 2.32GHz @ 8Cores
* **RAM:** 7.63GB

