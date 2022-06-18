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

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|
| Update    16 entities with 3 Systems | 8586ns    | 6586ns    | 8285ns           | 6563ns         | 6405ns          | 6525ns    | 84141ns    | 11723ns   |
| Update    64 entities with 3 Systems | 35123ns   | 26920ns   | 34249ns          | 26802ns        | 26332ns         | 27058ns   | 100132ns   | 31898ns   |
| Update   256 entities with 3 Systems | 158071ns  | 118369ns  | 152283ns         | 118809ns       | 115493ns        | 119424ns  | 185986ns   | 121469ns  |
| Update   ~1K entities with 3 Systems | 634442ns  | 473035ns  | 608478ns         | 475103ns       | 461509ns        | 476499ns  | 552646ns   | 469061ns  |
| Update   ~4K entities with 3 Systems | 2438552ns | 1801611ns | 2346543ns        | 1810703ns      | 1751117ns       | 1812692ns | 1875480ns  | 1764723ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 9ms       | 7ms    | 9ms              | 7ms            | 7ms             | 7ms       | 7ms        | 7ms     |
| Update  ~65K entities with 3 Systems | 39ms      | 30ms   | 38ms             | 30ms           | 29ms            | 30ms      | 28ms       | 29ms    |
| Update  262K entities with 3 Systems | 161ms     | 124ms  | 155ms            | 132ms          | 119ms           | 122ms     | 117ms      | 118ms   |
| Update   ~1M entities with 3 Systems | 649ms     | 487ms  | 626ms            | 679ms          | 477ms           | 488ms     | 467ms      | 473ms   |
| Update   ~2M entities with 3 Systems | 1299ms    | 981ms  | 1255ms           | 1414ms         | 959ms           | 983ms     | 939ms      | 953ms   |





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
* **CPU:** 3.10GHz @ 4Cores
* **RAM:** 8 GB

Run on my old Laptop :)


### Create entities

