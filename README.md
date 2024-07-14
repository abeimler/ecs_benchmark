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
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     1 entities with 7 Systems | 124ns  | 135ns            | 78ns           | 128ns                 | 41ns      | 240ns      | 1921ns  | 65ns       | 222ns      | 231ns            |
| Update     4 entities with 7 Systems | 212ns  | 345ns            | 126ns          | 179ns                 | 115ns     | 460ns      | 3347ns  | 122ns      | 410ns      | 392ns            |
| Update     8 entities with 7 Systems | 334ns  | 632ns            | 181ns          | 255ns                 | 165ns     | 521ns      | 3452ns  | 179ns      | 455ns      | 454ns            |
| Update    16 entities with 7 Systems | 332ns  | 835ns            | 177ns          | 181ns                 | 220ns     | 474ns      | 3187ns  | 190ns      | 356ns      | 349ns            |
| Update    32 entities with 7 Systems | 559ns  | 1618ns           | 268ns          | 235ns                 | 370ns     | 545ns      | 3231ns  | 326ns      | 425ns      | 416ns            |
| Update    64 entities with 7 Systems | 1028ns | 3067ns           | 471ns          | 346ns                 | 712ns     | 674ns      | 3399ns  | 563ns      | 568ns      | 571ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 21us             | 3us            | 4us                   | 4us       | 2us        | 4us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 31us   | 87us             | 18us           | 21us                  | 16us      | 7us        | 10us    | 17us       | 10us       | 9us              |
| Update   ~4K entities with 7 Systems | 140us  | 355us            | 93us           | 89us                  | 70us      | 28us       | 32us    | 80us       | 45us       | 46us             |
| Update  ~16K entities with 7 Systems | 576us  | 1439us           | 407us          | 352us                 | 297us     | 122us      | 116us   | 310us      | 215us      | 216us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms                   | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 24ms             | 8ms            | 6ms                   | 6ms       | 3ms        | 4ms     | 5ms        | 7ms        | 7ms              |
| Update   ~1M entities with 7 Systems | 41ms   | 95ms             | 35ms           | 26ms                  | 27ms      | 16ms       | 20ms    | 23ms       | 31ms       | 31ms             |
| Update   ~2M entities with 7 Systems | 84ms   | 183ms            | 86ms           | 52ms                  | 54ms      | 32ms       | 38ms    | 49ms       | 62ms       | 65ms             |



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

