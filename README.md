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

_(lower is better)_

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update    16 entities with 5 Systems | 358ns  | 828ns            | 175ns          | 165ns           | 212ns     | 51901ns    | 2263ns  | 187ns      | 322ns      | 353ns            |
| Update    64 entities with 5 Systems | 1054ns | 2967ns           | 464ns          | 335ns           | 739ns     | 53999ns    | 2374ns  | 598ns      | 563ns      | 574ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 5 Systems | 7us    | 20us             | 3us            | 5us             | 4us       | 53us       | 3us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 5 Systems | 31us   | 88us             | 19us           | 21us            | 17us      | 64us       | 9us     | 17us       | 10us       | 10us             |
| Update   ~4K entities with 5 Systems | 144us  | 340us            | 93us           | 88us            | 71us      | 83us       | 32us    | 74us       | 48us       | 50us             |
| Update  ~16K entities with 5 Systems | 588us  | 1407us           | 396us          | 361us           | 292us     | 182us      | 119us   | 328us      | 216us      | 224us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 5 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 5 Systems | 10ms   | 23ms             | 8ms            | 6ms             | 6ms       | 3ms        | 3ms     | 5ms        | 8ms        | 9ms              |
| Update   ~1M entities with 5 Systems | 42ms   | 90ms             | 36ms           | 26ms            | 26ms      | 13ms       | 21ms    | 24ms       | 36ms       | 34ms             |
| Update   ~2M entities with 5 Systems | 85ms   | 180ms            | 92ms           | 54ms            | 54ms      | 30ms       | 41ms    | 49ms       | 69ms       | 66ms             |



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

* **OS:** Linux
* **CPU:** 0.00GHz @ 0Cores
* **RAM:** 46.97GB


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_(lower is better)_

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs    | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:---------|:-----------|:-----------|
| Create    16 entities with two Components | 3003ns    | 4116ns | 10796ns   | 3780ns     | 507015ns | 1861ns     | 10090ns    |
| Create    64 entities with two Components | 6693ns    | 6275ns | 12260ns   | 7012ns     | 499577ns | 2842ns     | 17431ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create   256 entities with two Components | 21us      | 14us   | 17us      | 19us       | 543us   | 7us        | 45us       |
| Create   ~1K entities with two Components | 78us      | 45us   | 35us      | 68us       | 726us   | 23us       | 158us      |
| Create   ~4K entities with two Components | 305us     | 168us  | 104us     | 268us      | 1597us  | 103us      | 658us      |
| Create  ~16K entities with two Components | 1208us    | 669us  | 375us     | 1078us     | 5118us  | 405us      | 3445us     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~65K entities with two Components | 4ms       | 2ms    | 1ms       | 4ms        | 16ms    | 1ms        | 29ms       |
| Create  262K entities with two Components | 19ms      | 11ms   | 8ms       | 17ms       | 65ms    | 8ms        | 425ms      |
| Create   ~1M entities with two Components | 92ms      | 72ms   | 58ms      | 87ms       | 303ms   | 51ms       | 6003ms     |
| Create   ~2M entities with two Components | 181ms     | 134ms  | 105ms     | 169ms      | 571ms   | 73ms       | 23199ms    |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_(lower is better)_

|                                            | EntityX   | EnTT   | Ginseng   | Flecs    | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:---------|:-----------|:-----------|
| Destroy    16 entities with two components | 1978ns    | 1736ns | 2695ns    | 450281ns | 1591ns     | 6133ns     |
| Destroy    64 entities with two components | 4296ns    | 3421ns | 7005ns    | 432994ns | 2012ns     | 14450ns    |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy   256 entities with two components | 13us      | 10us   | 23us      | 437us   | 3us        | 39us       |
| Destroy   ~1K entities with two components | 50us      | 37us   | 91us      | 496us   | 10us       | 140us      |
| Destroy   ~4K entities with two components | 204us     | 146us  | 363us     | 739us   | 40us       | 561us      |
| Destroy  ~16K entities with two components | 836us     | 588us  | 1448us    | 1467us  | 158us      | 2252us     |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 4ms     | 0ms        | 9ms        |
| Destroy  262K entities with two components | 14ms      | 9ms    | 24ms      | 16ms    | 2ms        | 44ms       |
| Destroy   ~1M entities with two components | 64ms      | 42ms   | 100ms     | 61ms    | 13ms       | 218ms      |
| Destroy   ~2M entities with two components | 128ms     | 84ms   | 193ms     | 122ms   | 24ms       | 556ms      |