![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT      | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:------------------------------------------|:----------|:----------|:----------|:-----------|:----------|:----------|
| Create    16 entities with two Components | 13006ns   | 12102ns   | 23301ns   | 12038ns    | 11786ns   | 652181ns  |
| Create    64 entities with two Components | 44540ns   | 41674ns   | 52939ns   | 41594ns    | 41278ns   | 683784ns  |
| Create   256 entities with two Components | 170629ns  | 160067ns  | 171832ns  | 159999ns   | 159984ns  | 809708ns  |
| Create   ~1K entities with two Components | 672915ns  | 632360ns  | 643963ns  | 632419ns   | 630455ns  | 1299762ns |
| Create   ~4K entities with two Components | 2683714ns | 2528196ns | 2534059ns | 2524609ns  | 2515605ns | 3277625ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Create  ~16K entities with two Components | 10ms      | 10ms   | 10ms      | 10ms       | 10ms      | 11ms    |
| Create  ~65K entities with two Components | 43ms      | 40ms   | 40ms      | 40ms       | 40ms      | 42ms    |
| Create  262K entities with two Components | 176ms     | 162ms  | 164ms     | 162ms      | 161ms     | 169ms   |
| Create   ~1M entities with two Components | 741ms     | 654ms  | 660ms     | 655ms      | 645ms     | 691ms   |
| Create   ~2M entities with two Components | 1484ms    | 1308ms | 1320ms    | 1312ms     | 1291ms    | 1382ms  |


### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:-------------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Destroy    16 entities with two components | 12067ns   | 12047ns   | 12180ns   | 12071ns    | 642948ns  |
| Destroy    64 entities with two components | 41990ns   | 41462ns   | 41851ns   | 41613ns    | 672059ns  |
| Destroy   256 entities with two components | 161906ns  | 159222ns  | 161033ns  | 159803ns   | 795062ns  |
| Destroy   ~1K entities with two components | 641562ns  | 630017ns  | 634055ns  | 632040ns   | 1273045ns |
| Destroy   ~4K entities with two components | 2573603ns | 2513973ns | 2523474ns | 2519646ns  | 3196579ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Destroy  ~16K entities with two components | 10ms      | 10ms   | 10ms      | 10ms       | 10ms    |
| Destroy  ~65K entities with two components | 41ms      | 40ms   | 40ms      | 40ms       | 41ms    |
| Destroy  262K entities with two components | 167ms     | 160ms  | 161ms     | 161ms      | 162ms   |
| Destroy   ~1M entities with two components | 697ms     | 650ms  | 662ms     | 654ms      | 658ms   |
| Destroy   ~2M entities with two components | 1402ms    | 1302ms | 1325ms    | 1310ms     | 1318ms  |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:---------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Unpack one component in    16 entities | 11114ns   | 11511ns   | 11358ns   | 11663ns    | 12638ns   |
| Unpack one component in    64 entities | 40704ns   | 42265ns   | 41855ns   | 42862ns    | 46476ns   |
| Unpack one component in   256 entities | 159268ns  | 165013ns  | 163619ns  | 167209ns   | 182628ns  |
| Unpack one component in   ~1K entities | 633151ns  | 657450ns  | 654271ns  | 668318ns   | 720513ns  |
| Unpack one component in   ~4K entities | 2530240ns | 2638923ns | 2602483ns | 2659691ns  | 2938959ns |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack one component in  ~16K entities | 10ms      | 10ms   | 10ms      | 10ms       | 11ms    |
| Unpack one component in  ~65K entities | 40ms      | 42ms   | 42ms      | 42ms       | 46ms    |
| Unpack one component in  262K entities | 161ms     | 169ms  | 167ms     | 170ms      | 184ms   |
| Unpack one component in   ~1M entities | 646ms     | 678ms  | 715ms     | 684ms      | 740ms   |
| Unpack one component in   ~2M entities | 1295ms    | 1359ms | 1391ms    | 1369ms     | 1479ms  |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:--------------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Get one (const) component in    16 entities | 11102ns   | 11461ns   | 11262ns   | 11581ns    | 12350ns   |
| Get one (const) component in    64 entities | 40682ns   | 42088ns   | 41537ns   | 42675ns    | 45364ns   |
| Get one (const) component in   256 entities | 159006ns  | 164376ns  | 162836ns  | 166805ns   | 179065ns  |
| Get one (const) component in   ~1K entities | 632262ns  | 654474ns  | 648663ns  | 661041ns   | 706422ns  |
| Get one (const) component in   ~4K entities | 2525134ns | 2626935ns | 2598877ns | 2652876ns  | 2828398ns |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Get one (const) component in  ~16K entities | 10ms      | 10ms   | 10ms      | 10ms       | 11ms    |
| Get one (const) component in  ~65K entities | 40ms      | 42ms   | 41ms      | 42ms       | 45ms    |
| Get one (const) component in  262K entities | 161ms     | 169ms  | 165ms     | 170ms      | 182ms   |
| Get one (const) component in   ~1M entities | 647ms     | 676ms  | 666ms     | 682ms      | 725ms   |
| Get one (const) component in   ~2M entities | 1294ms    | 1354ms | 1328ms    | 1359ms     | 1449ms  |

**Note:**
* Get one const component
  1. `const PositionComponent`


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:----------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Unpack two components in    16 entities | 11228ns   | 11551ns   | 11435ns   | 11756ns    | 13336ns   |
| Unpack two components in    64 entities | 40891ns   | 42480ns   | 42151ns   | 43023ns    | 49935ns   |
| Unpack two components in   256 entities | 160015ns  | 165549ns  | 164856ns  | 168450ns   | 194230ns  |
| Unpack two components in   ~1K entities | 636329ns  | 660741ns  | 656741ns  | 671063ns   | 770197ns  |
| Unpack two components in   ~4K entities | 2542753ns | 2640515ns | 2632686ns | 2680369ns  | 3073637ns |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack two components in  ~16K entities | 10ms      | 10ms   | 10ms      | 10ms       | 12ms    |
| Unpack two components in  ~65K entities | 40ms      | 42ms   | 42ms      | 43ms       | 49ms    |
| Unpack two components in  262K entities | 162ms     | 170ms  | 167ms     | 172ms      | 197ms   |
| Unpack two components in   ~1M entities | 650ms     | 681ms  | 673ms     | 689ms      | 787ms   |
| Unpack two components in   ~2M entities | 1300ms    | 1362ms | 1347ms    | 1378ms     | 1577ms  |

**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`

### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:------------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Unpack three components in     8 entities | 6230ns    | 6447ns    | 6373ns    | 6547ns     | 7967ns    |
| Unpack three components in    32 entities | 21174ns   | 21995ns   | 21768ns   | 22194ns    | 27629ns   |
| Unpack three components in   128 entities | 80917ns   | 83656ns   | 83393ns   | 84752ns    | 106585ns  |
| Unpack three components in   512 entities | 320050ns  | 333084ns  | 330237ns  | 336205ns   | 421421ns  |
| Unpack three components in   ~2K entities | 1277032ns | 1326582ns | 1318451ns | 1343089ns  | 1667907ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack three components in   ~8K entities | 5ms       | 5ms    | 5ms       | 5ms        | 6ms     |
| Unpack three components in  ~32K entities | 20ms      | 21ms   | 21ms      | 21ms       | 26ms    |
| Unpack three components in  131K entities | 81ms      | 85ms   | 84ms      | 86ms       | 107ms   |
| Unpack three components in  524K entities | 327ms     | 343ms  | 338ms     | 345ms      | 432ms   |
| Unpack three components in   ~1M entities | 653ms     | 686ms  | 678ms     | 691ms      | 870ms   |

**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT      | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:---------------------------------------------|:----------|:----------|:----------|:-----------|:----------|:----------|
| Remove and Add a Component in    16 entities | 11691ns   | 11872ns   | 11505ns   | 12571ns    | 11630ns   | 18018ns   |
| Remove and Add a Component in    64 entities | 42883ns   | 43683ns   | 42318ns   | 46269ns    | 42333ns   | 67061ns   |
| Remove and Add a Component in   256 entities | 167649ns  | 170821ns  | 166372ns  | 181801ns   | 165141ns  | 263759ns  |
| Remove and Add a Component in   ~1K entities | 669222ns  | 684469ns  | 661544ns  | 721908ns   | 661921ns  | 1050093ns |
| Remove and Add a Component in   ~4K entities | 2670562ns | 2737008ns | 2641969ns | 2885468ns  | 2646482ns | 4194990ns |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:----------|:--------|
| Remove and Add a Component in  ~16K entities | 10ms      | 10ms   | 10ms      | 11ms       | 10ms      | 16ms    |
| Remove and Add a Component in  ~65K entities | 42ms      | 43ms   | 42ms      | 46ms       | 42ms      | 67ms    |
| Remove and Add a Component in  262K entities | 171ms     | 175ms  | 169ms     | 188ms      | 169ms     | 269ms   |
| Remove and Add a Component in   ~1M entities | 682ms     | 703ms  | 677ms     | 790ms      | 680ms     | 1076ms  |
| Remove and Add a Component in   ~2M entities | 1367ms    | 1410ms | 1360ms    | 1581ms     | 1361ms    | 2150ms  |



**Note:**
* Remove and add `PositionComponent`


### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:-------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Update    16 entities with 2 systems | 7599ns    | 6376ns    | 6279ns    | 50403ns    | 10789ns   |
| Update    64 entities with 2 systems | 31150ns   | 26241ns   | 26044ns   | 69031ns    | 30565ns   |
| Update   256 entities with 2 systems | 138271ns  | 115265ns  | 114362ns  | 162771ns   | 118280ns  |
| Update   ~1K entities with 2 systems | 552215ns  | 468684ns  | 456463ns  | 497929ns   | 457949ns  |
| Update   ~4K entities with 2 systems | 2111391ns | 1752864ns | 1737502ns | 1806206ns  | 1714613ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 8ms       | 7ms    | 7ms       | 7ms        | 6ms     |
| Update  ~65K entities with 2 systems | 34ms      | 29ms   | 28ms      | 28ms       | 28ms    |
| Update  262K entities with 2 systems | 141ms     | 119ms  | 117ms     | 114ms      | 115ms   |
| Update   ~1M entities with 2 systems | 566ms     | 475ms  | 469ms     | 458ms      | 460ms   |
| Update   ~2M entities with 2 systems | 1132ms    | 949ms  | 942ms     | 922ms      | 931ms   |

**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | Ginseng   | mustache   | Flecs     |
|:-------------------------------------|:----------|:----------|:----------|:-----------|:----------|
| Update    16 entities with 2 systems | 7598ns    | 6378ns    | 6404ns    | 46123ns    | 10772ns   |
| Update    64 entities with 2 systems | 31158ns   | 26272ns   | 26422ns   | 64520ns    | 30553ns   |
| Update   256 entities with 2 systems | 138243ns  | 115366ns  | 115442ns  | 161887ns   | 118415ns  |
| Update   ~1K entities with 2 systems | 552324ns  | 462417ns  | 459979ns  | 492922ns   | 458585ns  |
| Update   ~4K entities with 2 systems | 2108878ns | 1759468ns | 1745768ns | 1810591ns  | 1716239ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 8ms       | 7ms    | 7ms       | 7ms        | 6ms     |
| Update  ~65K entities with 2 systems | 34ms      | 29ms   | 28ms      | 28ms       | 28ms    |
| Update  262K entities with 2 systems | 140ms     | 118ms  | 118ms     | 115ms      | 115ms   |
| Update   ~1M entities with 2 systems | 565ms     | 472ms  | 469ms     | 458ms      | 460ms   |
| Update   ~2M entities with 2 systems | 1133ms    | 955ms  | 941ms     | 923ms      | 928ms   |

**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT\*    | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | Flecs     |
|:-------------------------------------|:----------|:----------|:------------------|:-----------------|:-------------------|:----------|:-----------|:----------|
| Update    16 entities with 3 systems | 8602ns    | 6576ns    | 8246ns            | 6571ns           | 6436ns             | 6524ns    | 78052ns    | 11817ns   |
| Update    64 entities with 3 systems | 35139ns   | 26877ns   | 34192ns           | 26814ns          | 26368ns            | 27038ns   | 106319ns   | 31986ns   |
| Update   256 entities with 3 systems | 157999ns  | 118470ns  | 152658ns          | 118765ns         | 115460ns           | 119415ns  | 190452ns   | 121536ns  |
| Update   ~1K entities with 3 systems | 633522ns  | 473762ns  | 608876ns          | 475260ns         | 461407ns           | 476465ns  | 552786ns   | 468797ns  |
| Update   ~4K entities with 3 systems | 2437296ns | 1801906ns | 2344336ns         | 1812432ns        | 1751976ns          | 1810828ns | 1868959ns  | 1763144ns |

|                                      | EntityX   | EnTT\* | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:------------------|:-----------------|:-------------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 systems | 9ms       | 7ms    | 9ms               | 7ms              | 7ms                | 7ms       | 7ms        | 7ms     |
| Update  ~65K entities with 3 systems | 39ms      | 30ms   | 38ms              | 30ms             | 29ms               | 30ms      | 28ms       | 29ms    |
| Update  262K entities with 3 systems | 161ms     | 122ms  | 155ms             | 132ms            | 120ms              | 122ms     | 117ms      | 118ms   |
| Update   ~1M entities with 3 systems | 651ms     | 487ms  | 626ms             | 680ms            | 476ms              | 488ms     | 468ms      | 474ms   |
| Update   ~2M entities with 3 systems | 1297ms    | 981ms  | 1253ms            | 1409ms           | 960ms              | 983ms     | 940ms      | 952ms   |

**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* \*   EnTT Framework, iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT Framework, iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT Framework, iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use normal `view`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(::entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT Framework, iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)




### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT\*    | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | Flecs     |
|:-------------------------------------|:----------|:----------|:------------------|:-----------------|:-------------------|:----------|:-----------|:----------|
| Update    16 entities with 3 Systems | 8586ns    | 6586ns    | 8285ns            | 6563ns           | 6405ns             | 6525ns    | 84141ns    | 11723ns   |
| Update    64 entities with 3 Systems | 35123ns   | 26920ns   | 34249ns           | 26802ns          | 26332ns            | 27058ns   | 100132ns   | 31898ns   |
| Update   256 entities with 3 Systems | 158071ns  | 118369ns  | 152283ns          | 118809ns         | 115493ns           | 119424ns  | 185986ns   | 121469ns  |
| Update   ~1K entities with 3 Systems | 634442ns  | 473035ns  | 608478ns          | 475103ns         | 461509ns           | 476499ns  | 552646ns   | 469061ns  |
| Update   ~4K entities with 3 Systems | 2438552ns | 1801611ns | 2346543ns         | 1810703ns        | 1751117ns          | 1812692ns | 1875480ns  | 1764723ns |

|                                      | EntityX   | EnTT\* | EnTT (runtime)\** | EnTT (group)\*** | EnTT (stable)\**** | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:------------------|:-----------------|:-------------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 9ms       | 7ms    | 9ms               | 7ms              | 7ms                | 7ms       | 7ms        | 7ms     |
| Update  ~65K entities with 3 Systems | 39ms      | 30ms   | 38ms              | 30ms             | 29ms               | 30ms      | 28ms       | 29ms    |
| Update  262K entities with 3 Systems | 161ms     | 124ms  | 155ms             | 132ms            | 119ms              | 122ms     | 117ms      | 118ms   |
| Update   ~1M entities with 3 Systems | 649ms     | 487ms  | 626ms             | 679ms            | 477ms              | 488ms     | 467ms      | 473ms   |
| Update   ~2M entities with 3 Systems | 1299ms    | 981ms  | 1255ms            | 1414ms           | 959ms              | 983ms     | 939ms      | 953ms   |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* Not every entity has all three components, some got removed
* \*   EnTT Framework, iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT Framework, iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT Framework, iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use normal `view`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(::entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT Framework, iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)



### Iterate over entities with one component

![IterateSingleComponent Plot](img/IterateSingleComponent.png)

_(lower is better)_

|                                                | EntityX   | EnTT   | EnTT (runtime)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs\* |
|:-----------------------------------------------|:----------|:-------|:-----------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over    16 entities with one component | 525ns     | 35ns   | 432ns            | 34ns            | 34ns      | 24292ns    | 21ns      | 658ns   |
| Iterate over    64 entities with one component | 1995ns    | 93ns   | 1681ns           | 93ns            | 127ns     | 25064ns    | 67ns      | 697ns   |
| Iterate over   256 entities with one component | 7872ns    | 354ns  | 6699ns           | 355ns           | 519ns     | 24859ns    | 273ns     | 848ns   |
| Iterate over   ~1K entities with one component | 31601ns   | 1348ns | 26854ns          | 1350ns          | 2070ns    | 25179ns    | 1018ns    | 1342ns  |
| Iterate over   ~4K entities with one component | 125976ns  | 5516ns | 104402ns         | 5519ns          | 7979ns    | 19676ns    | 4004ns    | 3732ns  |

|                                                | EntityX   | EnTT   | EnTT (runtime)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs\* |
|:-----------------------------------------------|:----------|:-------|:-----------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over  ~65K entities with one component | 2ms       | 0ms    | 1ms              | 0ms             | 0ms       | 0ms        | 0ms       | 0ms     |
| Iterate over  262K entities with one component | 7ms       | 0ms    | 6ms              | 0ms             | 0ms       | 0ms        | 0ms       | 0ms     |
| Iterate over   ~1M entities with one component | 32ms      | 2ms    | 27ms             | 2ms             | 3ms       | 2ms        | 1ms       | 1ms     |
| Iterate over   ~2M entities with one component | 64ms      | 4ms    | 56ms             | 4ms             | 7ms       | 4ms        | 2ms       | 4ms     |


**Notes:**
* pre create views/query when possible 
* \* flecs Frameworks, iterate components via [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EntityX   | EnTT    | EnTT (runtime)   | EnTT (full-owning group)\* | EnTT (non-owning group)\** | EnTT (partial-owning group)\*** | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs\**** |
|:------------------------------------------------|:----------|:--------|:-----------------|:---------------------------|:---------------------------|:--------------------------------|:----------------|:----------|:-----------|:----------|:-----------|
| Iterate over    16 entities with two components | 881ns     | 66ns    | 650ns            | 21ns                       | 43ns                       | 22ns                            | 66ns            | 61ns      | 24628ns    | 22ns      | 701ns      |
| Iterate over    64 entities with two components | 3397ns    | 252ns   | 2541ns           | 99ns                       | 169ns                      | 84ns                            | 252ns           | 242ns     | 25683ns    | 69ns      | 733ns      |
| Iterate over   256 entities with two components | 13483ns   | 1012ns  | 10107ns          | 346ns                      | 682ns                      | 348ns                           | 1013ns          | 920ns     | 25876ns    | 272ns     | 878ns      |
| Iterate over   ~1K entities with two components | 54824ns   | 3997ns  | 40202ns          | 1341ns                     | 2708ns                     | 1342ns                          | 3998ns          | 3596ns    | 24434ns    | 1017ns    | 1376ns     |
| Iterate over   ~4K entities with two components | 220333ns  | 15936ns | 160682ns         | 5316ns                     | 10786ns                    | 5326ns                          | 15933ns         | 14451ns   | 19976ns    | 4003ns    | 3749ns     |

|                                                 | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)\* | EnTT (non-owning group)\** | EnTT (partial-owning group)\*** | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs\**** |
|:------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:---------------------------|:--------------------------------|:----------------|:----------|:-----------|:----------|:-----------|
| Iterate over  ~65K entities with two components | 3ms       | 0ms    | 2ms              | 0ms                        | 0ms                        | 0ms                             | 0ms             | 0ms       | 0ms        | 0ms       | 0ms        |
| Iterate over  262K entities with two components | 14ms      | 1ms    | 10ms             | 0ms                        | 1ms                        | 0ms                             | 1ms             | 1ms       | 0ms        | 0ms       | 0ms        |
| Iterate over   ~1M entities with two components | 56ms      | 5ms    | 42ms             | 2ms                        | 5ms                        | 2ms                             | 5ms             | 6ms       | 2ms        | 1ms       | 1ms        |
| Iterate over   ~2M entities with two components | 112ms     | 11ms   | 84ms             | 5ms                        | 10ms                       | 5ms                             | 11ms            | 14ms      | 4ms        | 2ms       | 4ms        |


**Notes:**
* pre create views/query when possible
* \* EnTT Full-owning group, `registry.group<PositionComponent, VelocityComponent>()`
* \** EnTT Non-owning group, `registry.group(entt::get<<PositionComponent, VelocityComponent>>)`
* \*** EnTT Partial-owning group, `registry.group<PositionComponent>(::entt::get<VelocityComponent>)`
* \***** flecs Frameworks, iterate components via [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)

### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.png)

_(lower is better)_

|                                                   | EntityX   | EnTT    | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------------|:----------|:--------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:--------|
| Iterate over    16 entities with three components | 859ns     | 67ns    | 555ns            | 21ns                       | 30ns                      | 17ns                          | 67ns            | 85ns      | 24947ns    | 723ns   |
| Iterate over    64 entities with three components | 3641ns    | 267ns   | 2319ns           | 66ns                       | 118ns                     | 60ns                          | 268ns           | 318ns     | 24373ns    | 753ns   |
| Iterate over   256 entities with three components | 19337ns   | 1340ns  | 10982ns          | 348ns                      | 677ns                     | 348ns                         | 1342ns          | 1515ns    | 25291ns    | 915ns   |
| Iterate over   ~1K entities with three components | 79159ns   | 5353ns  | 43687ns          | 1336ns                     | 3486ns                    | 1333ns                        | 5385ns          | 6041ns    | 25168ns    | 1405ns  |
| Iterate over   ~4K entities with three components | 306911ns  | 21666ns | 175201ns         | 5446ns                     | 11340ns                   | 5287ns                        | 21654ns         | 24202ns   | 19624ns    | 3778ns  |

|                                                   | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:--------|
| Iterate over  ~16K entities with three components | 1ms       | 0ms    | 0ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  ~65K entities with three components | 4ms       | 0ms    | 2ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  262K entities with three components | 19ms      | 1ms    | 11ms             | 0ms                        | 1ms                       | 0ms                           | 1ms             | 1ms       | 0ms        | 0ms     |
| Iterate over   ~1M entities with three components | 79ms      | 7ms    | 45ms             | 2ms                        | 5ms                       | 2ms                           | 7ms             | 7ms       | 2ms        | 1ms     |
| Iterate over   ~2M entities with three components | 157ms     | 14ms   | 91ms             | 5ms                        | 10ms                      | 5ms                           | 14ms            | 15ms      | 4ms        | 4ms     |


**Notes:**
* Not every entity has all three components, some got removed
* pre create views/query when possible
* \* EnTT Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \** EnTT Non-owning group, `registry.group(entt::get<<PositionComponent, VelocityComponent, DataComponent>>)`
* \*** EnTT Partial-owning group, `registry.group<PositionComponent, VelocityComponent>(::entt::get<DataComponent>)`
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
