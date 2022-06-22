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

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:----------|
| Create    16 entities with two Components | 7334ns    | 6637ns   | 506880ns  | 7620ns     | 2749ns    | 1298694ns |
| Create    64 entities with two Components | 17912ns   | 9854ns   | 442353ns  | 15121ns    | 7682ns    | 1392403ns |
| Create   256 entities with two Components | 56614ns   | 20746ns  | 464017ns  | 39419ns    | 28281ns   | 1383772ns |
| Create   ~1K entities with two Components | 208817ns  | 60887ns  | 511284ns  | 137718ns   | 109591ns  | 1815506ns |
| Create   ~4K entities with two Components | 813817ns  | 224397ns | 683852ns  | 531346ns   | 436271ns  | 3552398ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Create  ~16K entities with two Components | 3ms       | 0ms    | 1ms       | 2ms        | 1ms       | 10ms    |
| Create  ~65K entities with two Components | 13ms      | 4ms    | 5ms       | 9ms        | 7ms       | 36ms    |
| Create  262K entities with two Components | 55ms      | 19ms   | 29ms      | 37ms       | 29ms      | 144ms   |
| Create   ~1M entities with two Components | 219ms     | 78ms   | 120ms     | 159ms      | 121ms     | 560ms   |
| Create   ~2M entities with two Components | 442ms     | 169ms  | 254ms     | 314ms      | 241ms     | 1133ms  |


### Create empty entities

![CreateEmptyEntities Plot](img/CreateEmptyEntities.png)

_(lower is better)_

|                               | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:------------------------------|:----------|:--------|:----------|:-----------|:----------|:----------|
| Create    16 (empty) entities | 3309ns    | 777ns   | 937ns     | 4641ns     | 894ns     | 864754ns  |
| Create    64 (empty) entities | 7568ns    | 1196ns  | 2072ns    | 10002ns    | 1882ns    | 853338ns  |
| Create   256 (empty) entities | 21634ns   | 2005ns  | 4853ns    | 27675ns    | 6462ns    | 859768ns  |
| Create   ~1K (empty) entities | 76827ns   | 4559ns  | 15074ns   | 94676ns    | 23415ns   | 975845ns  |
| Create   ~4K (empty) entities | 289195ns  | 15106ns | 61711ns   | 369096ns   | 89614ns   | 1239889ns |

