# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

Simple Benchmarks of common ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [flecs](https://github.com/SanderMertens/flecs)
* [pico_ecs](https://github.com/empyreanx/pico_headers)
* ~~TODO: [OpenEcs](https://github.com/Gronis/OpenEcs)~~

## TL;DR Results

### Update systems (for-each entities (with mixed components) in 3 systems)


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime) | EnTT (group) | EnTT (stable) | Ginseng  | mustache | Flecs        | pico_ecs   |
|:-------------------------------------|:---------|:---------------|:-------------|:--------------|:---------|:---------|:-------------|:-----------|
| Update    16 entities with 3 Systems | 1859ns   | 2164ns         | 1810ns       | 1452ns        | 1429ns   | 17379ns  | 2948ns       | **1169ns** |
| Update    64 entities with 3 Systems | 6676ns   | 8988ns         | 6081ns       | 5688ns        | 6042ns   | 22029ns  | 7731ns       | **5463ns** |
| Update   256 entities with 3 Systems | 31071ns  | 38832ns        | **25234ns**  | 27911ns       | 26494ns  | 38854ns  | 27001ns      | 25862ns    |
| Update   ~1K entities with 3 Systems | 117242ns | 146701ns       | 104298ns     | 101484ns      | 103017ns | 115266ns | **100549ns** | 101012ns   |
| Update   ~4K entities with 3 Systems | 437934ns | 623621ns       | 379911ns     | **382385ns**  | 424739ns | 391316ns | 403532ns     | 397232ns   |

|                                      | EnTT      | EnTT (runtime) | EnTT (group) | EnTT (stable) | Ginseng | mustache | Flecs        | pico_ecs   |
|:-------------------------------------|:----------|:---------------|:-------------|:--------------|:--------|:---------|:-------------|:-----------|
| Update  ~16K entities with 3 Systems | **1ms**   | 2ms            | **1ms**      | **1ms**       | **1ms** | **1ms**  | **1ms**      | **1ms**    |
| Update  ~65K entities with 3 Systems | 7ms       | 9ms            | **6ms**      | **6ms**       | **6ms** | **6ms**  | **6ms**      | **6ms**    |
| Update  262K entities with 3 Systems | 32ms      | 37ms           | 26ms         | **25ms**      | 27ms    | **25ms** | **25ms**     | 26ms       |
| Update   ~1M entities with 3 Systems | 113ms     | 150ms          | 126ms        | 107ms         | 106ms   | **98ms** | 99ms         | 104ms      |
| Update   ~2M entities with 3 Systems | 225ms     | 356ms          | 272ms        | 205ms         | 211ms   | 208ms    | **200ms**    | 213ms      |



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

* **OS:** Linux 64-Bit (Kernel: 6.4.6)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 13.1.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     | pico_ecs      |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:--------------|
| Create    16 entities with two Components | 2676ns    | 3495ns   | 10426ns   | 3097ns     | 522925ns  | **1191ns**    |
| Create    64 entities with two Components | 6668ns    | 5233ns   | 11974ns   | 6492ns     | 534176ns  | **2084ns**    |
| Create   256 entities with two Components | 21379ns   | 12007ns  | 16886ns   | 19764ns    | 589483ns  | **5725ns**    |
| Create   ~1K entities with two Components | 84588ns   | 37302ns  | 34845ns   | 72389ns    | 780777ns  | **19864ns**   |
| Create   ~4K entities with two Components | 316231ns  | 139040ns | 104352ns  | 280658ns   | 1584845ns | **84775ns**   |

|                                           | EntityX   | EnTT      | Ginseng      | mustache   | Flecs  | pico_ecs   |
|:------------------------------------------|:----------|:----------|:-------------|:-----------|:-------|:-----------|
| Create  ~16K entities with two Components | 1ms       | **0ms**   | **0ms**      | 1ms        | 4ms    | **0ms**    |
| Create  ~65K entities with two Components | 4ms       | 2ms       | **1ms**      | 4ms        | 17ms   | **1ms**    |
| Create  262K entities with two Components | 20ms      | 9ms       | 8ms          | 17ms       | 66ms   | **6ms**    |
| Create   ~1M entities with two Components | 93ms      | 54ms      | 52ms         | 82ms       | 292ms  | **33ms**   |
| Create   ~2M entities with two Components | 179ms     | 106ms     | 100ms        | 167ms      | 567ms  | **66ms**   |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | Flecs    | pico_ecs    |
|:-------------------------------------------|:----------|:---------|:----------|:---------|:------------|
| Destroy    16 entities with two components | 1377ns    | 1164ns   | 2010ns    | 474940ns | **1019ns**  |
| Destroy    64 entities with two components | 3518ns    | 2578ns   | 5592ns    | 477761ns | **1390ns**  |
| Destroy   256 entities with two components | 12282ns   | 8365ns   | 19809ns   | 492976ns | **2592ns**  |
| Destroy   ~1K entities with two components | 47721ns   | 31180ns  | 76583ns   | 527769ns | **6934ns**  |
| Destroy   ~4K entities with two components | 194602ns  | 123227ns | 305002ns  | 694052ns | **25251ns** |

|                                            | EntityX    | EnTT     | Ginseng  | Flecs   | pico_ecs  |
|:-------------------------------------------|:-----------|:---------|:---------|:--------|:----------|
| Destroy  ~16K entities with two components | **0ms**    | **0ms**  | 1ms      | 1ms     | **0ms**   |
| Destroy  ~65K entities with two components | 3ms        | 1ms      | 4ms      | 4ms     | **0ms**   |
| Destroy  262K entities with two components | 13ms       | 8ms      | 20ms     | 14ms    | **1ms**   |
| Destroy   ~1M entities with two components | 59ms       | 35ms     | 83ms     | 59ms    | **9ms**   |
| Destroy   ~2M entities with two components | 120ms      | 69ms     | 168ms    | 115ms   | **16ms**  |



### Get one component from Entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_(lower is better)_

|                                        | EntityX    | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------|:-----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack one component in    16 entities | **22ns**   | 57ns    | 30ns      | 194ns      | 611ns    | 30ns       |
| Unpack one component in    64 entities | **92ns**   | 217ns   | 114ns     | 798ns      | 2431ns   | 105ns      |
| Unpack one component in   256 entities | **372ns**  | 861ns   | 444ns     | 3164ns     | 9841ns   | 407ns      |
| Unpack one component in   ~1K entities | **1403ns** | 3419ns  | 1769ns    | 11481ns    | 39123ns  | 1597ns     |
| Unpack one component in   ~4K entities | **5584ns** | 13705ns | 7077ns    | 45996ns    | 155260ns | 6348ns     |

|                                        | EntityX   | EnTT    | Ginseng  | mustache | Flecs    | pico_ecs  |
|:---------------------------------------|:----------|:--------|:---------|:---------|:---------|:----------|
| Unpack one component in  ~16K entities | **0ms**   | **0ms** | **0ms**  | **0ms**  | **0ms**  | **0ms**   |
| Unpack one component in  ~65K entities | **0ms**   | **0ms** | **0ms**  | 1ms      | 2ms      | **0ms**   |
| Unpack one component in  262K entities | **0ms**   | **0ms** | **0ms**  | 3ms      | 10ms     | **0ms**   |
| Unpack one component in   ~1M entities | **1ms**   | 3ms     | **1ms**  | 12ms     | 39ms     | **1ms**   |
| Unpack one component in   ~2M entities | **3ms**   | 7ms     | **3ms**  | 27ms     | 78ms     | **3ms**   |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_(lower is better)_

|                                         | EntityX    | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs    |
|:----------------------------------------|:-----------|:--------|:----------|:-----------|:---------|:------------|
| Unpack two components in    16 entities | **42ns**   | 108ns   | 55ns      | 366ns      | 1227ns   | 48ns        |
| Unpack two components in    64 entities | 176ns      | 421ns   | 223ns     | 1394ns     | 4877ns   | **173ns**   |
| Unpack two components in   256 entities | **678ns**  | 1673ns  | 886ns     | 5575ns     | 19454ns  | 705ns       |
| Unpack two components in   ~1K entities | **2693ns** | 6666ns  | 3516ns    | 22236ns    | 78088ns  | 2699ns      |
| Unpack two components in   ~4K entities | 10704ns    | 26649ns | 14130ns   | 88406ns    | 310513ns | **10651ns** |

|                                         | EntityX  | EnTT    | Ginseng  | mustache  | Flecs   | pico_ecs  |
|:----------------------------------------|:---------|:--------|:---------|:----------|:--------|:----------|
| Unpack two components in  ~16K entities | **0ms**  | **0ms** | **0ms**  | **0ms**   | 1ms     | **0ms**   |
| Unpack two components in  ~65K entities | **0ms**  | **0ms** | **0ms**  | 1ms       | 4ms     | **0ms**   |
| Unpack two components in  262K entities | **0ms**  | 1ms     | **0ms**  | 6ms       | 19ms    | **0ms**   |
| Unpack two components in   ~1M entities | **2ms**  | 7ms     | 3ms      | 27ms      | 78ms    | **2ms**   |
| Unpack two components in   ~2M entities | **5ms**  | 13ms    | 7ms      | 51ms      | 156ms   | **5ms**   |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_(lower is better)_

|                                           | EntityX    | EnTT    | Ginseng | mustache   | Flecs    | pico_ecs    |
|:------------------------------------------|:-----------|:--------|:--------|:-----------|:---------|:------------|
| Unpack three components in     8 entities | **31ns**   | 120ns   | 49ns    | 178ns      | 935ns    | 36ns        |
| Unpack three components in    32 entities | **127ns**  | 452ns   | 200ns   | 702ns      | 3917ns   | 130ns       |
| Unpack three components in   128 entities | 515ns      | 1799ns  | 790ns   | 2795ns     | 14862ns  | **502ns**   |
| Unpack three components in   512 entities | 2008ns     | 7189ns  | 3163ns  | 11180ns    | 59584ns  | **1989ns**  |
| Unpack three components in   ~2K entities | 8042ns     | 28643ns | 12660ns | 46010ns    | 236976ns | **8032ns**  |

|                                           | EntityX  | EnTT    | Ginseng  | mustache | Flecs    | pico_ecs |
|:------------------------------------------|:---------|:--------|:---------|:---------|:---------|:---------|
| Unpack three components in   ~8K entities | **0ms**  | **0ms** | **0ms**  | **0ms**  | **0ms**  | **0ms**  |
| Unpack three components in  ~32K entities | **0ms**  | **0ms** | **0ms**  | **0ms**  | 3ms      | **0ms**  |
| Unpack three components in  131K entities | **0ms**  | 1ms     | **0ms**  | 2ms      | 15ms     | **0ms**  |
| Unpack three components in  524K entities | **2ms**  | 7ms     | 3ms      | 12ms     | 60ms     | **2ms**  |
| Unpack three components in   ~1M entities | **4ms**  | 15ms    | 7ms      | 25ms     | 121ms    | **4ms**  |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component


![RemoveAddComponent Plot](img/RemoveAddComponent.svg)

_(lower is better)_

|                                              | EntityX   | EnTT    | Ginseng   | Flecs    | pico_ecs    |
|:---------------------------------------------|:----------|:--------|:----------|:---------|:------------|
| Remove and Add a Component in    16 entities | 245ns     | 390ns   | 187ns     | 3687ns   | **141ns**   |
| Remove and Add a Component in    64 entities | 957ns     | 1537ns  | 725ns     | 14797ns  | **550ns**   |
| Remove and Add a Component in   256 entities | 3813ns    | 6150ns  | 2883ns    | 59815ns  | **2194ns**  |
| Remove and Add a Component in   ~1K entities | 15300ns   | 24607ns | 11711ns   | 247079ns | **8794ns**  |
| Remove and Add a Component in   ~4K entities | 61311ns   | 97870ns | 46932ns   | 944265ns | **35081ns** |

|                                              | EntityX   | EnTT     | Ginseng | Flecs   | pico_ecs |
|:---------------------------------------------|:----------|:---------|:--------|:--------|:---------|
| Remove and Add a Component in  ~16K entities | **0ms**   | **0ms**  | **0ms** | 3ms     | **0ms**  |
| Remove and Add a Component in  ~65K entities | **0ms**   | 1ms      | **0ms** | 15ms    | **0ms**  |
| Remove and Add a Component in  262K entities | 3ms       | 6ms      | 3ms     | 60ms    | **2ms**  |
| Remove and Add a Component in   ~1M entities | 16ms      | 25ms     | 13ms    | 242ms   | **12ms** |
| Remove and Add a Component in   ~2M entities | 32ms      | 51ms     | 24ms    | 481ms   | **19ms** |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


![SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache     | Flecs    | pico_ecs    |
|:-------------------------------------|:----------|:---------|:----------|:-------------|:---------|:------------|
| Update    16 entities with 2 systems | 1896ns    | 1582ns   | 1513ns    | 10693ns      | 3046ns   | **1509ns**  |
| Update    64 entities with 2 systems | 7021ns    | 6370ns   | 5972ns    | 15035ns      | 8567ns   | **5931ns**  |
| Update   256 entities with 2 systems | 27914ns   | 24363ns  | 23848ns   | 31699ns      | 28082ns  | **23732ns** |
| Update   ~1K entities with 2 systems | 107835ns  | 93592ns  | 95078ns   | 97670ns      | 105934ns | **91998ns** |
| Update   ~4K entities with 2 systems | 464062ns  | 366421ns | 382524ns  | **361184ns** | 416798ns | 366435ns    |

|                                      | EntityX  | EnTT    | Ginseng  | mustache  | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:--------|:---------|:----------|:---------|:-----------|
| Update  ~16K entities with 2 systems | **1ms**  | **1ms** | **1ms**  | **1ms**   | **1ms**  | **1ms**    |
| Update  ~65K entities with 2 systems | 7ms      | **5ms** | 6ms      | 5ms       | 6ms      | **5ms**    |
| Update  262K entities with 2 systems | 27ms     | 25ms    | 25ms     | **23ms**  | 25ms     | 24ms       |
| Update   ~1M entities with 2 systems | 113ms    | 96ms    | 96ms     | 92ms      | 102ms    | **95ms**   |
| Update   ~2M entities with 2 systems | 233ms    | 193ms   | 196ms    | **185ms** | 206ms    | 191ms      |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng      | mustache      | Flecs    | pico_ecs    |
|:-------------------------------------|:----------|:---------|:-------------|:--------------|:---------|:------------|
| Update    16 entities with 2 systems | 1741ns    | 1382ns   | 1314ns       | 12076ns       | 2901ns   | **1082ns**  |
| Update    64 entities with 2 systems | 7357ns    | 5892ns   | 5498ns       | 15774ns       | 7967ns   | **4392ns**  |
| Update   256 entities with 2 systems | 27980ns   | 24349ns  | **23812ns**  | 32926ns       | 28531ns  | 24260ns     |
| Update   ~1K entities with 2 systems | 112417ns  | 94608ns  | 94073ns      | 99601ns       | 106679ns | **91252ns** |
| Update   ~4K entities with 2 systems | 442703ns  | 365843ns | 375218ns     | **362228ns**  | 412745ns | 369230ns    |

|                                      | EntityX   | EnTT      | Ginseng    | mustache  | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:----------|:-----------|:----------|:---------|:-----------|
| Update  ~16K entities with 2 systems | **1ms**   | **1ms**   | **1ms**    | **1ms**   | **1ms**  | **1ms**    |
| Update  ~65K entities with 2 systems | 6ms       | **5ms**   | 6ms        | **5ms**   | 6ms      | **5ms**    |
| Update  262K entities with 2 systems | 28ms      | **23ms**  | 24ms       | **23ms**  | 25ms     | 29ms       |
| Update   ~1M entities with 2 systems | 119ms     | 93ms      | 96ms       | **92ms**  | 103ms    | 98ms       |
| Update   ~2M entities with 2 systems | 227ms     | **184ms** | 194ms      | **184ms** | 210ms    | 197ms      |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)


![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime) | EnTT (group)  | EnTT (stable) | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:---------------|:--------------|:--------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 systems | 1783ns   | 2419ns         | **1630ns**    | 1703ns        | 1722ns    | 16772ns    | 3053ns   | 1714ns     |
| Update    64 entities with 3 systems | 6654ns   | 10194ns        | 6668ns        | **6251ns**    | 7042ns    | 20810ns    | 7686ns   | 7361ns     |
| Update   256 entities with 3 systems | 27624ns  | 37992ns        | 25053ns       | **24801ns**   | 26410ns   | 38904ns    | 26957ns  | 26056ns    |
| Update   ~1K entities with 3 systems | 107331ns | 158191ns       | 98966ns       | **94128ns**   | 106460ns  | 107507ns   | 100699ns | 103664ns   |
| Update   ~4K entities with 3 systems | 408430ns | 589992ns       | 390686ns      | **375524ns**  | 419782ns  | 385067ns   | 402372ns | 444529ns   |

|                                      | EnTT     | EnTT (runtime) | EnTT (group) | EnTT (stable) | Ginseng  | mustache  | Flecs   | pico_ecs  |
|:-------------------------------------|:---------|:---------------|:-------------|:--------------|:---------|:----------|:--------|:----------|
| Update  ~16K entities with 3 systems | **1ms**  | 2ms            | **1ms**      | **1ms**       | **1ms**  | **1ms**   | **1ms** | **1ms**   |
| Update  ~65K entities with 3 systems | 7ms      | 10ms           | **6ms**      | **6ms**       | 7ms      | **6ms**   | **6ms** | **6ms**   |
| Update  262K entities with 3 systems | 31ms     | 38ms           | 31ms         | 25ms          | 26ms     | **24ms**  | 26ms    | 27ms      |
| Update   ~1M entities with 3 systems | 116ms    | 148ms          | 107ms        | **98ms**      | 105ms    | 100ms     | 99ms    | 103ms     |
| Update   ~2M entities with 3 systems | 227ms    | 300ms          | 233ms        | **195ms**     | 222ms    | **195ms** | 235ms   | 231ms     |



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


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime) | EnTT (group)  | EnTT (stable) | Ginseng  | mustache      | Flecs    | pico_ecs     |
|:-------------------------------------|:---------|:---------------|:--------------|:--------------|:---------|:--------------|:---------|:-------------|
| Update    16 entities with 3 Systems | 1859ns   | 2164ns         | 1810ns        | 1452ns        | 1429ns   | 17379ns       | 2948ns   | **1169ns**   |
| Update    64 entities with 3 Systems | 6676ns   | 8988ns         | 6081ns        | 5688ns        | 6042ns   | 22029ns       | 7731ns   | **5463ns**   |
| Update   256 entities with 3 Systems | 31071ns  | 38832ns        | **25234ns**   | 27911ns       | 26494ns  | 38854ns       | 27001ns  | 25862ns      |
| Update   ~1K entities with 3 Systems | 117242ns | 146701ns       | 104298ns      | 101484ns      | 103017ns | 115266ns      | 100549ns | **101012ns** |
| Update   ~4K entities with 3 Systems | 437934ns | 623621ns       | 379911ns      | 382385ns      | 424739ns | **391316ns**  | 403532ns | 397232ns     |

|                                      | EnTT     | EnTT (runtime) | EnTT (group) | EnTT (stable) | Ginseng | mustache  | Flecs     | pico_ecs   |
|:-------------------------------------|:---------|:---------------|:-------------|:--------------|:--------|:----------|:----------|:-----------|
| Update  ~16K entities with 3 Systems | **1ms**  | 2ms            | **1ms**      | **1ms**       | **1ms** | **1ms**   | **1ms**   | **1ms**    |
| Update  ~65K entities with 3 Systems | 7ms      | 9ms            | **6ms**      | **6ms**       | **6ms** | **6ms**   | **6ms**   | **6ms**    |
| Update  262K entities with 3 Systems | 32ms     | 37ms           | 26ms         | **25ms**      | 27ms    | **25ms**  | **25ms**  | 26ms       |
| Update   ~1M entities with 3 Systems | 113ms    | 150ms          | 126ms        | 107ms         | 106ms   | 98ms      | 99ms      | 104ms      |
| Update   ~2M entities with 3 Systems | 225ms    | 356ms          | 272ms        | 205ms         | 211ms   | 208ms     | **200ms** | 213ms      |



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


## Contributing

I try to implement the ECS-examples as good as possible for each framework, if you have any improvements, feel free to make a PR or open an issue.

You can find the frameworks example(s) in [`src/`](src/) and benchmark [`benchmarks/`](benchmarks/benchmarks/) for more details.
Also, you can write tests for the framework example :)
and add some metadata in [plot.config.json](plot.config.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

### Using [Taskfile](https://taskfile.dev/installation/)

1. `git submodule update --init --recursive`
2. Build: `task build`
3. Run (All) Benchmarks: `task benchmark`
4. Plot Graphs: `task plot:all`

You can now find the benchmark-results in [`reports/`](reports/).

_You need python (>=3.9.0) and some [dependencies](scripts/gen-benchmark-report/requirements.txt) to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting)_

```bash
pip install -r ./scripts/gen-benchmark-report/requirements.txt
```

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
  * [Forked cpp_vcpkg_project](https://github.com/abeimler/cpp_vcpkg_project)
* [Google benchmark](https://github.com/google/benchmark)
* https://github.com/SanderMertens/ecs-faq
* https://github.com/jslee02/awesome-entity-component-system


### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: v3.12.2

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.
> 
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.
> 
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Apr 2023)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.2.4

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: 2.2 (Mai 2023)

