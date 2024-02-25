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

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)         | Ginseng   | mustache   | Flecs   | pico_ecs  | gaia-ecs  | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:----------|:----------|:-----------------|
| Update     8 entities with 7 Systems | 362ns  | 696ns            | 201ns          | 246ns                 | **147ns** | 54871ns    | 2312ns  | 179ns     | 407ns     | 410ns            |
| Update    16 entities with 7 Systems | 363ns  | 868ns            | 188ns          | 176ns                 | 196ns     | 51732ns    | 2187ns  | **178ns** | 308ns     | 344ns            |
| Update    32 entities with 7 Systems | 598ns  | 1610ns           | 286ns          | **230ns**             | 367ns     | 51734ns    | 2256ns  | 320ns     | 379ns     | 393ns            |
| Update    64 entities with 7 Systems | 1056ns | 3003ns           | 496ns          | **342ns**             | 717ns     | 51066ns    | 2390ns  | 555ns     | 512ns     | 533ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs         | pico_ecs   | gaia-ecs         | gaia-ecs (SoA)      |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------------|:-----------|:-----------------|:--------------------|
| Update   256 entities with 7 Systems | 7us    | 20us             | 4us            | 5us             | 4us       | 53us       | 3us           | 4us        | **2us**          | **2us**             |
| Update   ~1K entities with 7 Systems | 31us   | 84us             | 18us           | 21us            | 16us      | 63us       | **9us**       | 17us       | **9us**          | 10us                |
| Update   ~4K entities with 7 Systems | 137us  | 343us            | 91us           | 88us            | 69us      | 83us       | **29us**      | 79us       | 45us             | 45us                |
| Update  ~16K entities with 7 Systems | 557us  | 1393us           | 377us          | 367us           | 282us     | 151us      | **115us**     | 296us      | 216us            | 208us               |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache        | Flecs      | pico_ecs | gaia-ecs  | gaia-ecs (SoA)  |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:----------------|:-----------|:---------|:----------|:----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | **0ms**         | **0ms**    | 1ms      | 1ms       | 1ms             |
| Update  262K entities with 7 Systems | 10ms   | 23ms             | 8ms            | 6ms             | 6ms       | **3ms**         | 4ms        | 5ms      | 7ms       | 8ms             |
| Update   ~1M entities with 7 Systems | 41ms   | 91ms             | 35ms           | 26ms            | 26ms      | **13ms**        | 20ms       | 23ms     | 32ms      | 32ms            |
| Update   ~2M entities with 7 Systems | 85ms   | 187ms            | 88ms           | 52ms            | 53ms      | **30ms**        | 41ms       | 47ms     | 65ms      | 66ms            |



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
| Create     8 entities with two Components | 2635ns    | 3663ns | 10520ns   | 3213ns     | 437264ns | 1588ns     | 8363ns     |
| Create    16 entities with two Components | 3478ns    | 4078ns | 10813ns   | 3837ns     | 439403ns | 1783ns     | 9411ns     |
| Create    32 entities with two Components | 5069ns    | 4779ns | 11378ns   | 4946ns     | 449244ns | 2068ns     | 11730ns    |
| Create    64 entities with two Components | 8065ns    | 6161ns | 12342ns   | 7116ns     | 453678ns | 2725ns     | 16094ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create   256 entities with two Components | 27us      | 14us   | 17us      | 19us       | 503us   | 6us        | 42us       |
| Create   ~1K entities with two Components | 102us     | 44us   | 34us      | 68us       | 678us   | 22us       | 147us      |
| Create   ~4K entities with two Components | 391us     | 165us  | 105us     | 271us      | 1414us  | 96us       | 576us      |
| Create  ~16K entities with two Components | 1499us    | 661us  | 377us     | 1054us     | 4417us  | 380us      | 2879us     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~65K entities with two Components | 5ms       | 2ms    | 1ms       | 4ms        | 16ms    | 1ms        | 22ms       |
| Create  262K entities with two Components | 21ms      | 11ms   | 8ms       | 18ms       | 61ms    | 6ms        | 390ms      |
| Create   ~1M entities with two Components | 94ms      | 70ms   | 56ms      | 87ms       | 276ms   | 46ms       | 6034ms     |
| Create   ~2M entities with two Components | 184ms     | 132ms  | 105ms     | 170ms      | 536ms   | 67ms       | 23153ms    |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                            | EntityX   | EnTT   | Ginseng   | Flecs    | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:-----------|:-----------|
| Destroy     8 entities with two components | 1663ns    | 1422ns | 2033ns    | 393705ns | 1466ns     | 4753ns     |
| Destroy    16 entities with two components | 2004ns    | 1697ns | 2767ns    | 401669ns | 1531ns     | 5848ns     |
| Destroy    32 entities with two components | 2755ns    | 2255ns | 4207ns    | 395073ns | 1672ns     | 9426ns     |
| Destroy    64 entities with two components | 4247ns    | 3447ns | 7118ns    | 396694ns | 1951ns     | 14500ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy   256 entities with two components | 13us      | 10us   | 23us      | 405us   | 3us        | 40us       |
| Destroy   ~1K entities with two components | 50us      | 38us   | 91us      | 442us   | 10us       | 134us      |
| Destroy   ~4K entities with two components | 204us     | 148us  | 360us     | 603us   | 38us       | 535us      |
| Destroy  ~16K entities with two components | 837us     | 588us  | 1436us    | 1249us  | 150us      | 2155us     |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 3ms     | 0ms        | 8ms        |
| Destroy  262K entities with two components | 14ms      | 9ms    | 23ms      | 15ms    | 2ms        | 40ms       |
| Destroy   ~1M entities with two components | 64ms      | 42ms   | 99ms      | 59ms    | 13ms       | 192ms      |
| Destroy   ~2M entities with two components | 129ms     | 83ms   | 194ms     | 114ms   | 23ms       | 436ms      |



