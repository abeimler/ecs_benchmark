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

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     8 entities with 7 Systems | 355ns  | 693ns            | 199ns          | 253ns           | 169ns     | 53373ns    | 2332ns  | 176ns      | 390ns      | 393ns            |
| Update    16 entities with 7 Systems | 360ns  | 834ns            | 184ns          | 176ns           | 210ns     | 51544ns    | 2198ns  | 181ns      | 315ns      | 335ns            |
| Update    32 entities with 7 Systems | 595ns  | 1576ns           | 286ns          | 230ns           | 383ns     | 52746ns    | 2266ns  | 323ns      | 382ns      | 389ns            |
| Update    64 entities with 7 Systems | 1052ns | 2961ns           | 476ns          | 343ns           | 720ns     | 51403ns    | 2402ns  | 559ns      | 518ns      | 518ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 21us             | 4us            | 4us             | 4us       | 52us       | 3us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 34us   | 84us             | 18us           | 21us            | 16us      | 64us       | 9us     | 18us       | 10us       | 10us             |
| Update   ~4K entities with 7 Systems | 137us  | 347us            | 92us           | 89us            | 68us      | 86us       | 29us    | 75us       | 44us       | 46us             |
| Update  ~16K entities with 7 Systems | 550us  | 1385us           | 391us          | 356us           | 296us     | 181us      | 124us   | 329us      | 218us      | 215us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 23ms             | 8ms            | 6ms             | 6ms       | 3ms        | 3ms     | 6ms        | 7ms        | 8ms              |
| Update   ~1M entities with 7 Systems | 40ms   | 92ms             | 36ms           | 26ms            | 27ms      | 14ms       | 19ms    | 23ms       | 32ms       | 32ms             |
| Update   ~2M entities with 7 Systems | 82ms   | 176ms            | 88ms           | 53ms            | 55ms      | 27ms       | 37ms    | 47ms       | 65ms       | 65ms             |



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

* **OS:** Linux 64-Bit (Kernel: 6.7.5)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 13.2.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs    | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:---------|:-----------|:-----------|
| Create     8 entities with two Components | 2324ns    | 3636ns | 10465ns   | 3151ns     | 439817ns | 1605ns     | 8251ns     |
| Create    16 entities with two Components | 2980ns    | 4038ns | 10759ns   | 3776ns     | 445037ns | 1751ns     | 9325ns     |
| Create    32 entities with two Components | 4240ns    | 4741ns | 11370ns   | 4858ns     | 447287ns | 2083ns     | 11289ns    |
| Create    64 entities with two Components | 6666ns    | 6107ns | 12342ns   | 6990ns     | 454778ns | 2741ns     | 15517ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create   256 entities with two Components | 20us      | 13us   | 17us      | 19us       | 500us   | 6us        | 38us       |
| Create   ~1K entities with two Components | 77us      | 44us   | 34us      | 68us       | 681us   | 22us       | 135us      |
| Create   ~4K entities with two Components | 303us     | 167us  | 105us     | 269us      | 1447us  | 95us       | 542us      |
| Create  ~16K entities with two Components | 1203us    | 665us  | 376us     | 1115us     | 4468us  | 379us      | 2762us     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~65K entities with two Components | 4ms       | 2ms    | 1ms       | 4ms        | 16ms    | 1ms        | 20ms       |
| Create  262K entities with two Components | 19ms      | 11ms   | 8ms       | 18ms       | 63ms    | 7ms        | 356ms      |
| Create   ~1M entities with two Components | 92ms      | 71ms   | 55ms      | 87ms       | 282ms   | 45ms       | 5358ms     |
| Create   ~2M entities with two Components | 180ms     | 133ms  | 102ms     | 168ms      | 544ms   | 67ms       | 23492ms    |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                            | EntityX   | EnTT   | Ginseng   | Flecs    | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:-----------|:-----------|
| Destroy     8 entities with two components | 1567ns    | 1395ns | 2002ns    | 412408ns | 1476ns     | 4611ns     |
| Destroy    16 entities with two components | 1939ns    | 1674ns | 2734ns    | 395578ns | 1543ns     | 5745ns     |
| Destroy    32 entities with two components | 2658ns    | 2254ns | 4182ns    | 395956ns | 1684ns     | 9033ns     |
| Destroy    64 entities with two components | 4236ns    | 3381ns | 7040ns    | 397542ns | 1979ns     | 13523ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy   256 entities with two components | 13us      | 10us   | 23us      | 406us   | 3us        | 37us       |
| Destroy   ~1K entities with two components | 50us      | 37us   | 93us      | 445us   | 10us       | 135us      |
| Destroy   ~4K entities with two components | 203us     | 150us  | 364us     | 598us   | 38us       | 538us      |
| Destroy  ~16K entities with two components | 837us     | 599us  | 1441us    | 1231us  | 151us      | 2168us     |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 3ms     | 0ms        | 8ms        |
| Destroy  262K entities with two components | 14ms      | 9ms    | 23ms      | 15ms    | 2ms        | 38ms       |
| Destroy   ~1M entities with two components | 64ms      | 43ms   | 99ms      | 57ms    | 13ms       | 195ms      |
| Destroy   ~2M entities with two components | 128ms     | 84ms   | 193ms     | 113ms   | 23ms       | 442ms      |