### Get one component from entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_(lower is better)_

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in    16 entities | 58ns      | 56ns   | 31ns      | 188ns      | 423ns   | 36ns       | 50ns       |
| Unpack one component in    64 entities | 233ns     | 229ns  | 117ns     | 761ns      | 1724ns  | 127ns      | 185ns      |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 3us        | 6us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 12us       | 26us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 14us      | 14us   | 7us       | 50us       | 107us   | 7us        | 11us       |
| Unpack one component in  ~16K entities | 59us      | 57us   | 30us      | 194us      | 422us   | 30us       | 48us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 3ms        | 6ms     | 0ms        | 1ms        |
| Unpack one component in   ~1M entities | 4ms       | 4ms    | 2ms       | 13ms       | 27ms    | 1ms        | 4ms        |
| Unpack one component in   ~2M entities | 9ms       | 8ms    | 4ms       | 27ms       | 55ms    | 3ms        | 9ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_(lower is better)_

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in    16 entities | 116ns     | 139ns  | 56ns      | 351ns      | 860ns   | 58ns       | 74ns       |
| Unpack two components in    64 entities | 477ns     | 543ns  | 229ns     | 1401ns     | 3358ns  | 212ns      | 279ns      |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in   256 entities | 1us       | 2us    | 0us       | 5us        | 13us    | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 8us    | 3us       | 22us       | 53us    | 3us        | 4us        |
| Unpack two components in   ~4K entities | 29us      | 34us   | 14us      | 97us       | 214us   | 13us       | 18us       |
| Unpack two components in  ~16K entities | 119us     | 137us  | 57us      | 362us      | 854us   | 52us       | 73us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 3ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 2ms    | 0ms       | 6ms        | 13ms    | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 8ms       | 9ms    | 3ms       | 25ms       | 54ms    | 3ms        | 5ms        |
| Unpack two components in   ~2M entities | 18ms      | 18ms   | 7ms       | 54ms       | 110ms   | 6ms        | 11ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_(lower is better)_

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     8 entities | 58ns      | 116ns  | 49ns      | 180ns      | 1218ns  | 42ns       | 86ns       |
| Unpack three components in    32 entities | 238ns     | 456ns  | 200ns     | 722ns      | 4783ns  | 151ns      | 323ns      |
| Unpack three components in   128 entities | 939ns     | 1807ns | 788ns     | 2892ns     | 19454ns | 578ns      | 1254ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   512 entities | 3us       | 7us    | 3us       | 11us       | 76us    | 2us        | 4us        |
| Unpack three components in   ~2K entities | 14us      | 29us   | 12us      | 48us       | 305us   | 9us        | 19us       |
| Unpack three components in   ~8K entities | 60us      | 117us  | 50us      | 186us      | 1250us  | 37us       | 81us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 0ms       | 3ms        | 19ms    | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 8ms    | 3ms       | 12ms       | 78ms    | 2ms        | 6ms        |
| Unpack three components in   ~1M entities | 9ms       | 16ms   | 8ms       | 25ms       | 159ms   | 4ms        | 14ms       |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component


![RemoveAddComponent Plot](img/RemoveAddComponent.svg)

_(lower is better)_

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in    16 entities | 245ns     | 447ns  | 189ns     | 3499ns  | 154ns      | 2829ns     |
| Remove and Add a Component in    64 entities | 960ns     | 1773ns | 739ns     | 13960ns | 583ns      | 11912ns    |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in   256 entities | 3us       | 7us    | 2us       | 55us    | 2us        | 45us       |
| Remove and Add a Component in   ~1K entities | 15us      | 28us   | 11us      | 222us   | 9us        | 182us      |
| Remove and Add a Component in   ~4K entities | 62us      | 115us  | 60us      | 878us   | 37us       | 741us      |
| Remove and Add a Component in  ~16K entities | 246us     | 454us  | 191us     | 3552us  | 149us      | 4039us     |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 13ms    | 0ms        | 35ms       |
| Remove and Add a Component in  262K entities | 4ms       | 7ms    | 3ms       | 56ms    | 2ms        | 404ms      |
| Remove and Add a Component in   ~1M entities | 16ms      | 29ms   | 12ms      | 226ms   | 9ms        | 6115ms     |
| Remove and Add a Component in   ~2M entities | 32ms      | 58ms   | 24ms      | 474ms   | 19ms       | 23899ms    |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


![SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is better)_

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update    16 entities with 2 systems | 362ns     | 175ns  | 116ns     | 15048ns    | 1066ns  | 150ns      | 128ns      |
| Update    64 entities with 2 systems | 1328ns    | 580ns  | 446ns     | 14441ns    | 1226ns  | 483ns      | 293ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 15us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 20us      | 8us    | 6us       | 17us       | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 97us      | 35us   | 27us      | 25us       | 14us    | 39us       | 16us       |
| Update  ~16K entities with 2 systems | 385us     | 143us  | 117us     | 62us       | 56us    | 181us      | 69us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 5ms       | 3ms    | 2ms       | 1ms        | 3ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 24ms      | 12ms   | 10ms      | 7ms        | 13ms    | 12ms       | 15ms       |
| Update   ~2M entities with 2 systems | 58ms      | 25ms   | 21ms      | 15ms       | 26ms    | 24ms       | 31ms       |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update    16 entities with 2 systems | 294ns     | 145ns  | 96ns      | 15785ns    | 1154ns  | 94ns       | 153ns      |
| Update    64 entities with 2 systems | 1205ns    | 545ns  | 415ns     | 15571ns    | 1317ns  | 351ns      | 311ns      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update   256 entities with 2 systems | 5us       | 2us    | 1us       | 16us       | 1us     | 1us        | 1us        |
| Update   ~1K entities with 2 systems | 25us      | 8us    | 6us       | 19us       | 4us     | 7us        | 4us        |
| Update   ~4K entities with 2 systems | 93us      | 32us   | 27us      | 28us       | 14us    | 30us       | 16us       |
| Update  ~16K entities with 2 systems | 409us     | 135us  | 132us     | 64us       | 56us    | 163us      | 71us       |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~65K entities with 2 systems | 1ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Update  262K entities with 2 systems | 6ms       | 3ms    | 2ms       | 1ms        | 2ms     | 2ms        | 3ms        |
| Update   ~1M entities with 2 systems | 28ms      | 13ms   | 11ms      | 7ms        | 13ms    | 12ms       | 16ms       |
| Update   ~2M entities with 2 systems | 53ms      | 27ms   | 22ms      | 14ms       | 26ms    | 25ms       | 34ms       |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 7 systems)


![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)

_(lower is better)_

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update    16 entities with 5 systems | 745ns  | 1830ns           | 404ns          | 579ns           | 405ns     | 52834ns    | 2225ns  | 458ns      | 416ns      | 490ns            |
| Update    64 entities with 5 systems | 2611ns | 6939ns           | 1253ns         | 2200ns          | 1431ns    | 51933ns    | 2607ns  | 1481ns     | 868ns      | 1102ns           |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 5 systems | 10us   | 27us             | 6us            | 9us             | 5us       | 52us       | 4us     | 5us        | 3us        | 3us              |
| Update   ~1K entities with 5 systems | 46us   | 117us            | 28us           | 40us            | 23us      | 58us       | 10us    | 23us       | 14us       | 15us             |
| Update   ~4K entities with 5 systems | 201us  | 462us            | 143us          | 166us           | 102us     | 85us       | 38us    | 90us       | 73us       | 75us             |
| Update  ~16K entities with 5 systems | 853us  | 1836us           | 588us          | 631us           | 415us     | 212us      | 171us   | 407us      | 368us      | 327us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 5 systems | 3ms    | 7ms              | 2ms            | 2ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 2ms              |
| Update  262K entities with 5 systems | 14ms   | 30ms             | 11ms           | 11ms            | 8ms       | 3ms        | 5ms     | 7ms        | 11ms       | 12ms             |
| Update   ~1M entities with 5 systems | 58ms   | 118ms            | 54ms           | 45ms            | 31ms      | 16ms       | 27ms    | 29ms       | 44ms       | 50ms             |
| Update   ~2M entities with 5 systems | 113ms  | 240ms            | 119ms          | 94ms            | 64ms      | 39ms       | 51ms    | 60ms       | 95ms       | 103ms            |



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


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update    16 entities with 5 Systems | 358ns  | 828ns            | 175ns          | 165ns           | 212ns     | 51901ns    | 2263ns  | 187ns      | 322ns      | 353ns            |
| Update    64 entities with 5 Systems | 1054ns | 2967ns           | 464ns          | 335ns           | 739ns     | 53999ns    | 2374ns  | 598ns      | 563ns      | 574ns            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update   256 entities with 5 Systems | 7us    | 20us             | 3us            | 5us             | 4us       | 53us       | 3us     | 4us        | 2us        | 2us              |
| Update   ~1K entities with 5 Systems | 31us   | 88us             | 19us           | 21us            | 17us      | 64us       | 9us     | 17us       | 10us       | 10us             |
| Update   ~4K entities with 5 Systems | 144us  | 340us            | 93us           | 88us            | 71us      | 83us       | 32us    | 74us       | 48us       | 50us             |
| Update  ~16K entities with 5 Systems | 588us  | 1407us           | 396us          | 361us           | 292us     | 182us      | 119us   | 328us      | 216us      | 224us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~65K entities with 5 Systems | 2ms    | 5ms              | 1ms            | 1ms             | 1ms       | 0ms        | 0ms     | 1ms        | 1ms        | 1ms              |
| Update  262K entities with 5 Systems | 10ms   | 23ms             | 8ms            | 6ms             | 6ms       | 3ms        | 3ms     | 5ms        | 8ms        | 9ms              |
| Update   ~1M entities with 5 Systems | 42ms   | 90ms             | 36ms           | 26ms            | 26ms      | 13ms       | 21ms    | 24ms       | 36ms       | 34ms             |
| Update   ~2M entities with 5 Systems | 85ms   | 180ms            | 92ms           | 54ms            | 54ms      | 30ms       | 41ms    | 49ms       | 69ms       | 66ms             |



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

The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.

Any function-like object can be used as a system. The function's parameters are used to determine the required components.

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