### Get one component from entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in     8 entities | 29ns      | 28ns   | 14ns      | 95ns       | 207ns   | 15ns       | 22ns       |
| Unpack one component in    16 entities | 58ns      | 56ns   | 31ns      | 196ns      | 409ns   | 34ns       | 46ns       |
| Unpack one component in    32 entities | 117ns     | 116ns  | 58ns      | 361ns      | 817ns   | 64ns       | 89ns       |
| Unpack one component in    64 entities | 232ns     | 227ns  | 114ns     | 735ns      | 1628ns  | 122ns      | 174ns      |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 2us        | 6us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 11us       | 25us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 15us      | 14us   | 7us       | 47us       | 103us   | 7us        | 11us       |
| Unpack one component in  ~16K entities | 59us      | 56us   | 28us      | 191us      | 415us   | 29us       | 45us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 3ms        | 6ms     | 0ms        | 1ms        |
| Unpack one component in   ~1M entities | 4ms       | 3ms    | 2ms       | 14ms       | 26ms    | 1ms        | 4ms        |
| Unpack one component in   ~2M entities | 9ms       | 7ms    | 4ms       | 26ms       | 53ms    | 3ms        | 8ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in     8 entities | 58ns      | 73ns   | 27ns      | 184ns      | 414ns   | 26ns       | 41ns       |
| Unpack two components in    16 entities | 116ns     | 137ns  | 55ns      | 355ns      | 824ns   | 55ns       | 73ns       |
| Unpack two components in    32 entities | 233ns     | 269ns  | 112ns     | 704ns      | 1644ns  | 105ns      | 142ns      |
| Unpack two components in    64 entities | 466ns     | 534ns  | 221ns     | 1408ns     | 3284ns  | 204ns      | 277ns      |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in   256 entities | 1us       | 2us    | 0us       | 5us        | 13us    | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 8us    | 3us       | 22us       | 52us    | 3us        | 4us        |
| Unpack two components in   ~4K entities | 29us      | 34us   | 14us      | 89us       | 209us   | 12us       | 17us       |
| Unpack two components in  ~16K entities | 119us     | 137us  | 56us      | 365us      | 842us   | 51us       | 70us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 3ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 2ms    | 0ms       | 6ms        | 13ms    | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 8ms       | 9ms    | 3ms       | 25ms       | 53ms    | 3ms        | 5ms        |
| Unpack two components in   ~2M entities | 18ms      | 18ms   | 7ms       | 57ms       | 107ms   | 6ms        | 10ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     8 entities | 58ns      | 115ns  | 57ns      | 194ns      | 1163ns  | 41ns       | 80ns       |
| Unpack three components in    16 entities | 118ns     | 226ns  | 111ns     | 380ns      | 2318ns  | 76ns       | 154ns      |
| Unpack three components in    32 entities | 241ns     | 450ns  | 206ns     | 744ns      | 4658ns  | 146ns      | 300ns      |
| Unpack three components in    64 entities | 473ns     | 896ns  | 398ns     | 1413ns     | 9408ns  | 286ns      | 594ns      |
| Unpack three components in   128 entities | 951ns     | 1798ns | 849ns     | 2817ns     | 18542ns | 567ns      | 1179ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   512 entities | 3us       | 7us    | 3us       | 11us       | 74us    | 2us        | 4us        |
| Unpack three components in   ~2K entities | 15us      | 29us   | 12us      | 44us       | 296us   | 8us        | 18us       |
| Unpack three components in   ~8K entities | 60us      | 117us  | 51us      | 186us      | 1188us  | 36us       | 76us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 0ms       | 3ms        | 18ms    | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 7ms    | 4ms       | 12ms       | 75ms    | 2ms        | 6ms        |
| Unpack three components in   ~1M entities | 9ms       | 15ms   | 7ms       | 26ms       | 151ms   | 4ms        | 12ms       |



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
| Remove and Add a Component in     8 entities | 127ns     | 234ns  | 97ns      | 1750ns  | 77ns       | 1391ns     |
| Remove and Add a Component in    16 entities | 250ns     | 443ns  | 187ns     | 3450ns  | 147ns      | 2770ns     |
| Remove and Add a Component in    32 entities | 488ns     | 881ns  | 368ns     | 6943ns  | 287ns      | 5532ns     |
| Remove and Add a Component in    64 entities | 966ns     | 1925ns | 735ns     | 13810ns | 567ns      | 11107ns    |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in   256 entities | 3us       | 7us    | 2us       | 55us    | 2us        | 44us       |
| Remove and Add a Component in   ~1K entities | 16us      | 29us   | 11us      | 220us   | 9us        | 179us      |
| Remove and Add a Component in   ~4K entities | 62us      | 112us  | 47us      | 885us   | 36us       | 722us      |
| Remove and Add a Component in  ~16K entities | 273us     | 458us  | 221us     | 3545us  | 143us      | 3443us     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~65K entities | 0ms       | 1ms    | 0ms       | 14ms    | 0ms        | 25ms       |
| Remove and Add a Component in  262K entities | 4ms       | 7ms    | 3ms       | 56ms    | 2ms        | 379ms      |
| Remove and Add a Component in   ~1M entities | 16ms      | 29ms   | 12ms      | 226ms   | 9ms        | 5996ms     |
| Remove and Add a Component in   ~2M entities | 32ms      | 58ms   | 24ms      | 452ms   | 18ms       | 23507ms    |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdate Plot](img/SystemsUpdate.svg)  |  ![SystemsUpdate Line Plot](img/LineSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     8 entities with 2 systems | 190ns     | 93ns   | 68ns      | 14025ns    | 1012ns  | 67ns       | 99ns       |
| Update    16 entities with 2 systems | 367ns     | 171ns  | 121ns     | 14517ns    | 1052ns  | 137ns      | 125ns      |
| Update    32 entities with 2 systems | 708ns     | 307ns  | 240ns     | 14265ns    | 1096ns  | 252ns      | 178ns      |
| Update    64 entities with 2 systems | 1386ns    | 636ns  | 480ns     | 14430ns    | 1196ns  | 479ns      | 301ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 14us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 20us      | 9us    | 7us       | 17us       | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 84us      | 43us   | 29us      | 25us       | 14us    | 29us       | 15us       |
| Update  ~16K entities with 2 systems | 379us     | 152us  | 133us     | 64us       | 56us    | 138us      | 68us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 3ms    | 3ms       | 1ms        | 3ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 25ms      | 13ms   | 12ms      | 7ms        | 13ms    | 12ms       | 14ms       |
| Update   ~2M entities with 2 systems | 52ms      | 27ms   | 26ms      | 15ms       | 25ms    | 24ms       | 28ms       |



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
| Update     8 entities with 2 systems | 160ns     | 88ns   | 56ns      | 15722ns    | 1097ns  | 54ns       | 131ns      |
| Update    16 entities with 2 systems | 296ns     | 150ns  | 109ns     | 15910ns    | 1132ns  | 94ns       | 147ns      |
| Update    32 entities with 2 systems | 590ns     | 303ns  | 207ns     | 15384ns    | 1178ns  | 191ns      | 192ns      |
| Update    64 entities with 2 systems | 1159ns    | 558ns  | 479ns     | 15746ns    | 1276ns  | 350ns      | 296ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 15us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 20us      | 8us    | 7us       | 18us       | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 98us      | 32us   | 28us      | 28us       | 14us    | 32us       | 16us       |
| Update  ~16K entities with 2 systems | 337us     | 141us  | 131us     | 63us       | 56us    | 163us      | 69us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 6ms       | 3ms    | 3ms       | 1ms        | 2ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 24ms      | 12ms   | 12ms      | 7ms        | 12ms    | 13ms       | 15ms       |
| Update   ~2M entities with 2 systems | 56ms      | 27ms   | 25ms      | 15ms       | 26ms    | 25ms       | 29ms       |


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
| Update     8 entities with 7 systems | 462ns  | 961ns            | 248ns          | 314ns           | 203ns     | 50857ns    | 2098ns  | 250ns      | 332ns      | 344ns            |
| Update    16 entities with 7 systems | 728ns  | 1801ns           | 394ns          | 541ns           | 392ns     | 50477ns    | 2177ns  | 434ns      | 406ns      | 441ns            |
| Update    32 entities with 7 systems | 1329ns | 3439ns           | 738ns          | 1120ns          | 744ns     | 52654ns    | 2318ns  | 783ns      | 562ns      | 576ns            |
| Update    64 entities with 7 systems | 2606ns | 6885ns           | 1254ns         | 1998ns          | 1443ns    | 50860ns    | 2659ns  | 1491ns     | 831ns      | 885ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 systems | 11us   | 27us             | 6us            | 9us             | 5us       | 52us       | 4us     | 5us        | 3us        | 3us              |
| Update   ~1K entities with 7 systems | 46us   | 118us            | 30us           | 39us            | 22us      | 57us       | 10us    | 23us       | 12us       | 14us             |
| Update   ~4K entities with 7 systems | 208us  | 468us            | 144us          | 165us           | 95us      | 79us       | 36us    | 90us       | 70us       | 71us             |
| Update  ~16K entities with 7 systems | 802us  | 1882us           | 617us          | 647us           | 430us     | 189us      | 198us   | 422us      | 350us      | 324us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 systems | 3ms    | 7ms              | 2ms            | 2ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 systems | 14ms   | 30ms             | 11ms           | 11ms            | 8ms       | 4ms        | 6ms     | 7ms        | 10ms       | 11ms             |
| Update   ~1M entities with 7 systems | 60ms   | 120ms            | 51ms           | 45ms            | 34ms      | 16ms       | 25ms    | 29ms       | 43ms       | 45ms             |
| Update   ~2M entities with 7 systems | 115ms  | 229ms            | 121ms          | 90ms            | 71ms      | 38ms       | 42ms    | 62ms       | 86ms       | 91ms             |



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
| Update     8 entities with 7 Systems | 362ns  | 696ns            | 201ns          | 246ns           | 147ns     | 54871ns    | 2312ns  | 179ns      | 407ns      | 410ns            |
| Update    16 entities with 7 Systems | 363ns  | 868ns            | 188ns          | 176ns           | 196ns     | 51732ns    | 2187ns  | 178ns      | 308ns      | 344ns            |
| Update    32 entities with 7 Systems | 598ns  | 1610ns           | 286ns          | 230ns           | 367ns     | 51734ns    | 2256ns  | 320ns      | 379ns      | 393ns            |
| Update    64 entities with 7 Systems | 1056ns | 3003ns           | 496ns          | 342ns           | 717ns     | 51066ns    | 2390ns  | 555ns      | 512ns      | 533ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 20us             | 4us            | 5us             | 4us       | 53us       | 3us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 31us   | 84us             | 18us           | 21us            | 16us      | 63us       | 9us     | 17us       | 9us        | 10us             |
| Update   ~4K entities with 7 Systems | 137us  | 343us            | 91us           | 88us            | 69us      | 83us       | 29us    | 79us       | 45us       | 45us             |
| Update  ~16K entities with 7 Systems | 557us  | 1393us           | 377us          | 367us           | 282us     | 151us      | 115us   | 296us      | 216us      | 208us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 23ms             | 8ms            | 6ms             | 6ms       | 3ms        | 4ms     | 5ms        | 7ms        | 8ms              |
| Update   ~1M entities with 7 Systems | 41ms   | 91ms             | 35ms           | 26ms            | 26ms      | 13ms       | 20ms    | 23ms       | 32ms       | 32ms             |
| Update   ~2M entities with 7 Systems | 85ms   | 187ms            | 88ms           | 52ms            | 53ms      | 30ms       | 41ms    | 47ms       | 65ms       | 66ms             |



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