### Get one component from entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in     8 entities | 29ns      | 28ns   | 13ns      | 92ns       | 203ns   | 15ns       | 22ns       |
| Unpack one component in    16 entities | 58ns      | 56ns   | 31ns      | 180ns      | 403ns   | 34ns       | 46ns       |
| Unpack one component in    32 entities | 115ns     | 116ns  | 59ns      | 394ns      | 799ns   | 64ns       | 89ns       |
| Unpack one component in    64 entities | 231ns     | 226ns  | 117ns     | 756ns      | 1596ns  | 122ns      | 175ns      |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 2us        | 6us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 11us       | 25us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 14us      | 14us   | 7us       | 66us       | 101us   | 7us        | 11us       |
| Unpack one component in  ~16K entities | 59us      | 56us   | 28us      | 268us      | 407us   | 29us       | 45us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 3ms        | 6ms     | 0ms        | 1ms        |
| Unpack one component in   ~1M entities | 4ms       | 4ms    | 2ms       | 12ms       | 26ms    | 1ms        | 4ms        |
| Unpack one component in   ~2M entities | 9ms       | 8ms    | 4ms       | 25ms       | 52ms    | 3ms        | 8ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in     8 entities | 57ns      | 74ns   | 27ns      | 181ns      | 409ns   | 26ns       | 40ns       |
| Unpack two components in    16 entities | 115ns     | 139ns  | 55ns      | 354ns      | 816ns   | 55ns       | 72ns       |
| Unpack two components in    32 entities | 231ns     | 269ns  | 113ns     | 707ns      | 1628ns  | 105ns      | 141ns      |
| Unpack two components in    64 entities | 465ns     | 536ns  | 221ns     | 1411ns     | 3254ns  | 204ns      | 275ns      |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in   256 entities | 1us       | 2us    | 0us       | 5us        | 12us    | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 8us    | 3us       | 22us       | 51us    | 3us        | 4us        |
| Unpack two components in   ~4K entities | 29us      | 34us   | 14us      | 89us       | 208us   | 12us       | 17us       |
| Unpack two components in  ~16K entities | 118us     | 137us  | 57us      | 372us      | 831us   | 51us       | 70us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 3ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 2ms    | 0ms       | 6ms        | 13ms    | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 8ms       | 9ms    | 3ms       | 25ms       | 53ms    | 3ms        | 5ms        |
| Unpack two components in   ~2M entities | 18ms      | 18ms   | 7ms       | 51ms       | 106ms   | 6ms        | 10ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     8 entities | 60ns      | 116ns  | 48ns      | 180ns      | 1174ns  | 41ns       | 79ns       |
| Unpack three components in    16 entities | 118ns     | 233ns  | 97ns      | 358ns      | 2342ns  | 76ns       | 152ns      |
| Unpack three components in    32 entities | 240ns     | 455ns  | 199ns     | 702ns      | 4674ns  | 146ns      | 299ns      |
| Unpack three components in    64 entities | 474ns     | 904ns  | 396ns     | 1399ns     | 9354ns  | 287ns      | 591ns      |
| Unpack three components in   128 entities | 956ns     | 1795ns | 788ns     | 4286ns     | 18657ns | 567ns      | 1176ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   512 entities | 3us       | 7us    | 3us       | 11us       | 74us    | 2us        | 4us        |
| Unpack three components in   ~2K entities | 14us      | 29us   | 12us      | 45us       | 300us   | 9us        | 18us       |
| Unpack three components in   ~8K entities | 60us      | 117us  | 50us      | 186us      | 1195us  | 35us       | 76us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 0ms       | 3ms        | 20ms    | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 8ms    | 4ms       | 12ms       | 76ms    | 2ms        | 6ms        |
| Unpack three components in   ~1M entities | 9ms       | 16ms   | 7ms       | 24ms       | 154ms   | 4ms        | 12ms       |



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
| Remove and Add a Component in     8 entities | 125ns     | 229ns  | 97ns      | 1738ns  | 76ns       | 1808ns     |
| Remove and Add a Component in    16 entities | 244ns     | 449ns  | 186ns     | 3430ns  | 146ns      | 3575ns     |
| Remove and Add a Component in    32 entities | 483ns     | 927ns  | 365ns     | 6807ns  | 287ns      | 7424ns     |
| Remove and Add a Component in    64 entities | 961ns     | 1944ns | 727ns     | 13662ns | 567ns      | 15024ns    |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in   256 entities | 3us       | 7us    | 2us       | 54us    | 2us        | 57us       |
| Remove and Add a Component in   ~1K entities | 15us      | 28us   | 11us      | 217us   | 9us        | 227us      |
| Remove and Add a Component in   ~4K entities | 61us      | 113us  | 50us      | 888us   | 35us       | 914us      |
| Remove and Add a Component in  ~16K entities | 245us     | 451us  | 188us     | 3489us  | 143us      | 4239us     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~65K entities | 0ms       | 1ms    | 0ms       | 14ms    | 0ms        | 30ms       |
| Remove and Add a Component in  262K entities | 3ms       | 7ms    | 3ms       | 55ms    | 2ms        | 370ms      |
| Remove and Add a Component in   ~1M entities | 16ms      | 29ms   | 12ms      | 222ms   | 9ms        | 5598ms     |
| Remove and Add a Component in   ~2M entities | 32ms      | 58ms   | 24ms      | 445ms   | 18ms       | 23806ms    |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdate Plot](img/SystemsUpdate.svg)  |  ![SystemsUpdate Line Plot](img/LineSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     8 entities with 2 systems | 190ns     | 92ns   | 64ns      | 13970ns    | 1057ns  | 67ns       | 93ns       |
| Update    16 entities with 2 systems | 369ns     | 164ns  | 115ns     | 14232ns    | 1078ns  | 136ns      | 122ns      |
| Update    32 entities with 2 systems | 698ns     | 293ns  | 226ns     | 14093ns    | 1119ns  | 248ns      | 171ns      |
| Update    64 entities with 2 systems | 1348ns    | 564ns  | 443ns     | 14684ns    | 1225ns  | 472ns      | 278ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 15us       | 1us     | 1us        | 0us        |
| Update   ~1K entities with 2 systems | 23us      | 8us    | 8us       | 17us       | 4us     | 9us        | 3us        |
| Update   ~4K entities with 2 systems | 86us      | 35us   | 27us      | 26us       | 15us    | 28us       | 15us       |
| Update  ~16K entities with 2 systems | 383us     | 140us  | 118us     | 61us       | 56us    | 162us      | 67us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 2ms    | 2ms       | 1ms        | 3ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 24ms      | 12ms   | 11ms      | 7ms        | 13ms    | 10ms       | 13ms       |
| Update   ~2M entities with 2 systems | 54ms      | 25ms   | 22ms      | 14ms       | 26ms    | 22ms       | 26ms       |



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
| Update     8 entities with 2 systems | 158ns     | 77ns   | 54ns      | 15284ns    | 1117ns  | 52ns       | 124ns      |
| Update    16 entities with 2 systems | 294ns     | 140ns  | 98ns      | 15306ns    | 1157ns  | 89ns       | 137ns      |
| Update    32 entities with 2 systems | 589ns     | 276ns  | 195ns     | 15313ns    | 1206ns  | 182ns      | 189ns      |
| Update    64 entities with 2 systems | 1153ns    | 539ns  | 410ns     | 15377ns    | 1292ns  | 330ns      | 290ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 15us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 20us      | 8us    | 6us       | 19us       | 4us     | 7us        | 3us        |
| Update   ~4K entities with 2 systems | 87us      | 39us   | 27us      | 27us       | 14us    | 28us       | 16us       |
| Update  ~16K entities with 2 systems | 403us     | 134us  | 132us     | 63us       | 57us    | 152us      | 67us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 2ms    | 2ms       | 1ms        | 2ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 24ms      | 14ms   | 11ms      | 7ms        | 13ms    | 11ms       | 13ms       |
| Update   ~2M entities with 2 systems | 51ms      | 26ms   | 22ms      | 14ms       | 26ms    | 23ms       | 27ms       |


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
| Update     8 entities with 7 systems | 452ns  | 977ns            | 254ns          | 331ns           | 233ns     | 50924ns    | 2110ns  | 248ns      | 333ns      | 340ns            |
| Update    16 entities with 7 systems | 784ns  | 1865ns           | 399ns          | 520ns           | 464ns     | 50202ns    | 2169ns  | 433ns      | 421ns      | 436ns            |
| Update    32 entities with 7 systems | 1312ns | 3569ns           | 701ns          | 1046ns          | 1055ns    | 50993ns    | 2317ns  | 783ns      | 576ns      | 576ns            |
| Update    64 entities with 7 systems | 2501ns | 6952ns           | 1362ns         | 2044ns          | 1661ns    | 51462ns    | 2613ns  | 1481ns     | 888ns      | 931ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 systems | 10us   | 27us             | 6us            | 9us             | 5us       | 52us       | 4us     | 5us        | 3us        | 3us              |
| Update   ~1K entities with 7 systems | 46us   | 116us            | 28us           | 39us            | 22us      | 57us       | 10us    | 22us       | 14us       | 15us             |
| Update   ~4K entities with 7 systems | 188us  | 478us            | 142us          | 162us           | 99us      | 83us       | 38us    | 100us      | 72us       | 73us             |
| Update  ~16K entities with 7 systems | 816us  | 1882us           | 569us          | 646us           | 424us     | 198us      | 202us   | 405us      | 351us      | 323us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 systems | 3ms    | 7ms              | 2ms            | 2ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 systems | 14ms   | 31ms             | 11ms           | 11ms            | 8ms       | 4ms        | 6ms     | 7ms        | 10ms       | 11ms             |
| Update   ~1M entities with 7 systems | 57ms   | 121ms            | 51ms           | 45ms            | 35ms      | 16ms       | 22ms    | 29ms       | 44ms       | 43ms             |
| Update   ~2M entities with 7 systems | 112ms  | 233ms            | 124ms          | 89ms            | 71ms      | 38ms       | 49ms    | 60ms       | 86ms       | 90ms             |



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
| Update     8 entities with 7 Systems | 355ns  | 693ns            | 199ns          | 253ns           | 169ns     | 53373ns    | 2332ns  | 176ns      | 390ns      | 393ns            |
| Update    16 entities with 7 Systems | 360ns  | 834ns            | 184ns          | 176ns           | 210ns     | 51544ns    | 2198ns  | 181ns      | 315ns      | 335ns            |
| Update    32 entities with 7 Systems | 595ns  | 1576ns           | 286ns          | 230ns           | 383ns     | 52746ns    | 2266ns  | 323ns      | 382ns      | 389ns            |
| Update    64 entities with 7 Systems | 1052ns | 2961ns           | 476ns          | 343ns           | 720ns     | 51403ns    | 2402ns  | 559ns      | 518ns      | 518ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 21us             | 4us            | 4us             | 4us       | 52us       | 3us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 34us   | 84us             | 18us           | 21us            | 16us      | 64us       | 9us     | 18us       | 10us       | 10us             |
| Update   ~4K entities with 7 Systems | 137us  | 347us            | 92us           | 89us            | 68us      | 86us       | 29us    | 75us       | 44us       | 46us             |
| Update  ~16K entities with 7 Systems | 550us  | 1385us           | 391us          | 356us           | 296us     | 181us      | 124us   | 329us      | 218us      | 215us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 23ms             | 8ms            | 6ms             | 6ms       | 3ms        | 3ms     | 6ms        | 7ms        | 8ms              |
| Update   ~1M entities with 7 Systems | 40ms   | 92ms             | 36ms           | 26ms            | 27ms      | 14ms       | 19ms    | 23ms       | 32ms       | 32ms             |
| Update   ~2M entities with 7 Systems | 82ms   | 176ms            | 88ms           | 53ms            | 55ms      | 27ms       | 37ms    | 47ms       | 65ms       | 65ms             |



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

