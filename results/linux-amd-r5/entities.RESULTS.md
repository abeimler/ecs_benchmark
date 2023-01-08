# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

None

None



## Benchmarks

### Create entities

![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     | pico_ecs   |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:-----------|
| Create    16 entities with two Components | 2628ns    | 2748ns   | 10581ns   | 2985ns     | 652407ns  | 593ns      |
| Create    64 entities with two Components | 6082ns    | 4309ns   | 11995ns   | 5983ns     | 665214ns  | 1025ns     |
| Create   256 entities with two Components | 19214ns   | 10152ns  | 16463ns   | 17605ns    | 739886ns  | 2782ns     |
| Create   ~1K entities with two Components | 71351ns   | 32864ns  | 32361ns   | 62070ns    | 896714ns  | 9716ns     |
| Create   ~4K entities with two Components | 278867ns  | 141754ns | 96061ns   | 237707ns   | 1532600ns | 88776ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        |
| Create  ~65K entities with two Components | 4ms       | 2ms    | 3ms       | 4ms        | 14ms    | 1ms        |
| Create  262K entities with two Components | 20ms      | 12ms   | 14ms      | 18ms       | 55ms    | 7ms        |
| Create   ~1M entities with two Components | 83ms      | 48ms   | 49ms      | 72ms       | 208ms   | 23ms       |
| Create   ~2M entities with two Components | 164ms     | 91ms   | 94ms      | 143ms      | 402ms   | 46ms       |


### Create empty entities

![CreateEmptyEntities Plot](img/CreateEmptyEntities.png)

_(lower is better)_

|                               | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Create    16 (empty) entities | 1132ns    | 428ns   | 422ns     | 1734ns     | 374008ns | 480ns      |
| Create    64 (empty) entities | 2519ns    | 572ns   | 769ns     | 3751ns     | 375535ns | 665ns      |
| Create   256 (empty) entities | 7650ns    | 1166ns  | 1749ns    | 11564ns    | 379466ns | 1406ns     |
| Create   ~1K (empty) entities | 27509ns   | 3230ns  | 5099ns    | 37586ns    | 398212ns | 4379ns     |
| Create   ~4K (empty) entities | 105911ns  | 11222ns | 18521ns   | 140453ns   | 473239ns | 19680ns    |

|                               | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Create  ~16K (empty) entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Create  ~65K (empty) entities | 1ms       | 0ms    | 0ms       | 2ms        | 2ms     | 0ms        |
| Create  262K (empty) entities | 6ms       | 0ms    | 2ms       | 8ms        | 7ms     | 1ms        |
| Create   ~1M (empty) entities | 27ms      | 3ms    | 9ms       | 39ms       | 39ms    | 7ms        |
| Create   ~2M (empty) entities | 63ms      | 12ms   | 24ms      | 89ms       | 76ms    | 13ms       |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack one component in    16 entities | 22ns      | 45ns    | 27ns      | 183ns      | 419ns    | 10ns       |
| Unpack one component in    64 entities | 96ns      | 184ns   | 112ns     | 707ns      | 1640ns   | 46ns       |
| Unpack one component in   256 entities | 367ns     | 724ns   | 437ns     | 2720ns     | 6586ns   | 171ns      |
| Unpack one component in   ~1K entities | 1452ns    | 2874ns  | 1748ns    | 10621ns    | 26356ns  | 675ns      |
| Unpack one component in   ~4K entities | 5796ns    | 11562ns | 6948ns    | 44903ns    | 104202ns | 2701ns     |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Unpack one component in  262K entities | 0ms       | 0ms    | 0ms       | 2ms        | 6ms     | 0ms        |
| Unpack one component in   ~1M entities | 1ms       | 3ms    | 1ms       | 11ms       | 26ms    | 0ms        |
| Unpack one component in   ~2M entities | 3ms       | 6ms    | 3ms       | 22ms       | 53ms    | 1ms        |


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:--------|:-----------|
| Get one (const) component in    16 entities | 22ns      | 46ns    | 27ns      | 93ns       | 252ns   | 12ns       |
| Get one (const) component in    64 entities | 95ns      | 190ns   | 112ns     | 359ns      | 988ns   | 55ns       |
| Get one (const) component in   256 entities | 365ns     | 748ns   | 437ns     | 1420ns     | 3947ns  | 211ns      |
| Get one (const) component in   ~1K entities | 1450ns    | 3015ns  | 1751ns    | 5675ns     | 15830ns | 837ns      |
| Get one (const) component in   ~4K entities | 5797ns    | 12041ns | 6990ns    | 22702ns    | 63153ns | 3346ns     |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Get one (const) component in  262K entities | 0ms       | 0ms    | 0ms       | 1ms        | 4ms     | 0ms        |
| Get one (const) component in   ~1M entities | 1ms       | 3ms    | 1ms       | 5ms        | 16ms    | 0ms        |
| Get one (const) component in   ~2M entities | 3ms       | 6ms    | 3ms       | 11ms       | 32ms    | 1ms        |


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack two components in    16 entities | 41ns      | 93ns    | 54ns      | 360ns      | 676ns    | 22ns       |
| Unpack two components in    64 entities | 172ns     | 365ns   | 221ns     | 1023ns     | 2672ns   | 95ns       |
| Unpack two components in   256 entities | 671ns     | 1450ns  | 875ns     | 4090ns     | 10606ns  | 374ns      |
| Unpack two components in   ~1K entities | 2668ns    | 5804ns  | 3488ns    | 16335ns    | 42460ns  | 1483ns     |
| Unpack two components in   ~4K entities | 10674ns   | 23247ns | 13967ns   | 65838ns    | 169089ns | 5910ns     |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 2ms     | 0ms        |
| Unpack two components in  262K entities | 0ms       | 1ms    | 0ms       | 4ms        | 10ms    | 0ms        |
| Unpack two components in   ~1M entities | 2ms       | 6ms    | 3ms       | 18ms       | 43ms    | 1ms        |
| Unpack two components in   ~2M entities | 5ms       | 12ms   | 7ms       | 37ms       | 86ms    | 3ms        |


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack three components in     8 entities | 32ns      | 77ns    | 48ns      | 127ns      | 592ns    | 16ns       |
| Unpack three components in    32 entities | 135ns     | 299ns   | 197ns     | 502ns      | 2347ns   | 70ns       |
| Unpack three components in   128 entities | 524ns     | 1193ns  | 777ns     | 1986ns     | 9363ns   | 272ns      |
| Unpack three components in   512 entities | 2083ns    | 4796ns  | 3099ns    | 7971ns     | 37002ns  | 1076ns     |
| Unpack three components in   ~2K entities | 8293ns    | 19090ns | 12407ns   | 31775ns    | 149878ns | 4306ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Unpack three components in  131K entities | 0ms       | 1ms    | 0ms       | 2ms        | 9ms     | 0ms        |
| Unpack three components in  524K entities | 2ms       | 5ms    | 3ms       | 8ms        | 37ms    | 1ms        |
| Unpack three components in   ~1M entities | 4ms       | 10ms   | 6ms       | 17ms       | 74ms    | 2ms        |


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Remove and Add a Component in    16 entities | 294ns     | 427ns    | 187ns     | 958ns      | 2689ns   | 94ns       |
| Remove and Add a Component in    64 entities | 1170ns    | 1674ns   | 736ns     | 3799ns     | 10589ns  | 362ns      |
| Remove and Add a Component in   256 entities | 4681ns    | 6655ns   | 2937ns    | 15180ns    | 42112ns  | 1427ns     |
| Remove and Add a Component in   ~1K entities | 18717ns   | 26667ns  | 11910ns   | 60647ns    | 170502ns | 5690ns     |
| Remove and Add a Component in   ~4K entities | 75062ns   | 105841ns | 47867ns   | 242589ns   | 683467ns | 23006ns    |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 3ms        | 10ms    | 0ms        |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 15ms       | 43ms    | 1ms        |
| Remove and Add a Component in   ~1M entities | 19ms      | 28ms   | 12ms      | 65ms       | 174ms   | 5ms        |
| Remove and Add a Component in   ~2M entities | 38ms      | 55ms   | 24ms      | 140ms      | 348ms   | 13ms       |


### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Destroy    16 entities with two components | 1451ns    | 1075ns   | 1970ns    | 671ns      | 393841ns | 545ns      |
| Destroy    64 entities with two components | 3464ns    | 2537ns   | 5391ns    | 807ns      | 396080ns | 725ns      |
| Destroy   256 entities with two components | 11681ns   | 8528ns   | 18841ns   | 1287ns     | 402022ns | 1435ns     |
| Destroy   ~1K entities with two components | 45895ns   | 32234ns  | 72359ns   | 3046ns     | 428988ns | 4301ns     |
| Destroy   ~4K entities with two components | 186443ns  | 127482ns | 285900ns  | 9703ns     | 537208ns | 15811ns    |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 0ms        | 0ms     | 0ms        |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 4ms       | 0ms        | 2ms     | 0ms        |
| Destroy  262K entities with two components | 13ms      | 8ms    | 19ms      | 0ms        | 9ms     | 0ms        |
| Destroy   ~1M entities with two components | 58ms      | 35ms   | 77ms      | 4ms        | 41ms    | 5ms        |
| Destroy   ~2M entities with two components | 117ms     | 72ms   | 154ms     | 8ms        | 79ms    | 10ms       |


### Create entities at once

![CreateEntitiesInBulk Plot](img/CreateEntitiesInBulk.png)

_(lower is better)_

|                                                   | EnTT    |
|:--------------------------------------------------|:--------|
| Create    16 entities with two components at once | 2385ns  |
| Create    64 entities with two components at once | 3222ns  |
| Create   256 entities with two components at once | 6342ns  |
| Create   ~1K entities with two components at once | 17935ns |
| Create   ~4K entities with two components at once | 63428ns |

|                                                   | EnTT   |
|:--------------------------------------------------|:-------|
| Create  ~16K entities with two components at once | 0ms    |
| Create  ~65K entities with two components at once | 0ms    |
| Create  262K entities with two components at once | 4ms    |
| Create   ~1M entities with two components at once | 29ms   |
| Create   ~2M entities with two components at once | 63ms   |


### Create empty entities at once

![CreateEmptyEntitiesInBulk Plot](img/CreateEmptyEntitiesInBulk.png)

_(lower is better)_

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create    16 (empty) entities at once | 358ns  |
| Create    64 (empty) entities at once | 373ns  |
| Create   256 (empty) entities at once | 509ns  |
| Create   ~1K (empty) entities at once | 807ns  |
| Create   ~4K (empty) entities at once | 2159ns |

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create  ~16K (empty) entities at once | 0ms    |
| Create  ~65K (empty) entities at once | 0ms    |
| Create  262K (empty) entities at once | 0ms    |
| Create   ~1M (empty) entities at once | 2ms    |
| Create   ~2M (empty) entities at once | 5ms    |


### Destroy entities at once

![DestroyEntitiesInBulk Plot](img/DestroyEntitiesInBulk.png)

_(lower is better)_

|                                                    | EnTT     |
|:---------------------------------------------------|:---------|
| Destroy    16 entities with two components at once | 1097ns   |
| Destroy    64 entities with two components at once | 2580ns   |
| Destroy   256 entities with two components at once | 8552ns   |
| Destroy   ~1K entities with two components at once | 32272ns  |
| Destroy   ~4K entities with two components at once | 128508ns |

|                                                    | EnTT   |
|:---------------------------------------------------|:-------|
| Destroy  ~16K entities with two components at once | 0ms    |
| Destroy  ~65K entities with two components at once | 2ms    |
| Destroy  262K entities with two components at once | 8ms    |
| Destroy   ~1M entities with two components at once | 34ms   |
| Destroy   ~2M entities with two components at once | 72ms   |





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
* **CPU:** 3.47GHz @ 12Cores
* **RAM:** 15.55GB

