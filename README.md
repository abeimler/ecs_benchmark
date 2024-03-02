# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

This repository contains a collection of benchmarks for popular Entity-Component-System (ECS) frameworks.
The benchmarks cover different aspects of ECS frameworks, such as update systems, component additions/removals, and entity creation/destruction.
It's important to note that different ECS frameworks have different strengths and weaknesses.
For example, some frameworks might excel in adding/removing components, while others might be better at creating/destroying entities or have query support.
Therefore, it's crucial to choose an ECS framework based on your specific requirements.

ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [flecs](https://github.com/SanderMertens/flecs)
* [pico_ecs](https://github.com/empyreanx/pico_headers)
* [gaia-ecs](https://github.com/richardbiely/gaia-ecs)

## TL;DR Results

Main feature of an ECS is the iterating over a lot of entities and using system to update the components.
The results of these benchmarks should be used as a starting point for your own benchmarking efforts.

### Update systems (for-each entities (with mixed components) in 7 systems)


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)            | Ginseng      | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:-------------------------|:-------------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     8 entities with 7 Systems | 369ns  | 661ns            | 192ns          | 262ns                    | **164ns**    | 52386ns    | 2297ns  | 176ns      | 405ns      | 410ns            |
| Update    16 entities with 7 Systems | 370ns  | 837ns            | 178ns          | **175ns**                | 206ns        | 51615ns    | 2163ns  | 182ns      | 317ns      | 351ns            |
| Update    32 entities with 7 Systems | 603ns  | 1581ns           | 279ns          | **230ns**                | 388ns        | 51111ns    | 2235ns  | 324ns      | 386ns      | 418ns            |
| Update    64 entities with 7 Systems | 1060ns | 2980ns           | 469ns          | **343ns**                | 745ns        | 50157ns    | 2325ns  | 563ns      | 513ns      | 546ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs            | pico_ecs   | gaia-ecs      | gaia-ecs (SoA)      |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:-----------------|:-----------|:--------------|:--------------------|
| Update   256 entities with 7 Systems | 7us    | 20us             | 3us            | 4us             | 4us       | 53us       | 3us              | 4us        | **2us**       | **2us**             |
| Update   ~1K entities with 7 Systems | 30us   | 82us             | 18us           | 21us            | 17us      | 64us       | **9us**          | 17us       | 10us          | 10us                |
| Update   ~4K entities with 7 Systems | 134us  | 343us            | 90us           | 91us            | 72us      | 84us       | **30us**         | 70us       | 45us          | 48us                |
| Update  ~16K entities with 7 Systems | 560us  | 1397us           | 381us          | 357us           | 323us     | 160us      | **122us**        | 317us      | 217us         | 216us               |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache               | Flecs         | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------------------|:--------------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | **0ms**                | **0ms**       | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 22ms             | 8ms            | 6ms             | 7ms       | **3ms**                | **3ms**       | 5ms        | 8ms        | 8ms              |
| Update   ~1M entities with 7 Systems | 41ms   | 91ms             | 35ms           | 26ms            | 27ms      | **14ms**               | 18ms          | 23ms       | 32ms       | 33ms             |
| Update   ~2M entities with 7 Systems | 81ms   | 180ms            | 87ms           | 52ms            | 58ms      | **30ms**               | 37ms          | 49ms       | 65ms       | 66ms             |



While this benchmark only includes up to 6 components and 7 small systems,
it's important to note that Entity-Component-Systems can become much more complex in the wild,
with hundreds of components and systems.
Therefore, it's crucial to always benchmark your specific cases and systems when necessary and compare results.
Choose an ECS framework based on its features,
for example, EnTT offers [resource management](https://github.com/skypjack/entt/wiki/Crash-Course:-resource-management) and [event handling](https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between),
while flecs provides useful [add-ons](https://github.com/SanderMertens/flecs#addons) and [querying](https://github.com/SanderMertens/flecs/tree/master/examples/cpp/queries/basics),
and EntityX includes a built-in [world/system manager](https://github.com/alecthomas/entityx#manager-tying-it-all-together=).

To evaluate a framework, look at the examples and API design, and pick the one that suits your needs.


## Details

### Features

All benchmarks are located in the [`benchmark/benchmarks/`](benchmark/benchmarks/) directory and write with with the [google/benchmark](https://github.com/google/benchmark) library.
Each benchmark uses an example application for each framework (see [`src/`](src) directory), and every example application has specific base features implemented (see [`src/base`](src/base)).

#### Components

1. `PositionComponent`: includes `x` and `y` coordinates.
2. `VelocityComponent`: includes `x` and `y` coordinates for movement.
3. `DataComponent`: includes some arbitrary data.
4. `HealthComponent`: Hero/Monster data includes HP/MaxHP and status.
5. `DamageComponent`: Hero/Monster data includes damage.
6. `SpriteComponent`: Hero/Monster ASCII character as sprite.

#### Systems

1. `MovementSystem`: updates the `PositionComponent` with a constant `VelocityComponent`.
2. `DataSystem`: updates the `DataComponent` with arbitrary data.
3. `MoreComplexSystem`: updates components with random data and arbitrary information.
4. `HealthSystem`: update Hero/Monster health (update HP and status).
5. `DamageSystem`: update Hero/Monster health by taking damage.
6. `SpriteSystem`: update Hero/Monster ASCII character depending on health and type.
7. `RenderSystem`: "render"(write) Hero/Monster character sprite into a "frame buffer"(string buffer).



## Additional Benchmarks

Benchmarks for more common features, such as "Creating entities", "Adding and removing components", and others.

### Features tested

* Entity Creation
* Entity Destruction
* Component Retrieval
* Adding and removing components
* Iterating entities/quires


### Environment

* **OS:** Linux 64-Bit (Kernel: 6.7.6)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 13.2.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs    | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:---------|:-----------|:-----------|
| Create     8 entities with two Components | 2295ns    | 3626ns | 10435ns   | 3149ns     | 449404ns | 1556ns     | 5939ns     |
| Create    16 entities with two Components | 2934ns    | 4018ns | 10742ns   | 3764ns     | 450858ns | 1717ns     | 7011ns     |
| Create    32 entities with two Components | 4177ns    | 4759ns | 11244ns   | 4916ns     | 454206ns | 2061ns     | 9226ns     |
| Create    64 entities with two Components | 6549ns    | 6091ns | 12216ns   | 7044ns     | 461511ns | 2703ns     | 13805ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create   256 entities with two Components | 20us      | 13us   | 17us      | 19us       | 506us   | 6us        | 39us       |
| Create   ~1K entities with two Components | 75us      | 44us   | 34us      | 70us       | 692us   | 22us       | 142us      |
| Create   ~4K entities with two Components | 292us     | 167us  | 104us     | 270us      | 1431us  | 96us       | 549us      |
| Create  ~16K entities with two Components | 1164us    | 663us  | 376us     | 1050us     | 4416us  | 377us      | 2195us     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~65K entities with two Components | 4ms       | 2ms    | 1ms       | 4ms        | 16ms    | 1ms        | 9ms        |
| Create  262K entities with two Components | 19ms      | 11ms   | 8ms       | 17ms       | 63ms    | 6ms        | 39ms       |
| Create   ~1M entities with two Components | 91ms      | 70ms   | 55ms      | 86ms       | 279ms   | 45ms       | 164ms      |
| Create   ~2M entities with two Components | 180ms     | 129ms  | 105ms     | 169ms      | 548ms   | 67ms       | 333ms      |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                            | EntityX   | EnTT   | Ginseng   | Flecs    | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:-----------|:-----------|
| Destroy     8 entities with two components | 1593ns    | 1427ns | 1974ns    | 405872ns | 1444ns     | 3839ns     |
| Destroy    16 entities with two components | 1937ns    | 1706ns | 2705ns    | 405971ns | 1511ns     | 4940ns     |
| Destroy    32 entities with two components | 2712ns    | 2232ns | 4146ns    | 407308ns | 1645ns     | 7039ns     |
| Destroy    64 entities with two components | 4259ns    | 3388ns | 6962ns    | 405946ns | 1920ns     | 11189ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy   256 entities with two components | 13us      | 10us   | 24us      | 418us   | 3us        | 34us       |
| Destroy   ~1K entities with two components | 51us      | 38us   | 91us      | 456us   | 10us       | 131us      |
| Destroy   ~4K entities with two components | 208us     | 150us  | 361us     | 614us   | 38us       | 532us      |
| Destroy  ~16K entities with two components | 855us     | 587us  | 1447us    | 1258us  | 150us      | 2149us     |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 3ms     | 0ms        | 8ms        |
| Destroy  262K entities with two components | 14ms      | 9ms    | 23ms      | 16ms    | 2ms        | 39ms       |
| Destroy   ~1M entities with two components | 64ms      | 42ms   | 99ms      | 59ms    | 12ms       | 193ms      |
| Destroy   ~2M entities with two components | 128ms     | 82ms   | 192ms     | 115ms   | 22ms       | 433ms      |



### Get one component from entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in     8 entities | 28ns      | 28ns   | 14ns      | 99ns       | 207ns   | 15ns       | 22ns       |
| Unpack one component in    16 entities | 57ns      | 55ns   | 31ns      | 195ns      | 410ns   | 35ns       | 47ns       |
| Unpack one component in    32 entities | 115ns     | 113ns  | 58ns      | 360ns      | 814ns   | 64ns       | 90ns       |
| Unpack one component in    64 entities | 231ns     | 227ns  | 114ns     | 733ns      | 1621ns  | 122ns      | 175ns      |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 3us        | 6us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 12us       | 25us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 14us      | 14us   | 7us       | 49us       | 103us   | 7us        | 11us       |
| Unpack one component in  ~16K entities | 59us      | 57us   | 28us      | 202us      | 415us   | 29us       | 45us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 3ms        | 6ms     | 0ms        | 1ms        |
| Unpack one component in   ~1M entities | 4ms       | 3ms    | 2ms       | 11ms       | 26ms    | 1ms        | 4ms        |
| Unpack one component in   ~2M entities | 9ms       | 7ms    | 4ms       | 36ms       | 52ms    | 3ms        | 8ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in     8 entities | 57ns      | 73ns   | 27ns      | 178ns      | 412ns   | 25ns       | 40ns       |
| Unpack two components in    16 entities | 116ns     | 137ns  | 55ns      | 377ns      | 823ns   | 55ns       | 71ns       |
| Unpack two components in    32 entities | 232ns     | 268ns  | 113ns     | 699ns      | 1640ns  | 105ns      | 138ns      |
| Unpack two components in    64 entities | 462ns     | 533ns  | 223ns     | 1388ns     | 3283ns  | 204ns      | 275ns      |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in   256 entities | 1us       | 2us    | 0us       | 5us        | 13us    | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 8us    | 3us       | 22us       | 52us    | 3us        | 4us        |
| Unpack two components in   ~4K entities | 29us      | 34us   | 14us      | 88us       | 210us   | 12us       | 17us       |
| Unpack two components in  ~16K entities | 118us     | 136us  | 57us      | 362us      | 837us   | 50us       | 70us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 3ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 2ms    | 0ms       | 6ms        | 13ms    | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 8ms       | 9ms    | 3ms       | 27ms       | 53ms    | 3ms        | 5ms        |
| Unpack two components in   ~2M entities | 18ms      | 18ms   | 7ms       | 57ms       | 106ms   | 6ms        | 10ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     8 entities | 58ns      | 115ns  | 48ns      | 193ns      | 1173ns  | 40ns       | 80ns       |
| Unpack three components in    16 entities | 116ns     | 226ns  | 97ns      | 357ns      | 2338ns  | 76ns       | 155ns      |
| Unpack three components in    32 entities | 240ns     | 448ns  | 199ns     | 700ns      | 4666ns  | 146ns      | 300ns      |
| Unpack three components in    64 entities | 470ns     | 892ns  | 393ns     | 1399ns     | 9347ns  | 286ns      | 592ns      |
| Unpack three components in   128 entities | 940ns     | 1780ns | 782ns     | 2793ns     | 18670ns | 567ns      | 1178ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   512 entities | 3us       | 7us    | 3us       | 11us       | 75us    | 2us        | 4us        |
| Unpack three components in   ~2K entities | 14us      | 28us   | 12us      | 44us       | 297us   | 8us        | 19us       |
| Unpack three components in   ~8K entities | 59us      | 117us  | 51us      | 193us      | 1193us  | 35us       | 76us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 1ms       | 3ms        | 19ms    | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 7ms    | 3ms       | 12ms       | 76ms    | 2ms        | 6ms        |
| Unpack three components in   ~1M entities | 9ms       | 15ms   | 7ms       | 25ms       | 152ms   | 4ms        | 12ms       |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component


![RemoveAddComponent Plot](img/RemoveAddComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in     8 entities | 126ns     | 224ns  | 99ns      | 1727ns  | 76ns       | 1387ns     |
| Remove and Add a Component in    16 entities | 244ns     | 442ns  | 188ns     | 3449ns  | 146ns      | 2775ns     |
| Remove and Add a Component in    32 entities | 482ns     | 882ns  | 370ns     | 6913ns  | 287ns      | 5535ns     |
| Remove and Add a Component in    64 entities | 967ns     | 1761ns | 729ns     | 13753ns | 567ns      | 10983ns    |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in   256 entities | 3us       | 7us    | 2us       | 55us    | 2us        | 43us       |
| Remove and Add a Component in   ~1K entities | 15us      | 28us   | 11us      | 221us   | 8us        | 176us      |
| Remove and Add a Component in   ~4K entities | 68us      | 112us  | 52us      | 884us   | 35us       | 703us      |
| Remove and Add a Component in  ~16K entities | 284us     | 449us  | 189us     | 3540us  | 144us      | 2799us     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 14ms    | 0ms        | 11ms       |
| Remove and Add a Component in  262K entities | 4ms       | 7ms    | 3ms       | 57ms    | 2ms        | 45ms       |
| Remove and Add a Component in   ~1M entities | 16ms      | 29ms   | 12ms      | 223ms   | 9ms        | 180ms      |
| Remove and Add a Component in   ~2M entities | 33ms      | 67ms   | 24ms      | 448ms   | 18ms       | 361ms      |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdate Plot](img/SystemsUpdate.svg)  |  ![SystemsUpdate Line Plot](img/LineSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     8 entities with 2 systems | 189ns     | 89ns   | 66ns      | 13870ns    | 1016ns  | 65ns       | 95ns       |
| Update    16 entities with 2 systems | 364ns     | 161ns  | 118ns     | 14348ns    | 1059ns  | 132ns      | 123ns      |
| Update    32 entities with 2 systems | 684ns     | 294ns  | 233ns     | 14389ns    | 1092ns  | 243ns      | 184ns      |
| Update    64 entities with 2 systems | 1328ns    | 566ns  | 456ns     | 14309ns    | 1215ns  | 460ns      | 286ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 14us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 21us      | 8us    | 7us       | 16us       | 4us     | 7us        | 3us        |
| Update   ~4K entities with 2 systems | 99us      | 35us   | 28us      | 25us       | 15us    | 39us       | 15us       |
| Update  ~16K entities with 2 systems | 353us     | 141us  | 137us     | 60us       | 57us    | 146us      | 67us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 6ms       | 3ms    | 2ms       | 1ms        | 3ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 28ms      | 12ms   | 10ms      | 7ms        | 13ms    | 11ms       | 13ms       |
| Update   ~2M entities with 2 systems | 56ms      | 26ms   | 21ms      | 14ms       | 25ms    | 22ms       | 28ms       |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)  |  ![SystemsUpdateMixedEntities Line Plot](img/LineSystemsUpdateMixedEntities.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     8 entities with 2 systems | 163ns     | 78ns   | 53ns      | 15017ns    | 1104ns  | 52ns       | 129ns      |
| Update    16 entities with 2 systems | 304ns     | 143ns  | 96ns      | 15359ns    | 1144ns  | 90ns       | 150ns      |
| Update    32 entities with 2 systems | 605ns     | 277ns  | 196ns     | 15185ns    | 1190ns  | 186ns      | 195ns      |
| Update    64 entities with 2 systems | 1183ns    | 540ns  | 410ns     | 15261ns    | 1283ns  | 330ns      | 311ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 15us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 21us      | 8us    | 6us       | 18us       | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 86us      | 33us   | 32us      | 27us       | 14us    | 37us       | 16us       |
| Update  ~16K entities with 2 systems | 424us     | 140us  | 112us     | 63us       | 57us    | 123us      | 70us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 3ms    | 2ms       | 1ms        | 2ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 27ms      | 15ms   | 10ms      | 7ms        | 12ms    | 10ms       | 14ms       |
| Update   ~2M entities with 2 systems | 55ms      | 28ms   | 22ms      | 14ms       | 26ms    | 22ms       | 28ms       |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 7 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)  |  ![ComplexSystemsUpdate Line Plot](img/LineComplexSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     8 entities with 7 systems | 476ns  | 978ns            | 251ns          | 314ns           | 207ns     | 49753ns    | 2118ns  | 256ns      | 340ns      | 342ns            |
| Update    16 entities with 7 systems | 747ns  | 1815ns           | 410ns          | 521ns           | 397ns     | 49315ns    | 2203ns  | 446ns      | 431ns      | 433ns            |
| Update    32 entities with 7 systems | 1282ns | 3503ns           | 687ns          | 1028ns          | 760ns     | 50327ns    | 2353ns  | 801ns      | 596ns      | 599ns            |
| Update    64 entities with 7 systems | 2529ns | 6764ns           | 1297ns         | 2014ns          | 1451ns    | 51837ns    | 2659ns  | 1512ns     | 919ns      | 954ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 systems | 10us   | 27us             | 5us            | 9us             | 5us       | 52us       | 4us     | 5us        | 3us        | 3us              |
| Update   ~1K entities with 7 systems | 46us   | 96us             | 30us           | 38us            | 22us      | 57us       | 11us    | 22us       | 14us       | 14us             |
| Update   ~4K entities with 7 systems | 201us  | 466us            | 143us          | 134us           | 93us      | 87us       | 39us    | 93us       | 72us       | 74us             |
| Update  ~16K entities with 7 systems | 810us  | 1874us           | 600us          | 641us           | 382us     | 172us      | 155us   | 403us      | 345us      | 329us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 systems | 3ms    | 7ms              | 2ms            | 2ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 systems | 14ms   | 30ms             | 11ms           | 11ms            | 9ms       | 4ms        | 5ms     | 7ms        | 10ms       | 11ms             |
| Update   ~1M entities with 7 systems | 57ms   | 118ms            | 51ms           | 44ms            | 37ms      | 16ms       | 21ms    | 29ms       | 44ms       | 44ms             |
| Update   ~2M entities with 7 systems | 111ms  | 237ms            | 118ms          | 90ms            | 76ms      | 40ms       | 43ms    | 60ms       | 87ms       | 88ms             |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
    4. `HealthSystem`
    5. `DamageSystem`
    6. `SpriteSystem`
    7. `RenderSystem`
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** gaia-ecs (SoA) iterate via [SoA Layout](https://github.com/richardbiely/gaia-ecs?tab=readme-ov-file#data-layouts) using an `Position`- and `Velocity`-SoA-component



### Update systems (for-each entities (with mixed components) in 7 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)  |  ![ComplexSystemsUpdateMixedEntities Line Plot](img/LineComplexSystemsUpdateMixedEntities.svg)  


_Tables shows total cost. lower is faster._

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     8 entities with 7 Systems | 369ns  | 661ns            | 192ns          | 262ns           | 164ns     | 52386ns    | 2297ns  | 176ns      | 405ns      | 410ns            |
| Update    16 entities with 7 Systems | 370ns  | 837ns            | 178ns          | 175ns           | 206ns     | 51615ns    | 2163ns  | 182ns      | 317ns      | 351ns            |
| Update    32 entities with 7 Systems | 603ns  | 1581ns           | 279ns          | 230ns           | 388ns     | 51111ns    | 2235ns  | 324ns      | 386ns      | 418ns            |
| Update    64 entities with 7 Systems | 1060ns | 2980ns           | 469ns          | 343ns           | 745ns     | 50157ns    | 2325ns  | 563ns      | 513ns      | 546ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 20us             | 3us            | 4us             | 4us       | 53us       | 3us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 30us   | 82us             | 18us           | 21us            | 17us      | 64us       | 9us     | 17us       | 10us       | 10us             |
| Update   ~4K entities with 7 Systems | 134us  | 343us            | 90us           | 91us            | 72us      | 84us       | 30us    | 70us       | 45us       | 48us             |
| Update  ~16K entities with 7 Systems | 560us  | 1397us           | 381us          | 357us           | 323us     | 160us      | 122us   | 317us      | 217us      | 216us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 22ms             | 8ms            | 6ms             | 7ms       | 3ms        | 3ms     | 5ms        | 8ms        | 8ms              |
| Update   ~1M entities with 7 Systems | 41ms   | 91ms             | 35ms           | 26ms            | 27ms      | 14ms       | 18ms    | 23ms       | 32ms       | 33ms             |
| Update   ~2M entities with 7 Systems | 81ms   | 180ms            | 87ms           | 52ms            | 58ms      | 30ms       | 37ms    | 49ms       | 65ms       | 66ms             |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
    4. `HealthSystem`
    5. `DamageSystem`
    6. `SpriteSystem`
    7. `RenderSystem`
* Not every entity has all three components, some got removed
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** gaia-ecs (SoA) iterate via [SoA Layout](https://github.com/richardbiely/gaia-ecs?tab=readme-ov-file#data-layouts) using an `Position`- und `Velocity`-SoA-component


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

0. Install [Taskfile](https://taskfile.dev/installation/)
1. Run Build: `task build`
2. Run (All) Benchmarks: `task benchmark`
3. Plot Graphs: `task plot:all`

Or run `task generate`

You can now find the benchmark-results in [`reports/`](reports/).

_You need python (>=3.8.0) and some [dependencies](scripts/gen-benchmark-report/requirements.txt) to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting), install [pipx](https://pipx.pypa.io/stable/installation/) and [poetry](https://python-poetry.org/docs/#installing-with-pipx)._

Then install the dependencies for the script:
```bash
cd ./scripts/gen-benchmark-report && poetry install
```

Or run the script directly:
```bash
task plot:all
```

#### Generate README

```bash
task generate:readme
```


### ~~Step-by-Step~~

1. Configure and build benchmarks, see [Building Details](doc/README_building.md):
   1. `cmake -S . -B ./build`
   2. `cmake --build ./build`
2. Run benchmark(s), with [`run-benchmarks.sh`](run-benchmarks.sh) or each:
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt` _(console output)_ _(optional)_
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json` _(write json report)_
3. Plot Reports, after generating json reports, see [`plot-results.sh`](plot-results.sh):
   1. `pipx run --spec ./scripts/gen-benchmark-report gen-benchmark-report -i ./info.json gen-plot ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate graphs)_
   2. `pipx run --spec ./scripts/gen-benchmark-report gen-benchmark-report -i ./info.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate full report)_


### Run a single benchmark

```bash
cmake -G Ninja -S . -B build
cmake --build build --target ecs-benchmark-entt -j 4
./build/benchmark/benchmarks/entt/ecs-benchmark-entt
```

By default, building with `-DCMAKE_BUILD_TYPE=Release` is the best way. but you can use `-DCMAKE_BUILD_TYPE=Debug` (or `-DCMAKE_BUILD_TYPE=RelWithDebInfo`) to enable sanitizers and run tests.

## Links and More

- [Dependency Setup](doc/README_dependencies.md)
- [Building Details](doc/README_building.md)
- Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
  - [Forked cpp_vcpkg_project](https://github.com/abeimler/cpp_vcpkg_project)
- [Google benchmark](https://github.com/google/benchmark)
- https://github.com/SanderMertens/ecs-faq
- https://github.com/jslee02/awesome-entity-component-system


### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Apr 2023)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: v3.13.1

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.
> 
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.
> 
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Feb 2024)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: 0.1.101 (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.2.11

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: 2.3 (Sep 2023)

#### gaia-ecs by @richardbiely 

> Gaia-ECS is a fast and easy-to-use ECS framework.

Version: v0.8.4