|                               | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Create  ~16K (empty) entities | 1ms       | 0ms    | 0ms       | 1ms        | 0ms       | 2ms     |
| Create  ~65K (empty) entities | 4ms       | 0ms    | 1ms       | 6ms        | 1ms       | 7ms     |
| Create  262K (empty) entities | 19ms      | 1ms    | 9ms       | 25ms       | 7ms       | 29ms    |
| Create   ~1M (empty) entities | 83ms      | 8ms    | 37ms      | 101ms      | 28ms      | 117ms   |
| Create   ~2M (empty) entities | 167ms     | 18ms   | 77ms      | 206ms      | 60ms      | 234ms   |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs    |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:----------|:---------|
| Unpack one component in    16 entities | 76ns      | 211ns   | 71ns      | 292ns      | 276ns     | 1568ns   |
| Unpack one component in    64 entities | 339ns     | 908ns   | 264ns     | 1202ns     | 1081ns    | 6169ns   |
| Unpack one component in   256 entities | 1286ns    | 3621ns  | 1023ns    | 4418ns     | 4274ns    | 24661ns  |
| Unpack one component in   ~1K entities | 5011ns    | 14322ns | 4112ns    | 18166ns    | 17051ns   | 98821ns  |
| Unpack one component in   ~4K entities | 20487ns   | 58685ns | 17091ns   | 78706ns    | 69600ns   | 408034ns |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms       | 1ms     |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 1ms       | 6ms     |
| Unpack one component in  262K entities | 1ms       | 3ms    | 1ms       | 4ms        | 4ms       | 25ms    |
| Unpack one component in   ~1M entities | 5ms       | 15ms   | 5ms       | 18ms       | 18ms      | 103ms   |
| Unpack one component in   ~2M entities | 11ms      | 30ms   | 9ms       | 41ms       | 36ms      | 204ms   |


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs    |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:----------|:---------|
| Get one (const) component in    16 entities | 88ns      | 244ns   | 72ns      | 163ns      | 274ns     | 1232ns   |
| Get one (const) component in    64 entities | 335ns     | 847ns   | 272ns     | 623ns      | 1084ns    | 5021ns   |
| Get one (const) component in   256 entities | 1306ns    | 3501ns  | 1051ns    | 2472ns     | 5150ns    | 19643ns  |
| Get one (const) component in   ~1K entities | 5226ns    | 13322ns | 4214ns    | 9863ns     | 20562ns   | 78170ns  |
| Get one (const) component in   ~4K entities | 21479ns   | 59271ns | 17074ns   | 39641ns    | 77021ns   | 314130ns |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms       | 1ms     |
| Get one (const) component in  ~65K entities | 0ms       | 1ms    | 0ms       | 0ms        | 1ms       | 5ms     |
| Get one (const) component in  262K entities | 1ms       | 3ms    | 1ms       | 2ms        | 4ms       | 20ms    |
| Get one (const) component in   ~1M entities | 6ms       | 15ms   | 5ms       | 10ms       | 18ms      | 85ms    |
| Get one (const) component in   ~2M entities | 11ms      | 31ms   | 10ms      | 21ms       | 37ms      | 168ms   |


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT     | Ginseng   | mustache   | OpenEcs   | Flecs    |
|:----------------------------------------|:----------|:---------|:----------|:-----------|:----------|:---------|
| Unpack two components in    16 entities | 163ns     | 421ns    | 150ns     | 455ns      | 548ns     | 2808ns   |
| Unpack two components in    64 entities | 625ns     | 1512ns   | 586ns     | 1800ns     | 2200ns    | 11043ns  |
| Unpack two components in   256 entities | 2455ns    | 6441ns   | 2318ns    | 7160ns     | 8765ns    | 43869ns  |
| Unpack two components in   ~1K entities | 9987ns    | 25461ns  | 9303ns    | 28543ns    | 35163ns   | 182412ns |
| Unpack two components in   ~4K entities | 39444ns   | 100386ns | 37461ns   | 115202ns   | 140518ns  | 698047ns |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms       | 2ms     |
| Unpack two components in  ~65K entities | 0ms       | 1ms    | 0ms       | 1ms        | 2ms       | 11ms    |
| Unpack two components in  262K entities | 2ms       | 6ms    | 2ms       | 7ms        | 9ms       | 45ms    |
| Unpack two components in   ~1M entities | 10ms      | 27ms   | 10ms      | 30ms       | 36ms      | 181ms   |
| Unpack two components in   ~2M entities | 21ms      | 55ms   | 21ms      | 58ms       | 73ms      | 382ms   |


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs    |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:----------|:---------|
| Unpack three components in     8 entities | 131ns     | 298ns   | 126ns     | 243ns      | 438ns     | 2098ns   |
| Unpack three components in    32 entities | 498ns     | 1173ns  | 471ns     | 940ns      | 1848ns    | 8501ns   |
| Unpack three components in   128 entities | 1967ns    | 4649ns  | 1860ns    | 3727ns     | 7048ns    | 33568ns  |
| Unpack three components in   512 entities | 7824ns    | 18683ns | 7291ns    | 14828ns    | 28076ns   | 137735ns |
| Unpack three components in   ~2K entities | 32629ns   | 74923ns | 28680ns   | 60304ns    | 113365ns  | 552611ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms       | 2ms     |
| Unpack three components in  ~32K entities | 0ms       | 1ms    | 0ms       | 0ms        | 1ms       | 8ms     |
| Unpack three components in  131K entities | 2ms       | 4ms    | 2ms       | 3ms        | 7ms       | 35ms    |
| Unpack three components in  524K entities | 8ms       | 23ms   | 8ms       | 15ms       | 29ms      | 145ms   |
| Unpack three components in   ~1M entities | 17ms      | 49ms   | 16ms      | 31ms       | 60ms      | 285ms   |


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:----------|
| Remove and Add a Component in    16 entities | 1060ns    | 1540ns   | 364ns     | 1813ns     | 668ns     | 7891ns    |
| Remove and Add a Component in    64 entities | 4322ns    | 6095ns   | 1439ns    | 7300ns     | 2627ns    | 32021ns   |
| Remove and Add a Component in   256 entities | 17334ns   | 24417ns  | 5668ns    | 30038ns    | 10552ns   | 129837ns  |
| Remove and Add a Component in   ~1K entities | 79685ns   | 97908ns  | 23162ns   | 117480ns   | 42158ns   | 472762ns  |
| Remove and Add a Component in   ~4K entities | 291533ns  | 390530ns | 90378ns   | 462977ns   | 173686ns  | 1974421ns |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Remove and Add a Component in  ~16K entities | 1ms       | 1ms    | 0ms       | 1ms        | 0ms       | 7ms     |
| Remove and Add a Component in  ~65K entities | 4ms       | 6ms    | 1ms       | 7ms        | 2ms       | 31ms    |
| Remove and Add a Component in  262K entities | 17ms      | 25ms   | 6ms       | 30ms       | 10ms      | 127ms   |
| Remove and Add a Component in   ~1M entities | 72ms      | 102ms  | 24ms      | 133ms      | 44ms      | 512ms   |
| Remove and Add a Component in   ~2M entities | 145ms     | 206ms  | 50ms      | 293ms      | 88ms      | 1024ms  |


### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:----------|
| Destroy    16 entities with two components | 3847ns    | 2923ns   | 221738ns  | 1218ns     | 1880ns    | 822565ns  |
| Destroy    64 entities with two components | 9032ns    | 9138ns   | 226580ns  | 1440ns     | 3790ns    | 856148ns  |
| Destroy   256 entities with two components | 29627ns   | 33553ns  | 244415ns  | 2107ns     | 10359ns   | 875063ns  |
| Destroy   ~1K entities with two components | 114291ns  | 132560ns | 316049ns  | 4675ns     | 35715ns   | 992980ns  |
| Destroy   ~4K entities with two components | 459018ns  | 528652ns | 584014ns  | 14733ns    | 135895ns  | 1306428ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Destroy  ~16K entities with two components | 1ms       | 2ms    | 1ms       | 0ms        | 0ms       | 2ms     |
| Destroy  ~65K entities with two components | 7ms       | 8ms    | 6ms       | 0ms        | 2ms       | 7ms     |
| Destroy  262K entities with two components | 32ms      | 34ms   | 30ms      | 1ms        | 11ms      | 26ms    |
| Destroy   ~1M entities with two components | 136ms     | 139ms  | 124ms     | 6ms        | 46ms      | 99ms    |
| Destroy   ~2M entities with two components | 281ms     | 281ms  | 247ms     | 13ms       | 92ms      | 199ms   |


### Create entities at once

![CreateEntitiesInBulk Plot](img/CreateEntitiesInBulk.png)

_(lower is better)_

|                                                   | EnTT     | OpenEcs   |
|:--------------------------------------------------|:---------|:----------|
| Create    16 entities with two components at once | 5921ns   | 2753ns    |
| Create    64 entities with two components at once | 7919ns   | 7552ns    |
| Create   256 entities with two components at once | 13066ns  | 25560ns   |
| Create   ~1K entities with two components at once | 31928ns  | 96009ns   |
| Create   ~4K entities with two components at once | 110199ns | 387629ns  |

|                                                   | EnTT   | OpenEcs   |
|:--------------------------------------------------|:-------|:----------|
| Create  ~16K entities with two components at once | 0ms    | 1ms       |
| Create  ~65K entities with two components at once | 1ms    | 6ms       |
| Create  262K entities with two components at once | 9ms    | 25ms      |
| Create   ~1M entities with two components at once | 43ms   | 108ms     |
| Create   ~2M entities with two components at once | 96ms   | 210ms     |


### Create empty entities at once

![CreateEmptyEntitiesInBulk Plot](img/CreateEmptyEntitiesInBulk.png)

_(lower is better)_

|                                       | EnTT   | OpenEcs   |
|:--------------------------------------|:-------|:----------|
| Create    16 (empty) entities at once | 316ns  | 1018ns    |
| Create    64 (empty) entities at once | 375ns  | 1413ns    |
| Create   256 (empty) entities at once | 534ns  | 4151ns    |
| Create   ~1K (empty) entities at once | 1201ns | 13235ns   |
| Create   ~4K (empty) entities at once | 4905ns | 46813ns   |

|                                       | EnTT   | OpenEcs   |
|:--------------------------------------|:-------|:----------|
| Create  ~16K (empty) entities at once | 0ms    | 0ms       |
| Create  ~65K (empty) entities at once | 0ms    | 0ms       |
| Create  262K (empty) entities at once | 1ms    | 4ms       |
| Create   ~1M (empty) entities at once | 5ms    | 16ms      |
| Create   ~2M (empty) entities at once | 10ms   | 32ms      |


### Destroy entities at once

![DestroyEntitiesInBulk Plot](img/DestroyEntitiesInBulk.png)

_(lower is better)_

|                                                    | EnTT     |
|:---------------------------------------------------|:---------|
| Destroy    16 entities with two components at once | 2907ns   |
| Destroy    64 entities with two components at once | 9013ns   |
| Destroy   256 entities with two components at once | 33819ns  |
| Destroy   ~1K entities with two components at once | 130385ns |
| Destroy   ~4K entities with two components at once | 520442ns |

|                                                    | EnTT   |
|:---------------------------------------------------|:-------|
| Destroy  ~16K entities with two components at once | 2ms    |
| Destroy  ~65K entities with two components at once | 8ms    |
| Destroy  262K entities with two components at once | 33ms   |
| Destroy   ~1M entities with two components at once | 135ms  |
| Destroy   ~2M entities with two components at once | 277ms  |





### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: 3.10.1

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.

The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.

Any function-like object can be used as a system. The function's parameters are used to determine the required components.

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




### Environment

* **OS:** Windows 10
* **CPU:** 2.30GHz @ 8Cores
* **RAM:** 16GB

