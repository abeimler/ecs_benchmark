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

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|
| Create    16 entities with two Components | 2716ns    | 2750ns   | 10472ns   | 2993ns     | 692709ns  |
| Create    64 entities with two Components | 6567ns    | 4352ns   | 11832ns   | 5894ns     | 694854ns  |
| Create   256 entities with two Components | 21436ns   | 10215ns  | 16207ns   | 16732ns    | 743310ns  |
| Create   ~1K entities with two Components | 81265ns   | 32936ns  | 32101ns   | 59557ns    | 851549ns  |
| Create   ~4K entities with two Components | 314925ns  | 141350ns | 96077ns   | 229287ns   | 1454413ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 0ms        | 4ms     |
| Create  ~65K entities with two Components | 5ms       | 2ms    | 3ms       | 4ms        | 14ms    |
| Create  262K entities with two Components | 23ms      | 12ms   | 14ms      | 18ms       | 54ms    |
| Create   ~1M entities with two Components | 92ms      | 48ms   | 49ms      | 72ms       | 202ms   |
| Create   ~2M entities with two Components | 183ms     | 93ms   | 94ms      | 145ms      | 395ms   |


### Create empty entities

![CreateEmptyEntities Plot](img/CreateEmptyEntities.png)

_(lower is better)_

|                               | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Create    16 (empty) entities | 1147ns    | 420ns   | 425ns     | 1697ns     | 377167ns |
| Create    64 (empty) entities | 2566ns    | 573ns   | 753ns     | 3500ns     | 378652ns |
| Create   256 (empty) entities | 7672ns    | 1165ns  | 1749ns    | 10354ns    | 382524ns |
| Create   ~1K (empty) entities | 27451ns   | 3245ns  | 5207ns    | 36024ns    | 398420ns |
| Create   ~4K (empty) entities | 105603ns  | 11248ns | 18666ns   | 138715ns   | 470078ns |

|                               | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Create  ~16K (empty) entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Create  ~65K (empty) entities | 1ms       | 0ms    | 0ms       | 2ms        | 1ms     |
| Create  262K (empty) entities | 6ms       | 0ms    | 2ms       | 9ms        | 7ms     |
| Create   ~1M (empty) entities | 28ms      | 3ms    | 10ms      | 38ms       | 37ms    |
| Create   ~2M (empty) entities | 63ms      | 12ms   | 24ms      | 89ms       | 73ms    |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Unpack one component in    16 entities | 22ns      | 45ns    | 27ns      | 162ns      | 354ns   |
| Unpack one component in    64 entities | 96ns      | 184ns   | 112ns     | 730ns      | 1393ns  |
| Unpack one component in   256 entities | 366ns     | 725ns   | 441ns     | 2752ns     | 5561ns  |
| Unpack one component in   ~1K entities | 1456ns    | 2887ns  | 1763ns    | 10906ns    | 22790ns |
| Unpack one component in   ~4K entities | 5786ns    | 11572ns | 7039ns    | 45466ns    | 91112ns |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack one component in  262K entities | 0ms       | 0ms    | 0ms       | 3ms        | 5ms     |
| Unpack one component in   ~1M entities | 1ms       | 3ms    | 1ms       | 11ms       | 22ms    |
| Unpack one component in   ~2M entities | 3ms       | 6ms    | 3ms       | 25ms       | 45ms    |


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Get one (const) component in    16 entities | 22ns      | 47ns    | 27ns      | 93ns       | 252ns   |
| Get one (const) component in    64 entities | 96ns      | 190ns   | 112ns     | 360ns      | 988ns   |
| Get one (const) component in   256 entities | 366ns     | 750ns   | 444ns     | 1424ns     | 3929ns  |
| Get one (const) component in   ~1K entities | 1454ns    | 2985ns  | 1748ns    | 5670ns     | 15717ns |
| Get one (const) component in   ~4K entities | 5789ns    | 11989ns | 6968ns    | 22700ns    | 62789ns |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Get one (const) component in  262K entities | 0ms       | 0ms    | 0ms       | 1ms        | 4ms     |
| Get one (const) component in   ~1M entities | 1ms       | 3ms    | 1ms       | 5ms        | 16ms    |
| Get one (const) component in   ~2M entities | 3ms       | 6ms    | 3ms       | 11ms       | 32ms    |


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack two components in    16 entities | 41ns      | 93ns    | 54ns      | 257ns      | 618ns    |
| Unpack two components in    64 entities | 172ns     | 365ns   | 222ns     | 1022ns     | 2471ns   |
| Unpack two components in   256 entities | 672ns     | 1457ns  | 877ns     | 4090ns     | 9818ns   |
| Unpack two components in   ~1K entities | 2674ns    | 5809ns  | 3500ns    | 16350ns    | 39301ns  |
| Unpack two components in   ~4K entities | 10707ns   | 23174ns | 14009ns   | 65442ns    | 157353ns |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 2ms     |
| Unpack two components in  262K entities | 0ms       | 1ms    | 0ms       | 4ms        | 10ms    |
| Unpack two components in   ~1M entities | 2ms       | 6ms    | 3ms       | 17ms       | 40ms    |
| Unpack two components in   ~2M entities | 5ms       | 12ms   | 7ms       | 34ms       | 80ms    |


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack three components in     8 entities | 33ns      | 73ns    | 47ns      | 129ns      | 505ns    |
| Unpack three components in    32 entities | 143ns     | 296ns   | 191ns     | 522ns      | 1971ns   |
| Unpack three components in   128 entities | 538ns     | 1177ns  | 751ns     | 2018ns     | 7909ns   |
| Unpack three components in   512 entities | 2133ns    | 4700ns  | 2986ns    | 8071ns     | 31638ns  |
| Unpack three components in   ~2K entities | 8523ns    | 18743ns | 12002ns   | 32199ns    | 125618ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack three components in  131K entities | 0ms       | 1ms    | 0ms       | 2ms        | 7ms     |
| Unpack three components in  524K entities | 2ms       | 5ms    | 3ms       | 8ms        | 31ms    |
| Unpack three components in   ~1M entities | 4ms       | 10ms   | 6ms       | 17ms       | 62ms    |


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Remove and Add a Component in    16 entities | 300ns     | 426ns    | 208ns     | 880ns      | 2700ns   |
| Remove and Add a Component in    64 entities | 1176ns    | 1684ns   | 737ns     | 3463ns     | 10838ns  |
| Remove and Add a Component in   256 entities | 4691ns    | 6692ns   | 2947ns    | 13810ns    | 42652ns  |
| Remove and Add a Component in   ~1K entities | 18746ns   | 26836ns  | 12003ns   | 56276ns    | 170747ns |
| Remove and Add a Component in   ~4K entities | 74966ns   | 107751ns | 52925ns   | 221859ns   | 681861ns |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 3ms        | 10ms    |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 14ms       | 43ms    |
| Remove and Add a Component in   ~1M entities | 19ms      | 27ms   | 12ms      | 64ms       | 175ms   |
| Remove and Add a Component in   ~2M entities | 38ms      | 55ms   | 27ms      | 136ms      | 347ms   |


### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Destroy    16 entities with two components | 1416ns    | 1075ns   | 1978ns    | 682ns      | 396515ns |
| Destroy    64 entities with two components | 3421ns    | 2540ns   | 5515ns    | 819ns      | 398124ns |
| Destroy   256 entities with two components | 11662ns   | 8462ns   | 19184ns   | 1294ns     | 404232ns |
| Destroy   ~1K entities with two components | 46007ns   | 32197ns  | 73215ns   | 3061ns     | 428263ns |
| Destroy   ~4K entities with two components | 187868ns  | 127435ns | 288918ns  | 9721ns     | 518695ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 0ms        | 0ms     |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 4ms       | 0ms        | 2ms     |
| Destroy  262K entities with two components | 13ms      | 8ms    | 19ms      | 0ms        | 8ms     |
| Destroy   ~1M entities with two components | 58ms      | 35ms   | 78ms      | 4ms        | 34ms    |
| Destroy   ~2M entities with two components | 119ms     | 74ms   | 157ms     | 8ms        | 70ms    |


### Create entities at once

![CreateEntitiesInBulk Plot](img/CreateEntitiesInBulk.png)

_(lower is better)_

|                                                   | EnTT    |
|:--------------------------------------------------|:--------|
| Create    16 entities with two components at once | 2409ns  |
| Create    64 entities with two components at once | 3246ns  |
| Create   256 entities with two components at once | 6375ns  |
| Create   ~1K entities with two components at once | 17989ns |
| Create   ~4K entities with two components at once | 64166ns |

|                                                   | EnTT   |
|:--------------------------------------------------|:-------|
| Create  ~16K entities with two components at once | 0ms    |
| Create  ~65K entities with two components at once | 0ms    |
| Create  262K entities with two components at once | 4ms    |
| Create   ~1M entities with two components at once | 29ms   |
| Create   ~2M entities with two components at once | 64ms   |


### Create empty entities at once

![CreateEmptyEntitiesInBulk Plot](img/CreateEmptyEntitiesInBulk.png)

_(lower is better)_

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create    16 (empty) entities at once | 350ns  |
| Create    64 (empty) entities at once | 369ns  |
| Create   256 (empty) entities at once | 502ns  |
| Create   ~1K (empty) entities at once | 802ns  |
| Create   ~4K (empty) entities at once | 2155ns |

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
| Destroy    16 entities with two components at once | 1088ns   |
| Destroy    64 entities with two components at once | 2576ns   |
| Destroy   256 entities with two components at once | 8540ns   |
| Destroy   ~1K entities with two components at once | 32302ns  |
| Destroy   ~4K entities with two components at once | 128371ns |

|                                                    | EnTT   |
|:---------------------------------------------------|:-------|
| Destroy  ~16K entities with two components at once | 0ms    |
| Destroy  ~65K entities with two components at once | 2ms    |
| Destroy  262K entities with two components at once | 8ms    |
| Destroy   ~1M entities with two components at once | 34ms   |
| Destroy   ~2M entities with two components at once | 73ms   |





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




### Environment

* **OS:** Linux
* **CPU:** 3.12GHz @ 12Cores
* **RAM:** 15.55GB