* **OS:** Linux 64-Bit (Kernel: 6.9.9)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 14.1.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs    | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:---------|:-----------|:-----------|
| Create     1 entities with two Components | 1457ns    | 2868ns | 10034ns   | 2456ns     | 401342ns | 1334ns     | 4512ns     |
| Create     4 entities with two Components | 1776ns    | 3182ns | 10260ns   | 2819ns     | 405156ns | 1419ns     | 4894ns     |
| Create     8 entities with two Components | 2144ns    | 3467ns | 10459ns   | 3148ns     | 407955ns | 1501ns     | 5399ns     |
| Create    16 entities with two Components | 2820ns    | 3801ns | 10748ns   | 3722ns     | 408108ns | 1650ns     | 6339ns     |
| Create    32 entities with two Components | 4036ns    | 4476ns | 11280ns   | 4817ns     | 414509ns | 1954ns     | 8284ns     |
| Create    64 entities with two Components | 6410ns    | 5742ns | 12245ns   | 6935ns     | 422601ns | 2563ns     | 12306ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create   256 entities with two Components | 20us      | 13us   | 16us      | 19us       | 486us   | 6us        | 35us       |
| Create   ~1K entities with two Components | 74us      | 41us   | 33us      | 68us       | 740us   | 20us       | 124us      |
| Create   ~4K entities with two Components | 292us     | 155us  | 100us     | 264us      | 1813us  | 90us       | 481us      |
| Create  ~16K entities with two Components | 1163us    | 625us  | 357us     | 1047us     | 5902us  | 355us      | 1929us     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~65K entities with two Components | 4ms       | 2ms    | 1ms       | 4ms        | 21ms    | 1ms        | 7ms        |
| Create  262K entities with two Components | 18ms      | 10ms   | 8ms       | 17ms       | 89ms    | 6ms        | 35ms       |
| Create   ~1M entities with two Components | 91ms      | 66ms   | 55ms      | 88ms       | 371ms   | 44ms       | 147ms      |
| Create   ~2M entities with two Components | 180ms     | 128ms  | 103ms     | 172ms      | 721ms   | 74ms       | 303ms      |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                            | EntityX   | EnTT   | Ginseng   | Flecs    | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:-----------|:-----------|
| Destroy     1 entities with two components | 1123ns    | 1053ns | 1174ns    | 349451ns | 1318ns     | 2940ns     |
| Destroy     4 entities with two components | 1266ns    | 1123ns | 1492ns    | 350054ns | 1355ns     | 3212ns     |
| Destroy     8 entities with two components | 1455ns    | 1312ns | 1902ns    | 351086ns | 1374ns     | 3642ns     |
| Destroy    16 entities with two components | 1783ns    | 1609ns | 2621ns    | 351077ns | 1420ns     | 4603ns     |
| Destroy    32 entities with two components | 2476ns    | 2425ns | 4029ns    | 351619ns | 1553ns     | 6430ns     |
| Destroy    64 entities with two components | 3937ns    | 3701ns | 6836ns    | 353878ns | 1728ns     | 10340ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy   256 entities with two components | 12us      | 11us   | 23us      | 362us   | 2us        | 30us       |
| Destroy   ~1K entities with two components | 48us      | 43us   | 89us      | 400us   | 7us        | 113us      |
| Destroy   ~4K entities with two components | 198us     | 159us  | 353us     | 553us   | 29us       | 463us      |
| Destroy  ~16K entities with two components | 811us     | 633us  | 1408us    | 1162us  | 111us      | 1862us     |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 3ms     | 0ms        | 7ms        |
| Destroy  262K entities with two components | 13ms      | 10ms   | 23ms      | 16ms    | 1ms        | 33ms       |
| Destroy   ~1M entities with two components | 63ms      | 44ms   | 98ms      | 59ms    | 10ms       | 186ms      |
| Destroy   ~2M entities with two components | 125ms     | 86ms   | 189ms     | 114ms   | 18ms       | 409ms      |



