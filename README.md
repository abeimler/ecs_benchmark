# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/MacOS/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/Windows/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/Ubuntu/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![codecov](https://codecov.io/gh/abeimler/ecs_benchmark/branch/master/graph/badge.svg)](https://codecov.io/gh/abeimler/ecs_benchmark)
[![CodeQL](https://github.com/abeimler/ecs_benchmark/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions/workflows/codeql-analysis.yml)
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

### Update systems (3 systems with mixed entities)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group) | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs         |
|:-------------------------------------|:----------|:----------|:-----------------|:-------------|:----------------|:----------|:-----------|:----------|:--------------|
| Update    16 entities with 3 Systems | 9561ns    | 8089ns    | 9140ns           | **7016ns**   | 7775ns          | 7756ns    | 88893ns    | 9801ns    | 10002ns       |
| Update    64 entities with 3 Systems | 39776ns   | 33367ns   | 39097ns          | **28283ns**  | 32176ns         | 32392ns   | 117110ns   | 40011ns   | 31996ns       |
| Update   256 entities with 3 Systems | 172841ns  | 144813ns  | 169627ns         | **124698ns** | 139788ns        | 141888ns  | 217666ns   | 176447ns  | 127142ns      |
| Update   ~1K entities with 3 Systems | 696880ns  | 570857ns  | 670592ns         | 503420ns     | 551486ns        | 557960ns  | 636303ns   | 721395ns  | **502292ns**  |
| Update   ~4K entities with 3 Systems | 2824212ns | 2322159ns | 2707465ns        | 2034778ns    | 2230426ns       | 2311024ns | 2164733ns  | 2876703ns | **2024610ns** |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs      |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:-----------|
| Update  ~16K entities with 3 Systems | 11ms      | 9ms    | 10ms             | 8ms            | 9ms             | 9ms       | 8ms        | 12ms      | **7ms**    |
| Update  ~65K entities with 3 Systems | 44ms      | 38ms   | 43ms             | 32ms           | 37ms            | 36ms      | 32ms       | 56ms      | **31ms**   |
| Update  262K entities with 3 Systems | 176ms     | 147ms  | 176ms            | 134ms          | 144ms           | 146ms     | 139ms      | 221ms     | **127ms**  |
| Update   ~1M entities with 3 Systems | 703ms     | 594ms  | 703ms            | 626ms          | 582ms           | 582ms     | 531ms      | 900ms     | **499ms**  |
| Update   ~2M entities with 3 Systems | 1417ms    | 1194ms | 1383ms           | 1266ms         | 1159ms          | 1156ms    | 1067ms     | 1798ms    | **1016ms** |





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

* **OS:** Windows 10
* **CPU:** i7 - 2.8GHz @ 8Cores
* **RAM:** 16 GB
* **Compiler:** MSVC (Visual Studio 2019)

Run on my Laptop :)


### Create entities

![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT         | Ginseng   | mustache   | OpenEcs    | Flecs     |
|:------------------------------------------|:----------|:-------------|:----------|:-----------|:-----------|:----------|
| Create    16 entities with two Components | 7334ns    | 6637ns       | 506880ns  | 7620ns     | **2749ns** | 1298694ns |
| Create    64 entities with two Components | 17912ns   | 9854ns       | 442353ns  | 15121ns    | **7682ns** | 1392403ns |
| Create   256 entities with two Components | 56614ns   | **20746ns**  | 464017ns  | 39419ns    | 28281ns    | 1383772ns |
| Create   ~1K entities with two Components | 208817ns  | **60887ns**  | 511284ns  | 137718ns   | 109591ns   | 1815506ns |
| Create   ~4K entities with two Components | 813817ns  | **224397ns** | 683852ns  | 531346ns   | 436271ns   | 3552398ns |

|                                           | EntityX   | EnTT      | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------|:----------|:----------|:----------|:-----------|:----------|:--------|
| Create  ~16K entities with two Components | 3ms       | **<0ms**  | 1ms       | 2ms        | 1ms       | 10ms    |
| Create  ~65K entities with two Components | 13ms      | **4ms**   | 5ms       | 9ms        | 7ms       | 36ms    |
| Create  262K entities with two Components | 55ms      | **19ms**  | 29ms      | 37ms       | 29ms      | 144ms   |
| Create   ~1M entities with two Components | 219ms     | **78ms**  | 120ms     | 159ms      | 121ms     | 560ms   |
| Create   ~2M entities with two Components | 442ms     | **169ms** | 254ms     | 314ms      | 241ms     | 1133ms  |



### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache    | OpenEcs   | Flecs     |
|:-------------------------------------------|:----------|:---------|:----------|:------------|:----------|:----------|
| Destroy    16 entities with two components | 3847ns    | 2923ns   | 221738ns  | **1218ns**  | 1880ns    | 822565ns  |
| Destroy    64 entities with two components | 9032ns    | 9138ns   | 226580ns  | **1440ns**  | 3790ns    | 856148ns  |
| Destroy   256 entities with two components | 29627ns   | 33553ns  | 244415ns  | **2107ns**  | 10359ns   | 875063ns  |
| Destroy   ~1K entities with two components | 114291ns  | 132560ns | 316049ns  | **4675ns**  | 35715ns   | 992980ns  |
| Destroy   ~4K entities with two components | 459018ns  | 528652ns | 584014ns  | **14733ns** | 135895ns  | 1306428ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache | OpenEcs  | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:---------|:--------|
| Destroy  ~16K entities with two components | 1ms       | 2ms    | 1ms       | **<0ms** | **<0ms** | 2ms     |
| Destroy  ~65K entities with two components | 7ms       | 8ms    | 6ms       | **<0ms** | 2ms      | 7ms     |
| Destroy  262K entities with two components | 32ms      | 34ms   | 30ms      | **1ms**  | 11ms     | 26ms    |
| Destroy   ~1M entities with two components | 136ms     | 139ms  | 124ms     | **6ms**  | 46ms     | 99ms    |
| Destroy   ~2M entities with two components | 281ms     | 281ms  | 247ms     | **13ms** | 92ms     | 199ms   |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng     | mustache   | OpenEcs   | Flecs    |
|:---------------------------------------|:----------|:--------|:------------|:-----------|:----------|:---------|
| Unpack one component in    16 entities | 76ns      | 211ns   | **71ns**    | 292ns      | 276ns     | 1568ns   |
| Unpack one component in    64 entities | 339ns     | 908ns   | **264ns**   | 1202ns     | 1081ns    | 6169ns   |
| Unpack one component in   256 entities | 1286ns    | 3621ns  | **1023ns**  | 4418ns     | 4274ns    | 24661ns  |
| Unpack one component in   ~1K entities | 5011ns    | 14322ns | **4112ns**  | 18166ns    | 17051ns   | 98821ns  |
| Unpack one component in   ~4K entities | 20487ns   | 58685ns | **17091ns** | 78706ns    | 69600ns   | 408034ns |

|                                        | EntityX  | EnTT     | Ginseng  | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------|:---------|:---------|:---------|:-----------|:----------|:--------|
| Unpack one component in  ~65K entities | **<0ms** | **<0ms** | **<0ms** | 1ms        | 1ms       | 6ms     |
| Unpack one component in  262K entities | 1ms      | 3ms      | **1ms**  | 4ms        | 4ms       | 25ms    |
| Unpack one component in   ~1M entities | 5ms      | 15ms     | **5ms**  | 18ms       | 18ms      | 103ms   |
| Unpack one component in   ~2M entities | 11ms     | 30ms     | **9ms**  | 41ms       | 36ms      | 204ms   |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng     | mustache   | OpenEcs   | Flecs    |
|:--------------------------------------------|:----------|:--------|:------------|:-----------|:----------|:---------|
| Get one (const) component in    16 entities | 88ns      | 244ns   | **72ns**    | 163ns      | 274ns     | 1232ns   |
| Get one (const) component in    64 entities | 335ns     | 847ns   | **272ns**   | 623ns      | 1084ns    | 5021ns   |
| Get one (const) component in   256 entities | 1306ns    | 3501ns  | **1051ns**  | 2472ns     | 5150ns    | 19643ns  |
| Get one (const) component in   ~1K entities | 5226ns    | 13322ns | **4214ns**  | 9863ns     | 20562ns   | 78170ns  |
| Get one (const) component in   ~4K entities | 21479ns   | 59271ns | **17074ns** | 39641ns    | 77021ns   | 314130ns |

|                                             | EntityX  | EnTT   | Ginseng  | mustache | OpenEcs   | Flecs   |
|:--------------------------------------------|:---------|:-------|:---------|:---------|:----------|:--------|
| Get one (const) component in  ~65K entities | **<0ms** | 1ms    | **<0ms** | **<0ms** | 1ms       | 5ms     |
| Get one (const) component in  262K entities | 1ms      | 3ms    | **1ms**  | 2ms      | 4ms       | 20ms    |
| Get one (const) component in   ~1M entities | 6ms      | 15ms   | **5ms**  | 10ms     | 18ms      | 85ms    |
| Get one (const) component in   ~2M entities | 11ms     | 31ms   | **10ms** | 21ms     | 37ms      | 168ms   |


**Note:**
* Get one const component
  1. `const PositionComponent`


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT     | Ginseng     | mustache   | OpenEcs   | Flecs    |
|:----------------------------------------|:----------|:---------|:------------|:-----------|:----------|:---------|
| Unpack two components in    16 entities | 163ns     | 421ns    | **150ns**   | 455ns      | 548ns     | 2808ns   |
| Unpack two components in    64 entities | 625ns     | 1512ns   | **586ns**   | 1800ns     | 2200ns    | 11043ns  |
| Unpack two components in   256 entities | 2455ns    | 6441ns   | **2318ns**  | 7160ns     | 8765ns    | 43869ns  |
| Unpack two components in   ~1K entities | 9987ns    | 25461ns  | **9303ns**  | 28543ns    | 35163ns   | 182412ns |
| Unpack two components in   ~4K entities | 39444ns   | 100386ns | **37461ns** | 115202ns   | 140518ns  | 698047ns |

|                                         | EntityX  | EnTT   | Ginseng  | mustache   | OpenEcs   | Flecs   |
|:----------------------------------------|:---------|:-------|:---------|:-----------|:----------|:--------|
| Unpack two components in  ~65K entities | **<0ms** | 1ms    | **<0ms** | 1ms        | 2ms       | 11ms    |
| Unpack two components in  262K entities | **2ms**  | 6ms    | **2ms**  | 7ms        | 9ms       | 45ms    |
| Unpack two components in   ~1M entities | **10ms** | 27ms   | **10ms** | 30ms       | 36ms      | 181ms   |
| Unpack two components in   ~2M entities | **21ms** | 55ms   | **21ms** | 58ms       | 73ms      | 382ms   |


**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`



### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng     | mustache   | OpenEcs   | Flecs    |
|:------------------------------------------|:----------|:--------|:------------|:-----------|:----------|:---------|
| Unpack three components in     8 entities | 131ns     | 298ns   | **126ns**   | 243ns      | 438ns     | 2098ns   |
| Unpack three components in    32 entities | 498ns     | 1173ns  | **471ns**   | 940ns      | 1848ns    | 8501ns   |
| Unpack three components in   128 entities | 1967ns    | 4649ns  | **1860ns**  | 3727ns     | 7048ns    | 33568ns  |
| Unpack three components in   512 entities | 7824ns    | 18683ns | **7291ns**  | 14828ns    | 28076ns   | 137735ns |
| Unpack three components in   ~2K entities | 32629ns   | 74923ns | **28680ns** | 60304ns    | 113365ns  | 552611ns |

|                                           | EntityX  | EnTT   | Ginseng  | mustache | OpenEcs   | Flecs   |
|:------------------------------------------|:---------|:-------|:---------|:---------|:----------|:--------|
| Unpack three components in  ~32K entities | **<0ms** | 1ms    | **<0ms** | **<0ms** | 1ms       | 8ms     |
| Unpack three components in  131K entities | **2ms**  | 4ms    | **2ms**  | 3ms      | 7ms       | 35ms    |
| Unpack three components in  524K entities | **8ms**  | 23ms   | **8ms**  | 15ms     | 29ms      | 145ms   |
| Unpack three components in   ~1M entities | 17ms     | 49ms   | **16ms** | 31ms     | 60ms      | 285ms   |


**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng     | mustache   | OpenEcs   | Flecs     |
|:---------------------------------------------|:----------|:---------|:------------|:-----------|:----------|:----------|
| Remove and Add a Component in    16 entities | 1060ns    | 1540ns   | **364ns**   | 1813ns     | 668ns     | 7891ns    |
| Remove and Add a Component in    64 entities | 4322ns    | 6095ns   | **1439ns**  | 7300ns     | 2627ns    | 32021ns   |
| Remove and Add a Component in   256 entities | 17334ns   | 24417ns  | **5668ns**  | 30038ns    | 10552ns   | 129837ns  |
| Remove and Add a Component in   ~1K entities | 79685ns   | 97908ns  | **23162ns** | 117480ns   | 42158ns   | 472762ns  |
| Remove and Add a Component in   ~4K entities | 291533ns  | 390530ns | **90378ns** | 462977ns   | 173686ns  | 1974421ns |

|                                              | EntityX   | EnTT   | Ginseng  | mustache   | OpenEcs  | Flecs   |
|:---------------------------------------------|:----------|:-------|:---------|:-----------|:---------|:--------|
| Remove and Add a Component in  ~16K entities | 1ms       | 1ms    | **<0ms** | 1ms        | **<0ms** | 7ms     |
| Remove and Add a Component in  ~65K entities | 4ms       | 6ms    | **1ms**  | 7ms        | 2ms      | 31ms    |
| Remove and Add a Component in  262K entities | 17ms      | 25ms   | **6ms**  | 30ms       | 10ms     | 127ms   |
| Remove and Add a Component in   ~1M entities | 72ms      | 102ms  | **24ms** | 133ms      | 44ms     | 512ms   |
| Remove and Add a Component in   ~2M entities | 145ms     | 206ms  | **50ms** | 293ms      | 88ms     | 1024ms  |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT         | Ginseng   | mustache      | Flecs     | OpenEcs   |
|:-------------------------------------|:----------|:-------------|:----------|:--------------|:----------|:----------|
| Update    16 entities with 2 systems | 9842ns    | **8006ns**   | 9092ns    | 61807ns       | 12983ns   | 10405ns   |
| Update    64 entities with 2 systems | 39238ns   | **31195ns**  | 35733ns   | 88060ns       | 41924ns   | 40771ns   |
| Update   256 entities with 2 systems | 154352ns  | **124750ns** | 162061ns  | 190305ns      | 157600ns  | 159449ns  |
| Update   ~1K entities with 2 systems | 622049ns  | **500859ns** | 595589ns  | 575610ns      | 617963ns  | 633379ns  |
| Update   ~4K entities with 2 systems | 2481847ns | 6317373ns    | 2256297ns | **2060109ns** | 2474796ns | 2601191ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | OpenEcs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:----------|
| Update  ~16K entities with 2 systems | 10ms      | 16ms   | 9ms       | **8ms**    | 9ms     | 10ms      |
| Update  ~65K entities with 2 systems | 40ms      | 68ms   | 36ms      | **31ms**   | 39ms    | 41ms      |
| Update  262K entities with 2 systems | 158ms     | 178ms  | 141ms     | **127ms**  | 153ms   | 165ms     |
| Update   ~1M entities with 2 systems | 636ms     | 1065ms | 566ms     | **515ms**  | 617ms   | 654ms     |
| Update   ~2M entities with 2 systems | 1270ms    | 1756ms | 1145ms    | **1011ms** | 1229ms  | 1319ms    |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | Ginseng      | mustache      | Flecs     | OpenEcs   |
|:-------------------------------------|:----------|:----------|:-------------|:--------------|:----------|:----------|
| Update    16 entities with 2 systems | 8816ns    | 11181ns   | **7760ns**   | 62203ns       | 11364ns   | 8820ns    |
| Update    64 entities with 2 systems | 35742ns   | 44804ns   | **31729ns**  | 86956ns       | 36511ns   | 36339ns   |
| Update   256 entities with 2 systems | 157779ns  | 191739ns  | **139098ns** | 191599ns      | 151039ns  | 157742ns  |
| Update   ~1K entities with 2 systems | 634325ns  | 783349ns  | **580538ns** | 591529ns      | 584928ns  | 638091ns  |
| Update   ~4K entities with 2 systems | 2485028ns | 2406099ns | 2264724ns    | **2063344ns** | 2376301ns | 2595152ns |

|                                      | EntityX   | EnTT   | Ginseng | mustache   | Flecs   | OpenEcs   |
|:-------------------------------------|:----------|:-------|:--------|:-----------|:--------|:----------|
| Update  ~16K entities with 2 systems | 9ms       | 9ms    | **8ms** | **8ms**    | 10ms    | 10ms      |
| Update  ~65K entities with 2 systems | 40ms      | 36ms   | 36ms    | **32ms**   | 37ms    | 41ms      |
| Update  262K entities with 2 systems | 160ms     | 145ms  | 142ms   | **127ms**  | 150ms   | 162ms     |
| Update   ~1M entities with 2 systems | 635ms     | 582ms  | 580ms   | **512ms**  | 602ms   | 651ms     |
| Update   ~2M entities with 2 systems | 1292ms    | 1151ms | 1145ms  | **1006ms** | 1200ms  | 1314ms    |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT\*    | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:------------------|:-----------------|:-------------------|:----------|:-----------|:----------|:----------|
| Update    16 entities with 3 systems | 11692ns   | 9440ns    | 11098ns           | **8050ns**       | 8862ns             | 9029ns    | 88231ns    | 11943ns   | 13558ns   |
| Update    64 entities with 3 systems | 43626ns   | 36785ns   | 43828ns           | **31634ns**      | 35211ns            | 35630ns   | 112388ns   | 44968ns   | 40464ns   |
| Update   256 entities with 3 systems | 173383ns  | 141796ns  | 169792ns          | **124748ns**     | 139559ns           | 142625ns  | 222066ns   | 178552ns  | 151251ns  |
| Update   ~1K entities with 3 systems | 694543ns  | 569244ns  | 673371ns          | **502709ns**     | 557537ns           | 556947ns  | 647644ns   | 714996ns  | 592964ns  |
| Update   ~4K entities with 3 systems | 2878674ns | 2355741ns | 2699398ns         | **2028502ns**    | 2286205ns          | 2290036ns | 2093706ns  | 2889629ns | 2397974ns |

|                                      | EntityX   | EnTT\* | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:------------------|:-----------------|:-------------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 systems | 11ms      | 9ms    | 10ms              | **8ms**          | 9ms                | 9ms       | **8ms**    | 11ms      | 9ms     |
| Update  ~65K entities with 3 systems | 44ms      | 42ms   | 43ms              | **32ms**         | 36ms               | 36ms      | **32ms**   | 48ms      | 38ms    |
| Update  262K entities with 3 systems | 178ms     | 148ms  | 170ms             | 137ms            | 142ms              | 143ms     | **128ms**  | 189ms     | 150ms   |
| Update   ~1M entities with 3 systems | 716ms     | 593ms  | 697ms             | 625ms            | 569ms              | 587ms     | **519ms**  | 730ms     | 509ms   |
| Update   ~2M entities with 3 systems | 1418ms    | 1191ms | 1377ms            | 1243ms           | 1148ms             | 1186ms    | **1046ms** | 1494ms    | 1018ms  |


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

|                                      | EntityX   | EnTT\*    | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | OpenEcs   | Flecs         |
|:-------------------------------------|:----------|:----------|:------------------|:-----------------|:-------------------|:----------|:-----------|:----------|:--------------|
| Update    16 entities with 3 Systems | 9561ns    | 8089ns    | 9140ns            | **7016ns**       | 7775ns             | 7756ns    | 88893ns    | 9801ns    | 10002ns       |
| Update    64 entities with 3 Systems | 39776ns   | 33367ns   | 39097ns           | **28283ns**      | 32176ns            | 32392ns   | 117110ns   | 40011ns   | 31996ns       |
| Update   256 entities with 3 Systems | 172841ns  | 144813ns  | 169627ns          | **124698ns**     | 139788ns           | 141888ns  | 217666ns   | 176447ns  | 127142ns      |
| Update   ~1K entities with 3 Systems | 696880ns  | 570857ns  | 670592ns          | 503420ns         | 551486ns           | 557960ns  | 636303ns   | 721395ns  | **502292ns**  |
| Update   ~4K entities with 3 Systems | 2824212ns | 2322159ns | 2707465ns         | 2034778ns        | 2230426ns          | 2311024ns | 2164733ns  | 2876703ns | **2024610ns** |

|                                      | EntityX   | EnTT\* | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | OpenEcs   | Flecs      |
|:-------------------------------------|:----------|:-------|:------------------|:-----------------|:-------------------|:----------|:-----------|:----------|:-----------|
| Update  ~16K entities with 3 Systems | 11ms      | 9ms    | 10ms              | 8ms              | 9ms                | 9ms       | 8ms        | 12ms      | **7ms**    |
| Update  ~65K entities with 3 Systems | 44ms      | 38ms   | 43ms              | 32ms             | 37ms               | 36ms      | 32ms       | 56ms      | **31ms**   |
| Update  262K entities with 3 Systems | 176ms     | 147ms  | 176ms             | 134ms            | 144ms              | 146ms     | 139ms      | 221ms     | **127ms**  |
| Update   ~1M entities with 3 Systems | 703ms     | 594ms  | 703ms             | 626ms            | 582ms              | 582ms     | 531ms      | 900ms     | **499ms**  |
| Update   ~2M entities with 3 Systems | 1417ms    | 1194ms | 1383ms            | 1266ms           | 1159ms             | 1156ms    | 1067ms     | 1798ms    | **1016ms** |



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



### Iterate over entities with one component

![IterateSingleComponent Plot](img/IterateSingleComponent.png)

_(lower is better)_

|                                                | EntityX   | EnTT    | EnTT (runtime)   | EnTT (stable)\* | Ginseng    | mustache   | OpenEcs   | Flecs\** |
|:-----------------------------------------------|:----------|:--------|:-----------------|:----------------|:-----------|:-----------|:----------|:---------|
| Iterate over    16 entities with one component | 402ns     | 77ns    | 315ns            | 77ns            | **18ns**   | 24130ns    | 649ns     | 308ns    |
| Iterate over    64 entities with one component | 1538ns    | 230ns   | 1169ns           | 225ns           | **65ns**   | 24177ns    | 2419ns    | 316ns    |
| Iterate over   256 entities with one component | 6039ns    | 864ns   | 4578ns           | 827ns           | **254ns**  | 24023ns    | 9691ns    | 371ns    |
| Iterate over   ~1K entities with one component | 24727ns   | 3483ns  | 18355ns          | 3256ns          | **1016ns** | 24669ns    | 38666ns   | 562ns    |
| Iterate over   ~4K entities with one component | 98420ns   | 13704ns | 73473ns          | 11497ns         | **4248ns** | 25406ns    | 156340ns  | 1645ns   |

|                                                | EntityX   | EnTT     | EnTT (runtime)   | EnTT (stable)\* | Ginseng  | mustache | OpenEcs   | Flecs\** |
|:-----------------------------------------------|:----------|:---------|:-----------------|:----------------|:---------|:---------|:----------|:---------|
| Iterate over  ~65K entities with one component | 1ms       | **<0ms** | 1ms              | **<0ms**        | **<0ms** | **<0ms** | 2ms       | **<0ms** |
| Iterate over  262K entities with one component | 6ms       | **<0ms** | 4ms              | **<0ms**        | **<0ms** | **<0ms** | 9ms       | **<0ms** |
| Iterate over   ~1M entities with one component | 25ms      | 3ms      | 19ms             | 2ms             | 1ms      | **<0ms** | 39ms      | **<0ms** |
| Iterate over   ~2M entities with one component | 50ms      | 7ms      | 40ms             | 6ms             | 2ms      | **1ms**  | 80ms      | **1ms**  |


**Notes:**
* pre create views/query when possible 
* \* EnTT uses `registry.view` and a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \** flecs [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EntityX   | EnTT    | EnTT (runtime)   | EnTT (full-owning group)\* | EnTT (non-owning group)\** | EnTT (partial-owning group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | OpenEcs   | Flecs\***** |
|:------------------------------------------------|:----------|:--------|:-----------------|:---------------------------|:---------------------------|:--------------------------------|:-------------------|:----------|:-----------|:----------|:------------|
| Iterate over    16 entities with two components | 735ns     | 116ns   | 574ns            | 37ns                       | 68ns                       | 37ns                            | 87ns               | **36ns**  | 24410ns    | 685ns     | 321ns       |
| Iterate over    64 entities with two components | 2885ns    | 415ns   | 2155ns           | 145ns                      | 234ns                      | 146ns                           | 298ns              | **132ns** | 24409ns    | 2634ns    | 340ns       |
| Iterate over   256 entities with two components | 11364ns   | 1578ns  | 8543ns           | 552ns                      | 889ns                      | 549ns                           | 1133ns             | 517ns     | 24851ns    | 10339ns   | **392ns**   |
| Iterate over   ~1K entities with two components | 45657ns   | 6452ns  | 34505ns          | 2193ns                     | 3618ns                     | 2164ns                          | 4480ns             | 2230ns    | 24833ns    | 41675ns   | **593ns**   |
| Iterate over   ~4K entities with two components | 183215ns  | 25362ns | 141048ns         | 8763ns                     | 14689ns                    | 8651ns                          | 18193ns            | 8748ns    | 26031ns    | 168455ns  | **1655ns**  |

|                                                 | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)\* | EnTT (non-owning group)\** | EnTT (partial-owning group)\*** | EnTT (stable)\**** | Ginseng  | mustache | OpenEcs   | Flecs\***** |
|:------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:---------------------------|:--------------------------------|:-------------------|:---------|:---------|:----------|:------------|
| Iterate over  ~65K entities with two components | 2ms       | 0ms    | 2ms              | **<0ms**                   | **<0ms**                   | **<0ms**                        | **<0ms**           | **<0ms** | **<0ms** | 2ms       | **<0ms**    |
| Iterate over  262K entities with two components | 11ms      | 1ms    | 8ms              | **<0ms**                   | 1ms                        | **<0ms**                        | 1ms                | **<0ms** | **<0ms** | 11ms      | **<0ms**    |
| Iterate over   ~1M entities with two components | 47ms      | 6ms    | 36ms             | 2ms                        | 4ms                        | 2ms                             | 5ms                | 3ms      | **<0ms** | 46ms      | **<0ms**    |
| Iterate over   ~2M entities with two components | 95ms      | 14ms   | 73ms             | 4ms                        | 8ms                        | 4ms                             | 10ms               | 7ms      | **1ms**  | 95ms      | **1ms**     |


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

|                                                   | EntityX   | EnTT    | EnTT (runtime) | EnTT (full-owning group)\* | EnTT (non-owning group)\** | EnTT (partial-owning group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | OpenEcs   | Flecs\***** |
|:--------------------------------------------------|:----------|:--------|:---------------|:---------------------------|:---------------------------|:--------------------------------|:-------------------|:----------|:-----------|:----------|:------------|
| Iterate over    16 entities with three components | 764ns     | 90ns    | 471ns          | **27ns**                   | 53ns                       | **27ns**                        | 81ns               | 50ns      | 25139ns    | 618ns     | 338ns       |
| Iterate over    64 entities with three components | 3062ns    | 347ns   | 1838ns         | 84ns                       | 171ns                      | **83ns**                        | 289ns              | 163ns     | 24298ns    | 2515ns    | 351ns       |
| Iterate over   256 entities with three components | 15960ns   | 1455ns  | 8858ns         | 423ns                      | 906ns                      | 419ns                           | 1316ns             | 798ns     | 24631ns    | 11961ns   | **412ns**   |
| Iterate over   ~1K entities with three components | 63840ns   | 6010ns  | 36107ns        | 1643ns                     | 3629ns                     | 1621ns                          | 4862ns             | 3175ns    | 24698ns    | 46672ns   | **614ns**   |
| Iterate over   ~4K entities with three components | 255433ns  | 23248ns | 144752ns       | 6570ns                     | 14406ns                    | 6368ns                          | 20990ns            | 13023ns   | 26889ns    | 188002ns  | **1667ns**  |

|                                                   | EntityX   | EnTT     | EnTT (runtime)   | EnTT (full-owning group)\* | EnTT (non-owning group)\** | EnTT (partial-owning group)\*** | EnTT (stable)\**** | Ginseng      | mustache | OpenEcs   | Flecs\***** |
|:--------------------------------------------------|:----------|:---------|:-----------------|:---------------------------|:---------------------------|:--------------------------------|:-------------------|:-------------|:---------|:----------|:------------|
| Iterate over  ~65K entities with three components | 4ms       | **<0ms** | 2ms              | **<0ms**                   | **<0ms**                   | **<0ms**                        | **<0ms**           | **<0ms**     | **<0ms** | 2ms       | **<0ms**    |
| Iterate over  262K entities with three components | 16ms      | 1ms      | 9ms              | **<0ms**                   | **<0ms**                   | **<0ms**                        | 1ms                | **<0ms**     | **<0ms** | 11ms      | **<0ms**    |
| Iterate over   ~1M entities with three components | 65ms      | 6ms      | 38ms             | 1ms                        | 4ms                        | 1ms                             | 6ms                | 4ms          | **<0ms** | 45ms      | **<0ms**    |
| Iterate over   ~2M entities with three components | 131ms     | 13ms     | 76ms             | 3ms                        | 8ms                        | 3ms                             | 12ms               | 8ms          | **1ms**  | 90ms      | **1ms**     |


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

_You need python and some dependencies to run [gen-benchmark-report](scripts/gen-benchmark-report)_

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

Version: 3.10.1

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
