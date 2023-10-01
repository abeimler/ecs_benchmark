# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

This repository contains a collection of benchmarks for popular Entity-Component-System (ECS) frameworks. The benchmarks cover different aspects of ECS frameworks, such as update systems, component additions/removals, and entity creation/destruction.  
Each benchmark is performed on three simple components and three small systems, which can be scaled to hundreds of components and systems in a real-world scenario. The results of the benchmarks are displayed in tables and charts, allowing you to compare the performance of different ECS frameworks in different areas.  
It's important to note that different ECS frameworks have different strengths and weaknesses. For example, some frameworks might excel in adding/removing components, while others might be better at creating/destroying entities. Therefore, it's crucial to choose an ECS framework based on your specific requirements.  

ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [flecs](https://github.com/SanderMertens/flecs)
* [pico_ecs](https://github.com/empyreanx/pico_headers)

## TL;DR Results

The benchmark results are displayed in tables and charts, 
allowing you to quickly compare the performance of different ECS frameworks in different scenarios. The tables include the time in nanoseconds it takes to perform the benchmark on different numbers of entities, 
while the charts provide a visual representation of the results.   
When using ECS frameworks, it's important to benchmark your specific use case and compare the results. 
Therefore, the results of these benchmarks should be used as a starting point for your own benchmarking efforts.


### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 Systems | 1460ns   | 1988ns           | 1333ns         | 1362ns          | 1392ns    | 26458ns    | 2831ns   | 1141ns     |
| Update    64 entities with 3 Systems | 5949ns   | 8268ns           | 5592ns         | 5644ns          | 5881ns    | 30455ns    | 7307ns   | 4583ns     |
| Update   256 entities with 3 Systems | 25396ns  | 37313ns          | 24138ns        | 23515ns         | 25675ns   | 47928ns    | 26465ns  | 25937ns    |
| Update   ~1K entities with 3 Systems | 98721ns  | 145130ns         | 93535ns        | 96784ns         | 99236ns   | 115345ns   | 97519ns  | 102751ns   |
| Update   ~4K entities with 3 Systems | 389719ns | 579405ns         | 375206ns       | 359119ns        | 393509ns  | 386604ns   | 377360ns | 418940ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 Systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 Systems | 6ms    | 9ms              | 5ms            | 5ms             | 6ms       | 5ms        | 5ms     | 6ms        |
| Update  262K entities with 3 Systems | 25ms   | 36ms             | 24ms           | 24ms            | 25ms      | 26ms       | 24ms    | 24ms       |
| Update   ~1M entities with 3 Systems | 100ms  | 145ms            | 106ms          | 94ms            | 101ms     | 95ms       | 96ms    | 98ms       |
| Update   ~2M entities with 3 Systems | 199ms  | 291ms            | 273ms          | 198ms           | 202ms     | 192ms      | 195ms   | 200ms      |


While this benchmark only includes three simple components and three small systems, 
it's important to note that Entity-Component-Systems can become much more complex in the wild, 
with hundreds of components and systems.  
Therefore, it's crucial to always benchmark your specific cases and systems when necessary and compare results.
Different ECS frameworks excel in different areas, such as faster adding/removing of components or creating/destroying entities.  
Therefore, it's essential to choose an ECS framework based on its features. 
For example, EnTT offers [resource management](https://github.com/skypjack/entt/wiki/Crash-Course:-resource-management) and [event handling](https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between), while flecs provides useful [add-ons](https://github.com/SanderMertens/flecs#addons), and EntityX includes a built-in [world/system manager](https://github.com/alecthomas/entityx#manager-tying-it-all-together=).  

To evaluate a framework, look at its examples and API design, and pick the one that suits your needs the best.


## Details

### Features

All benchmarks are located in the [`benchmark/benchmarks/`](benchmark/benchmarks/) directory and are implemented with the [google/benchmark](https://github.com/google/benchmark) library. 
Each benchmark must implement the `ECSBenchmark.h` template.  

Each framework has its own sub-project in the [`src/`](src) directory and must implement specific features (see [`src/base`](src/base)).

#### Components

1. `PositionComponent`: includes `x` and `y` coordinates.
2. `VelocityComponent`: includes `x` and `y` coordinates for movement.
3. `DataComponent`: includes some arbitrary data.

#### Systems

1. `MovementSystem`: updates the `PositionComponent` with a constant `VelocityComponent`.
2. `DataSystem`: updates the `DataComponent` with arbitrary data.
3. `MoreComplexSystem`: updates components with random data and arbitrary information.

## Additional Benchmarks

Benchmarks for more common features, such as "Creating entities", "Adding and removing components", and others.

### Features tested

* Entity Creation
* Entity Destruction
* Component Retrieval
* Adding and Removing Components
* Systems (for iterating through entities)


### Environment

* **OS:** Linux 64-Bit (Kernel: 6.5.4)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 13.2.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     | pico_ecs   |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:-----------|
| Create    16 entities with two Components | 3123ns    | 3909ns   | 10943ns   | 3476ns     | 514606ns  | 1472ns     |
| Create    64 entities with two Components | 7108ns    | 5840ns   | 12606ns   | 7484ns     | 555455ns  | 2441ns     |
| Create   256 entities with two Components | 22722ns   | 12838ns  | 18445ns   | 21230ns    | 581109ns  | 5409ns     |
| Create   ~1K entities with two Components | 85253ns   | 38584ns  | 35607ns   | 74202ns    | 748617ns  | 19907ns    |
| Create   ~4K entities with two Components | 372921ns  | 141231ns | 106427ns  | 287775ns   | 1625498ns | 83456ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 1ms        | 5ms     | 0ms        |
| Create  ~65K entities with two Components | 5ms       | 2ms    | 1ms       | 4ms        | 17ms    | 1ms        |
| Create  262K entities with two Components | 21ms      | 11ms   | 9ms       | 18ms       | 64ms    | 6ms        |
| Create   ~1M entities with two Components | 103ms     | 57ms   | 59ms      | 92ms       | 290ms   | 34ms       |
| Create   ~2M entities with two Components | 208ms     | 118ms  | 110ms     | 182ms      | 569ms   | 69ms       |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | Flecs    | pico_ecs   |
|:-------------------------------------------|:----------|:---------|:----------|:---------|:-----------|
| Destroy    16 entities with two components | 1679ns    | 1562ns   | 2417ns    | 454230ns | 1269ns     |
| Destroy    64 entities with two components | 3729ns    | 3268ns   | 6026ns    | 458514ns | 1547ns     |
| Destroy   256 entities with two components | 12446ns   | 8980ns   | 20788ns   | 538117ns | 2557ns     |
| Destroy   ~1K entities with two components | 47944ns   | 33813ns  | 76495ns   | 524592ns | 5928ns     |
| Destroy   ~4K entities with two components | 194775ns  | 131020ns | 306243ns  | 775907ns | 22274ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 1ms     | 0ms        |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 4ms     | 0ms        |
| Destroy  262K entities with two components | 13ms      | 8ms    | 19ms      | 14ms    | 1ms        |
| Destroy   ~1M entities with two components | 63ms      | 36ms   | 85ms      | 62ms    | 9ms        |
| Destroy   ~2M entities with two components | 125ms     | 72ms   | 168ms     | 126ms   | 15ms       |



### Get one component from Entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack one component in    16 entities | 22ns      | 54ns    | 28ns      | 200ns      | 659ns    | 26ns       |
| Unpack one component in    64 entities | 100ns     | 221ns   | 114ns     | 819ns      | 2422ns   | 91ns       |
| Unpack one component in   256 entities | 362ns     | 878ns   | 445ns     | 3158ns     | 9770ns   | 339ns      |
| Unpack one component in   ~1K entities | 1441ns    | 3511ns  | 1786ns    | 11721ns    | 40790ns  | 1356ns     |
| Unpack one component in   ~4K entities | 5662ns    | 13834ns | 7097ns    | 46167ns    | 156085ns | 5583ns     |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Unpack one component in  262K entities | 0ms       | 0ms    | 0ms       | 4ms        | 10ms    | 0ms        |
| Unpack one component in   ~1M entities | 1ms       | 3ms    | 2ms       | 18ms       | 40ms    | 1ms        |
| Unpack one component in   ~2M entities | 3ms       | 7ms    | 3ms       | 29ms       | 80ms    | 2ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack two components in    16 entities | 48ns      | 108ns   | 59ns      | 358ns      | 1314ns   | 47ns       |
| Unpack two components in    64 entities | 174ns     | 431ns   | 248ns     | 1450ns     | 5133ns   | 174ns      |
| Unpack two components in   256 entities | 698ns     | 1663ns  | 1003ns    | 6020ns     | 19974ns  | 674ns      |
| Unpack two components in   ~1K entities | 2754ns    | 6648ns  | 3606ns    | 22481ns    | 81667ns  | 2664ns     |
| Unpack two components in   ~4K entities | 10867ns   | 26748ns | 14452ns   | 91050ns    | 323314ns | 10633ns    |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 5ms     | 0ms        |
| Unpack two components in  262K entities | 0ms       | 1ms    | 1ms       | 6ms        | 20ms    | 0ms        |
| Unpack two components in   ~1M entities | 2ms       | 7ms    | 3ms       | 26ms       | 80ms    | 2ms        |
| Unpack two components in   ~2M entities | 5ms       | 14ms   | 8ms       | 50ms       | 161ms   | 5ms        |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack three components in     8 entities | 33ns      | 123ns   | 50ns      | 186ns      | 977ns    | 35ns       |
| Unpack three components in    32 entities | 125ns     | 470ns   | 206ns     | 770ns      | 3985ns   | 123ns      |
| Unpack three components in   128 entities | 505ns     | 1899ns  | 808ns     | 2827ns     | 15417ns  | 475ns      |
| Unpack three components in   512 entities | 2069ns    | 7343ns  | 3395ns    | 11470ns    | 62415ns  | 1883ns     |
| Unpack three components in   ~2K entities | 8513ns    | 29829ns | 13996ns   | 50784ns    | 247313ns | 7512ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 3ms     | 0ms        |
| Unpack three components in  131K entities | 0ms       | 1ms    | 0ms       | 3ms        | 16ms    | 0ms        |
| Unpack three components in  524K entities | 2ms       | 7ms    | 3ms       | 12ms       | 65ms    | 1ms        |
| Unpack three components in   ~1M entities | 4ms       | 15ms   | 9ms       | 28ms       | 137ms   | 3ms        |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component


![RemoveAddComponent Plot](img/RemoveAddComponent.svg)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | Flecs    | pico_ecs   |
|:---------------------------------------------|:----------|:---------|:----------|:---------|:-----------|
| Remove and Add a Component in    16 entities | 246ns     | 421ns    | 194ns     | 3656ns   | 143ns      |
| Remove and Add a Component in    64 entities | 970ns     | 1668ns   | 763ns     | 15013ns  | 566ns      |
| Remove and Add a Component in   256 entities | 4064ns    | 6480ns   | 3042ns    | 58247ns  | 2155ns     |
| Remove and Add a Component in   ~1K entities | 16273ns   | 26029ns  | 13282ns   | 233165ns | 8608ns     |
| Remove and Add a Component in   ~4K entities | 65497ns   | 104614ns | 52822ns   | 968833ns | 37276ns    |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 4ms     | 0ms        |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 16ms    | 0ms        |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 60ms    | 2ms        |
| Remove and Add a Component in   ~1M entities | 16ms      | 26ms   | 12ms      | 260ms   | 8ms        |
| Remove and Add a Component in   ~2M entities | 32ms      | 53ms   | 24ms      | 518ms   | 19ms       |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


![SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 1787ns    | 1530ns   | 1544ns    | 17463ns    | 2638ns   | 1577ns     |
| Update    64 entities with 2 systems | 7394ns    | 5956ns   | 6163ns    | 22125ns    | 7382ns   | 6529ns     |
| Update   256 entities with 2 systems | 28879ns   | 23526ns  | 24570ns   | 39892ns    | 27542ns  | 24648ns    |
| Update   ~1K entities with 2 systems | 112575ns  | 98369ns  | 97617ns   | 102707ns   | 108173ns | 103970ns   |
| Update   ~4K entities with 2 systems | 458125ns  | 362088ns | 392786ns  | 359513ns   | 429106ns | 393898ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 7ms       | 5ms    | 6ms       | 5ms        | 6ms     | 6ms        |
| Update  262K entities with 2 systems | 29ms      | 23ms   | 25ms      | 22ms       | 25ms    | 26ms       |
| Update   ~1M entities with 2 systems | 115ms     | 93ms   | 109ms     | 91ms       | 107ms   | 100ms      |
| Update   ~2M entities with 2 systems | 226ms     | 186ms  | 194ms     | 185ms      | 197ms   | 214ms      |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 1627ns    | 1351ns   | 1379ns    | 17884ns    | 2678ns   | 1088ns     |
| Update    64 entities with 2 systems | 6589ns    | 5479ns   | 5843ns    | 22473ns    | 7075ns   | 4365ns     |
| Update   256 entities with 2 systems | 28393ns   | 23773ns  | 25667ns   | 38445ns    | 27896ns  | 24901ns    |
| Update   ~1K entities with 2 systems | 111353ns  | 92429ns  | 100518ns  | 105287ns   | 99573ns  | 99346ns    |
| Update   ~4K entities with 2 systems | 440921ns  | 363872ns | 391112ns  | 363471ns   | 401103ns | 388733ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 2ms     | 1ms        |
| Update  ~65K entities with 2 systems | 7ms       | 5ms    | 6ms       | 6ms        | 6ms     | 6ms        |
| Update  262K entities with 2 systems | 27ms      | 23ms   | 24ms      | 22ms       | 25ms    | 26ms       |
| Update   ~1M entities with 2 systems | 112ms     | 95ms   | 98ms      | 91ms       | 101ms   | 105ms      |
| Update   ~2M entities with 2 systems | 241ms     | 193ms  | 191ms     | 183ms      | 199ms   | 217ms      |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)


![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 systems | 1643ns   | 2362ns           | 1531ns         | 1545ns          | 1607ns    | 24329ns    | 2917ns   | 1647ns     |
| Update    64 entities with 3 systems | 6828ns   | 9267ns           | 6465ns         | 6054ns          | 6388ns    | 29074ns    | 7747ns   | 6523ns     |
| Update   256 entities with 3 systems | 25800ns  | 36985ns          | 24142ns        | 23717ns         | 25569ns   | 46420ns    | 26757ns  | 26216ns    |
| Update   ~1K entities with 3 systems | 98987ns  | 146332ns         | 94552ns        | 90570ns         | 99574ns   | 113073ns   | 98074ns  | 102292ns   |
| Update   ~4K entities with 3 systems | 386503ns | 576164ns         | 374139ns       | 360864ns        | 394419ns  | 381801ns   | 379212ns | 403493ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 systems | 6ms    | 9ms              | 5ms            | 5ms             | 6ms       | 5ms        | 5ms     | 6ms        |
| Update  262K entities with 3 systems | 25ms   | 36ms             | 24ms           | 24ms            | 25ms      | 24ms       | 24ms    | 26ms       |
| Update   ~1M entities with 3 systems | 99ms   | 145ms            | 104ms          | 95ms            | 100ms     | 95ms       | 95ms    | 100ms      |
| Update   ~2M entities with 3 systems | 203ms  | 290ms            | 226ms          | 191ms           | 202ms     | 190ms      | 192ms   | 204ms      |



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

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 Systems | 1460ns   | 1988ns           | 1333ns         | 1362ns          | 1392ns    | 26458ns    | 2831ns   | 1141ns     |
| Update    64 entities with 3 Systems | 5949ns   | 8268ns           | 5592ns         | 5644ns          | 5881ns    | 30455ns    | 7307ns   | 4583ns     |
| Update   256 entities with 3 Systems | 25396ns  | 37313ns          | 24138ns        | 23515ns         | 25675ns   | 47928ns    | 26465ns  | 25937ns    |
| Update   ~1K entities with 3 Systems | 98721ns  | 145130ns         | 93535ns        | 96784ns         | 99236ns   | 115345ns   | 97519ns  | 102751ns   |
| Update   ~4K entities with 3 Systems | 389719ns | 579405ns         | 375206ns       | 359119ns        | 393509ns  | 386604ns   | 377360ns | 418940ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 Systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 Systems | 6ms    | 9ms              | 5ms            | 5ms             | 6ms       | 5ms        | 5ms     | 6ms        |
| Update  262K entities with 3 Systems | 25ms   | 36ms             | 24ms           | 24ms            | 25ms      | 26ms       | 24ms    | 24ms       |
| Update   ~1M entities with 3 Systems | 100ms  | 145ms            | 106ms          | 94ms            | 101ms     | 95ms       | 96ms    | 98ms       |
| Update   ~2M entities with 3 Systems | 199ms  | 291ms            | 273ms          | 198ms           | 202ms     | 192ms      | 195ms   | 200ms      |



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


Here's an improved version of the "Contributing" section:

## Contributing

If you have any improvements to the ECS-examples for any of the frameworks, 
feel free to make a pull request or open an issue. 
The example(s) for each framework can be found in [`src/`](src/), and benchmarks are located in [`benchmarks/benchmarks/`](benchmarks/benchmarks/) for more details.

Additionally, you can write tests for the framework example and add some metadata to the [plot.config.json](plot.config.json) file. 
Any contributions are greatly appreciated!

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

Version: 1.1.2 (Apr 2023)

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

Version: 0.1.101 (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.2.7

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: 2.3 (Sep 2023)