### Get one component from entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in     1 entities | 3ns       | 3ns    | 1ns       | 10ns       | 26ns    | 1ns        | 2ns        |
| Unpack one component in     4 entities | 14ns      | 12ns   | 6ns       | 48ns       | 105ns   | 5ns        | 10ns       |
| Unpack one component in     8 entities | 28ns      | 25ns   | 13ns      | 88ns       | 205ns   | 11ns       | 22ns       |
| Unpack one component in    16 entities | 57ns      | 50ns   | 27ns      | 172ns      | 400ns   | 26ns       | 43ns       |
| Unpack one component in    32 entities | 115ns     | 104ns  | 60ns      | 335ns      | 800ns   | 48ns       | 82ns       |
| Unpack one component in    64 entities | 231ns     | 204ns  | 112ns     | 651ns      | 1596ns  | 89ns       | 163ns      |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 2us        | 6us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 10us       | 25us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 14us      | 12us   | 7us       | 41us       | 101us   | 5us        | 10us       |
| Unpack one component in  ~16K entities | 59us      | 51us   | 28us      | 195us      | 417us   | 21us       | 42us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 2ms        | 6ms     | 0ms        | 0ms        |
| Unpack one component in   ~1M entities | 4ms       | 3ms    | 2ms       | 11ms       | 27ms    | 1ms        | 3ms        |
| Unpack one component in   ~2M entities | 9ms       | 7ms    | 4ms       | 23ms       | 52ms    | 2ms        | 7ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in     1 entities | 7ns       | 6ns    | 3ns       | 22ns       | 51ns    | 2ns        | 4ns        |
| Unpack two components in     4 entities | 28ns      | 25ns   | 13ns      | 112ns      | 204ns   | 11ns       | 16ns       |
| Unpack two components in     8 entities | 57ns      | 50ns   | 27ns      | 211ns      | 406ns   | 21ns       | 38ns       |
| Unpack two components in    16 entities | 115ns     | 104ns  | 54ns      | 440ns      | 802ns   | 47ns       | 71ns       |
| Unpack two components in    32 entities | 231ns     | 204ns  | 109ns     | 697ns      | 1617ns  | 88ns       | 138ns      |
| Unpack two components in    64 entities | 462ns     | 404ns  | 223ns     | 1384ns     | 3219ns  | 171ns      | 266ns      |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in   256 entities | 1us       | 1us    | 0us       | 5us        | 12us    | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 6us    | 3us       | 22us       | 50us    | 2us        | 4us        |
| Unpack two components in   ~4K entities | 29us      | 25us   | 14us      | 111us      | 203us   | 10us       | 17us       |
| Unpack two components in  ~16K entities | 118us     | 103us  | 56us      | 452us      | 813us   | 42us       | 67us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 2ms        | 3ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 1ms    | 0ms       | 9ms        | 13ms    | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 9ms       | 6ms    | 3ms       | 39ms       | 51ms    | 2ms        | 5ms        |
| Unpack two components in   ~2M entities | 18ms      | 13ms   | 7ms       | 74ms       | 105ms   | 5ms        | 11ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_Graph shows cost per entity, tables shows total cost. lower is faster._

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     1 entities | 7ns       | 12ns   | 6ns       | 22ns       | 104ns   | 3ns        | 9ns        |
| Unpack three components in     2 entities | 14ns      | 24ns   | 12ns      | 44ns       | 212ns   | 7ns        | 18ns       |
| Unpack three components in     8 entities | 57ns      | 99ns   | 47ns      | 181ns      | 842ns   | 34ns       | 75ns       |
| Unpack three components in    16 entities | 115ns     | 195ns  | 96ns      | 353ns      | 1644ns  | 63ns       | 144ns      |
| Unpack three components in    32 entities | 231ns     | 387ns  | 195ns     | 697ns      | 3276ns  | 121ns      | 278ns      |
| Unpack three components in    64 entities | 464ns     | 772ns  | 385ns     | 1399ns     | 6569ns  | 236ns      | 549ns      |
| Unpack three components in   128 entities | 930ns     | 1548ns | 772ns     | 2792ns     | 13068ns | 467ns      | 1093ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   512 entities | 3us       | 6us    | 3us       | 11us       | 52us    | 1us        | 4us        |
| Unpack three components in   ~2K entities | 14us      | 24us   | 12us      | 44us       | 209us   | 7us        | 17us       |
| Unpack three components in   ~8K entities | 59us      | 100us  | 50us      | 196us      | 859us   | 29us       | 70us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 3ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 0ms       | 2ms        | 13ms    | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 6ms    | 3ms       | 13ms       | 53ms    | 1ms        | 5ms        |
| Unpack three components in   ~1M entities | 9ms       | 13ms   | 7ms       | 24ms       | 109ms   | 3ms        | 11ms       |



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
| Remove and Add a Component in     1 entities | 15ns      | 24ns   | 10ns      | 258ns   | 7ns        | 119ns      |
| Remove and Add a Component in     4 entities | 59ns      | 107ns  | 42ns      | 946ns   | 39ns       | 522ns      |
| Remove and Add a Component in     8 entities | 125ns     | 203ns  | 90ns      | 1892ns  | 69ns       | 1031ns     |
| Remove and Add a Component in    16 entities | 244ns     | 397ns  | 176ns     | 3799ns  | 131ns      | 2058ns     |
| Remove and Add a Component in    32 entities | 480ns     | 781ns  | 348ns     | 7573ns  | 257ns      | 4102ns     |
| Remove and Add a Component in    64 entities | 952ns     | 1554ns | 959ns     | 15096ns | 507ns      | 8220ns     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in   256 entities | 3us       | 6us    | 3us       | 60us    | 2us        | 32us       |
| Remove and Add a Component in   ~1K entities | 15us      | 25us   | 12us      | 240us   | 8us        | 136us      |
| Remove and Add a Component in   ~4K entities | 60us      | 102us  | 45us      | 961us   | 32us       | 544us      |
| Remove and Add a Component in  ~16K entities | 244us     | 453us  | 183us     | 3887us  | 130us      | 2172us     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~65K entities | 0ms       | 1ms    | 0ms       | 15ms    | 0ms        | 8ms        |
| Remove and Add a Component in  262K entities | 3ms       | 6ms    | 2ms       | 61ms    | 2ms        | 34ms       |
| Remove and Add a Component in   ~1M entities | 15ms      | 26ms   | 11ms      | 245ms   | 8ms        | 141ms      |
| Remove and Add a Component in   ~2M entities | 31ms      | 52ms   | 23ms      | 489ms   | 16ms       | 279ms      |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


  Cost per entity                         |  Cost of all entities
:-------------------------------------------:|:------------------------------------------------------:
  ![SystemsUpdate Plot](img/SystemsUpdate.svg)  |  ![SystemsUpdate Line Plot](img/LineSystemsUpdate.svg)  


_Tables shows total cost. lower is faster._

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update     1 entities with 2 systems | 39ns      | 27ns   | 13ns      | 66ns       | 1292ns  | 20ns       | 84ns       |
| Update     4 entities with 2 systems | 93ns      | 60ns   | 34ns      | 79ns       | 1298ns  | 39ns       | 100ns      |
| Update     8 entities with 2 systems | 166ns     | 97ns   | 59ns      | 95ns       | 1307ns  | 65ns       | 118ns      |
| Update    16 entities with 2 systems | 315ns     | 159ns  | 109ns     | 123ns      | 1349ns  | 132ns      | 148ns      |
| Update    32 entities with 2 systems | 649ns     | 296ns  | 216ns     | 174ns      | 1382ns  | 241ns      | 199ns      |
| Update    64 entities with 2 systems | 1167ns    | 561ns  | 423ns     | 286ns      | 1511ns  | 459ns      | 308ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 4us       | 2us    | 1us       | 0us        | 2us     | 1us        | 0us        |
| Update   ~1K entities with 2 systems | 20us      | 8us    | 8us       | 3us        | 4us     | 7us        | 3us        |
| Update   ~4K entities with 2 systems | 73us      | 34us   | 31us      | 13us       | 15us    | 29us       | 16us       |
| Update  ~16K entities with 2 systems | 314us     | 143us  | 127us     | 54us       | 56us    | 115us      | 66us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 2ms    | 2ms       | 1ms        | 3ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 21ms      | 12ms   | 11ms      | 8ms        | 13ms    | 10ms       | 13ms       |
| Update   ~2M entities with 2 systems | 44ms      | 25ms   | 23ms      | 16ms       | 25ms    | 22ms       | 27ms       |



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
| Update     1 entities with 2 systems | 31ns      | 16ns   | 7ns       | 36ns       | 532ns   | 14ns       | 42ns       |
| Update     4 entities with 2 systems | 75ns      | 44ns   | 28ns      | 123ns      | 1458ns  | 33ns       | 114ns      |
| Update     8 entities with 2 systems | 139ns     | 77ns   | 51ns      | 154ns      | 1472ns  | 53ns       | 148ns      |
| Update    16 entities with 2 systems | 271ns     | 140ns  | 93ns      | 183ns      | 1500ns  | 88ns       | 147ns      |
| Update    32 entities with 2 systems | 537ns     | 275ns  | 196ns     | 251ns      | 1543ns  | 180ns      | 204ns      |
| Update    64 entities with 2 systems | 1094ns    | 538ns  | 400ns     | 338ns      | 1650ns  | 329ns      | 315ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 4us       | 2us    | 1us       | 1us        | 2us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 18us      | 8us    | 6us       | 3us        | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 73us      | 32us   | 26us      | 14us       | 15us    | 36us       | 16us       |
| Update  ~16K entities with 2 systems | 345us     | 131us  | 127us     | 55us       | 56us    | 166us      | 67us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 3ms    | 2ms       | 2ms        | 2ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 21ms      | 14ms   | 11ms      | 7ms        | 13ms    | 11ms       | 13ms       |
| Update   ~2M entities with 2 systems | 44ms      | 29ms   | 23ms      | 15ms       | 26ms    | 23ms       | 27ms       |


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
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     1 entities with 7 systems | 136ns  | 173ns            | 100ns          | 133ns                 | 51ns      | 223ns      | 2930ns  | 64ns       | 290ns      | 280ns            |
| Update     4 entities with 7 systems | 301ns  | 504ns            | 181ns          | 216ns                 | 119ns     | 273ns      | 2948ns  | 132ns      | 326ns      | 318ns            |
| Update     8 entities with 7 systems | 463ns  | 960ns            | 254ns          | 316ns                 | 201ns     | 325ns      | 2958ns  | 243ns      | 375ns      | 361ns            |
| Update    16 entities with 7 systems | 727ns  | 1813ns           | 429ns          | 527ns                 | 392ns     | 398ns      | 3040ns  | 439ns      | 465ns      | 449ns            |
| Update    32 entities with 7 systems | 1332ns | 3574ns           | 723ns          | 999ns                 | 728ns     | 536ns      | 3174ns  | 788ns      | 615ns      | 606ns            |
| Update    64 entities with 7 systems | 2655ns | 7155ns           | 1388ns         | 2257ns                | 1348ns    | 833ns      | 3492ns  | 1482ns     | 956ns      | 943ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 systems | 11us   | 29us             | 6us            | 9us                   | 5us       | 2us        | 5us     | 6us        | 3us        | 3us              |
| Update   ~1K entities with 7 systems | 48us   | 116us            | 30us           | 38us                  | 21us      | 8us        | 11us    | 22us       | 14us       | 13us             |
| Update   ~4K entities with 7 systems | 200us  | 481us            | 154us          | 164us                 | 93us      | 39us       | 38us    | 92us       | 72us       | 71us             |
| Update  ~16K entities with 7 systems | 830us  | 1990us           | 606us          | 648us                 | 371us     | 182us      | 173us   | 407us      | 341us      | 346us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 systems | 3ms    | 7ms              | 2ms            | 2ms                   | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 systems | 14ms   | 32ms             | 11ms           | 11ms                  | 7ms       | 4ms        | 5ms     | 7ms        | 10ms       | 10ms             |
| Update   ~1M entities with 7 systems | 58ms   | 123ms            | 52ms           | 45ms                  | 30ms      | 17ms       | 21ms    | 29ms       | 43ms       | 42ms             |
| Update   ~2M entities with 7 systems | 113ms  | 233ms            | 122ms          | 90ms                  | 59ms      | 42ms       | 44ms    | 61ms       | 85ms       | 85ms             |



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
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update     1 entities with 7 Systems | 124ns  | 135ns            | 78ns           | 128ns                 | 41ns      | 240ns      | 1921ns  | 65ns       | 222ns      | 231ns            |
| Update     4 entities with 7 Systems | 212ns  | 345ns            | 126ns          | 179ns                 | 115ns     | 460ns      | 3347ns  | 122ns      | 410ns      | 392ns            |
| Update     8 entities with 7 Systems | 334ns  | 632ns            | 181ns          | 255ns                 | 165ns     | 521ns      | 3452ns  | 179ns      | 455ns      | 454ns            |
| Update    16 entities with 7 Systems | 332ns  | 835ns            | 177ns          | 181ns                 | 220ns     | 474ns      | 3187ns  | 190ns      | 356ns      | 349ns            |
| Update    32 entities with 7 Systems | 559ns  | 1618ns           | 268ns          | 235ns                 | 370ns     | 545ns      | 3231ns  | 326ns      | 425ns      | 416ns            |
| Update    64 entities with 7 Systems | 1028ns | 3067ns           | 471ns          | 346ns                 | 712ns     | 674ns      | 3399ns  | 563ns      | 568ns      | 571ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 7 Systems | 7us    | 21us             | 3us            | 4us                   | 4us       | 2us        | 4us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 7 Systems | 31us   | 87us             | 18us           | 21us                  | 16us      | 7us        | 10us    | 17us       | 10us       | 9us              |
| Update   ~4K entities with 7 Systems | 140us  | 355us            | 93us           | 89us                  | 70us      | 28us       | 32us    | 80us       | 45us       | 46us             |
| Update  ~16K entities with 7 Systems | 576us  | 1439us           | 407us          | 352us                 | 297us     | 122us      | 116us   | 310us      | 215us      | 216us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 7 Systems | 2ms    | 5ms              | 1ms            | 1ms                   | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 7 Systems | 10ms   | 24ms             | 8ms            | 6ms                   | 6ms       | 3ms        | 4ms     | 5ms        | 7ms        | 7ms              |
| Update   ~1M entities with 7 Systems | 41ms   | 95ms             | 35ms           | 26ms                  | 27ms      | 16ms       | 20ms    | 23ms       | 31ms       | 31ms             |
| Update   ~2M entities with 7 Systems | 84ms   | 183ms            | 86ms           | 52ms                  | 54ms      | 32ms       | 38ms    | 49ms       | 62ms       | 65ms             |



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

You can use `-DCMAKE_BUILD_TYPE=Debug` to enable Sanitizers.


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

Version: v3.13.2

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

Version: v4.0.0

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: 2.3 (Sep 2023)

#### gaia-ecs by @richardbiely 

> Gaia-ECS is a fast and easy-to-use ECS framework.

Version: v0.8.6

