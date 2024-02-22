# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

This repository contains a collection of benchmarks for popular Entity-Component-System (ECS) frameworks.
The benchmarks cover different aspects of ECS frameworks, such as update systems, component additions/removals, and entity creation/destruction.
It's important to note that different ECS frameworks have different strengths and weaknesses.
For example, some frameworks might excel in adding/removing components, while others might be better at creating/destroying entities.
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

When using ECS frameworks, it's important to benchmark your specific use case and compare the results.
Therefore, the results of these benchmarks should be used as a starting point for your own benchmarking efforts.


### Update systems (for-each entities (with mixed components) in 5 systems)


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT      | EnTT (runtime) | EnTT (group)  | EnTT (stable)  | Ginseng    | mustache | Flecs     | pico_ecs    | gaia-ecs      | gaia-ecs (SoA)   |
|:-------------------------------------|:----------|:---------------|:--------------|:---------------|:-----------|:---------|:----------|:------------|:--------------|:-----------------|
| Update    16 entities with 5 Systems | **1us**   | 2us            | **1us**       | **1us**        | **1us**    | 42us     | 3us       | **1us**     | **1us**       | **1us**          |
| Update    64 entities with 5 Systems | 6us       | 9us            | 6us           | 6us            | 6us        | 48us     | 7us       | **5us**     | 6us           | 6us              |
| Update   256 entities with 5 Systems | 29us      | 43us           | 27us          | 26us           | 27us       | 65us     | 26us      | 26us        | **25us**      | **25us**         |
| Update   ~1K entities with 5 Systems | 118us     | 168us          | 100us         | 102us          | 107us      | 149us    | 101us     | 102us       | **99us**      | **99us**         |
| Update   ~4K entities with 5 Systems | 473us     | 667us          | 414us         | 396us          | 412us      | 480us    | **385us** | 404us       | 400us         | 407us            |

|                                      | EnTT      | EnTT (runtime) | EnTT (group)      | EnTT (stable)        | Ginseng      | mustache       | Flecs             | pico_ecs         | gaia-ecs     | gaia-ecs (SoA)    |
|:-------------------------------------|:----------|:---------------|:------------------|:---------------------|:-------------|:---------------|:------------------|:-----------------|:-------------|:------------------|
| Update  ~16K entities with 5 Systems | **1ms**   | 2ms            | **1ms**           | **1ms**              | **1ms**      | **1ms**        | **1ms**           | **1ms**          | **1ms**      | **1ms**           |
| Update  ~65K entities with 5 Systems | 7ms       | 11ms           | **6ms**           | **6ms**              | **6ms**      | **6ms**        | **6ms**           | **6ms**          | 7ms          | **6ms**           |
| Update  262K entities with 5 Systems | 29ms      | 42ms           | 26ms              | **25ms**             | 27ms         | 27ms           | **25ms**          | **25ms**         | 31ms         | 29ms              |
| Update   ~1M entities with 5 Systems | 116ms     | 173ms          | 112ms             | 103ms                | 118ms        | 108ms          | **102ms**         | 109ms            | 128ms        | 112ms             |
| Update   ~2M entities with 5 Systems | 233ms     | 355ms          | 238ms             | 223ms                | 230ms        | 211ms          | **202ms**         | 214ms            | 240ms        | 228ms             |



While this benchmark only includes up to 5 simple components and 5 small systems,
it's important to note that Entity-Component-Systems can become much more complex in the wild,
with hundreds of components and systems.
Therefore, it's crucial to always benchmark your specific cases and systems when necessary and compare results.
Choose an ECS framework based on its features,
for example, EnTT offers [resource management](https://github.com/skypjack/entt/wiki/Crash-Course:-resource-management) and [event handling](https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between),
while flecs provides useful [add-ons](https://github.com/SanderMertens/flecs#addons),
and EntityX includes a built-in [world/system manager](https://github.com/alecthomas/entityx#manager-tying-it-all-together=).

To evaluate a framework, look at its examples and API design, and pick the one that suits your needs the best.


## Details

### Features

All benchmarks are located in the [`benchmark/benchmarks/`](benchmark/benchmarks/) directory and are implemented with the [google/benchmark](https://github.com/google/benchmark) library.
Each benchmark must implement the `ECSBenchmark.h` template.

Each framework has its own subproject in the [`src/`](src) directory and must implement specific features (see [`src/base`](src/base)).

#### Components

1. `PositionComponent`: includes `x` and `y` coordinates.
2. `VelocityComponent`: includes `x` and `y` coordinates for movement.
3. `DataComponent`: includes some arbitrary data.
4. `HealthComponent`: Hero/Monster data includes HP/MaxHP and status.
5. `DamageComponent`: Hero/Monster data includes damage.

#### Systems

1. `MovementSystem`: updates the `PositionComponent` with a constant `VelocityComponent`.
2. `DataSystem`: updates the `DataComponent` with arbitrary data.
3. `MoreComplexSystem`: updates components with random data and arbitrary information.
4. `HealthSystem`: update Hero/Monster health (update HP and status).
5. `DamageSystem`: update Hero/Monster health by taking damage.


## Additional Benchmarks

Benchmarks for more common features, such as "Creating entities", "Adding and removing components", and others.

### Features tested

* Entity Creation
* Entity Destruction
* Component Retrieval
* Adding and Removing Components
* Systems (for iterating through entities)


### Environment

* **OS:** Linux 64-Bit (Kernel: 6.7.5)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 47GB
* **Compiler:** gcc (GCC) 13.2.1


---

### Create entities


![CreateEntities Plot](img/CreateEntities.svg)

_(lower is better)_

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create    16 entities with two Components | 2us       | 4us    | 10us      | 3us        | 456us   | 1us        | 9us        |
| Create    64 entities with two Components | 6us       | 6us    | 12us      | 6us        | 469us   | 2us        | 16us       |
| Create   256 entities with two Components | 20us      | 14us   | 17us      | 19us       | 507us   | 6us        | 43us       |
| Create   ~1K entities with two Components | 76us      | 48us   | 34us      | 70us       | 701us   | 21us       | 145us      |
| Create   ~4K entities with two Components | 296us     | 195us  | 103us     | 271us      | 1510us  | 95us       | 602us      |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 1ms        | 4ms     | 0ms        | 3ms        |
| Create  ~65K entities with two Components | 5ms       | 2ms    | 1ms       | 4ms        | 16ms    | 1ms        | 31ms       |
| Create  262K entities with two Components | 19ms      | 12ms   | 9ms       | 17ms       | 76ms    | 8ms        | 505ms      |
| Create   ~1M entities with two Components | 101ms     | 82ms   | 61ms      | 97ms       | 282ms   | 46ms       | 8685ms     |
| Create   ~2M entities with two Components | 204ms     | 158ms  | 111ms     | 190ms      | 549ms   | 79ms       | 35776ms    |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.svg)

_(lower is better)_

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy    16 entities with two components | 1us       | 1us    | 2us       | 427us   | 1us        | 5us        |
| Destroy    64 entities with two components | 3us       | 3us    | 7us       | 411us   | 1us        | 13us       |
| Destroy   256 entities with two components | 12us      | 10us   | 24us      | 412us   | 3us        | 37us       |
| Destroy   ~1K entities with two components | 49us      | 40us   | 91us      | 454us   | 9us        | 139us      |
| Destroy   ~4K entities with two components | 198us     | 160us  | 362us     | 610us   | 36us       | 539us      |

|                                            | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 1ms     | 0ms        | 2ms        |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 5ms       | 4ms     | 0ms        | 9ms        |
| Destroy  262K entities with two components | 13ms      | 10ms   | 23ms      | 16ms    | 2ms        | 39ms       |
| Destroy   ~1M entities with two components | 64ms      | 44ms   | 99ms      | 60ms    | 11ms       | 199ms      |
| Destroy   ~2M entities with two components | 130ms     | 88ms   | 192ms     | 116ms   | 21ms       | 477ms      |



### Get one component from Entity


![UnpackOneComponent Plot](img/UnpackOneComponent.svg)

_(lower is better)_

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in    16 entities | 0us       | 0us    | 0us       | 0us        | 0us     | 0us        | 0us        |
| Unpack one component in    64 entities | 0us       | 0us    | 0us       | 0us        | 2us     | 0us        | 0us        |
| Unpack one component in   256 entities | 0us       | 0us    | 0us       | 2us        | 9us     | 0us        | 0us        |
| Unpack one component in   ~1K entities | 3us       | 3us    | 1us       | 11us       | 38us    | 1us        | 2us        |
| Unpack one component in   ~4K entities | 14us      | 14us   | 12us      | 43us       | 154us   | 6us        | 10us       |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        | 0ms        |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        | 0ms        |
| Unpack one component in  262K entities | 1ms       | 0ms    | 0ms       | 3ms        | 9ms     | 0ms        | 0ms        |
| Unpack one component in   ~1M entities | 4ms       | 3ms    | 1ms       | 15ms       | 39ms    | 1ms        | 3ms        |
| Unpack one component in   ~2M entities | 9ms       | 7ms    | 3ms       | 30ms       | 79ms    | 3ms        | 7ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.svg)

_(lower is better)_

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in    16 entities | 0us       | 0us    | 0us       | 0us        | 1us     | 0us        | 0us        |
| Unpack two components in    64 entities | 0us       | 0us    | 0us       | 1us        | 4us     | 0us        | 0us        |
| Unpack two components in   256 entities | 1us       | 1us    | 0us       | 5us        | 19us    | 0us        | 1us        |
| Unpack two components in   ~1K entities | 7us       | 6us    | 3us       | 22us       | 78us    | 3us        | 5us        |
| Unpack two components in   ~4K entities | 30us      | 25us   | 12us      | 88us       | 312us   | 12us       | 22us       |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 5ms     | 0ms        | 0ms        |
| Unpack two components in  262K entities | 2ms       | 1ms    | 0ms       | 6ms        | 20ms    | 0ms        | 1ms        |
| Unpack two components in   ~1M entities | 8ms       | 6ms    | 3ms       | 24ms       | 81ms    | 3ms        | 6ms        |
| Unpack two components in   ~2M entities | 18ms      | 13ms   | 6ms       | 50ms       | 162ms   | 10ms       | 12ms       |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.svg)

_(lower is better)_

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in     8 entities | 0us       | 0us    | 0us       | 0us        | 1us     | 0us        | 0us        |
| Unpack three components in    32 entities | 0us       | 0us    | 0us       | 0us        | 4us     | 0us        | 0us        |
| Unpack three components in   128 entities | 0us       | 1us    | 0us       | 2us        | 18us    | 0us        | 1us        |
| Unpack three components in   512 entities | 3us       | 5us    | 2us       | 11us       | 75us    | 2us        | 5us        |
| Unpack three components in   ~2K entities | 15us      | 20us   | 11us      | 45us       | 298us   | 9us        | 21us       |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        | 0ms        |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        | 0ms        |
| Unpack three components in  131K entities | 1ms       | 1ms    | 0ms       | 3ms        | 19ms    | 0ms        | 1ms        |
| Unpack three components in  524K entities | 4ms       | 5ms    | 3ms       | 12ms       | 77ms    | 2ms        | 6ms        |
| Unpack three components in   ~1M entities | 9ms       | 11ms   | 6ms       | 26ms       | 154ms   | 5ms        | 12ms       |



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
| Remove and Add a Component in    16 entities | 0us       | 0us    | 0us       | 3us     | 0us        | 2us        |
| Remove and Add a Component in    64 entities | 0us       | 1us    | 0us       | 14us    | 0us        | 11us       |
| Remove and Add a Component in   256 entities | 3us       | 6us    | 2us       | 58us    | 2us        | 44us       |
| Remove and Add a Component in   ~1K entities | 15us      | 24us   | 11us      | 238us   | 8us        | 178us      |
| Remove and Add a Component in   ~4K entities | 67us      | 99us   | 53us      | 917us   | 35us       | 736us      |

|                                              | EntityX   | EnTT   | Ginseng   | Flecs   | pico_ecs   | gaia-ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:--------|:-----------|:-----------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 3ms     | 0ms        | 3ms        |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 14ms    | 0ms        | 38ms       |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 59ms    | 2ms        | 540ms      |
| Remove and Add a Component in   ~1M entities | 16ms      | 27ms   | 12ms      | 236ms   | 9ms        | 8285ms     |
| Remove and Add a Component in   ~2M entities | 33ms      | 52ms   | 24ms      | 479ms   | 18ms       | 33176ms    |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


![SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is better)_

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update    16 entities with 2 systems | 1us       | 1us    | 1us       | 16us       | 2us     | 1us        | 1us        |
| Update    64 entities with 2 systems | 7us       | 6us    | 6us       | 21us       | 7us     | 6us        | 6us        |
| Update   256 entities with 2 systems | 28us      | 26us   | 24us      | 41us       | 24us    | 24us       | 24us       |
| Update   ~1K entities with 2 systems | 109us     | 95us   | 101us     | 111us      | 93us    | 94us       | 92us       |
| Update   ~4K entities with 2 systems | 441us     | 384us  | 390us     | 405us      | 368us   | 369us      | 366us      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        | 1ms        |
| Update  ~65K entities with 2 systems | 7ms       | 6ms    | 6ms       | 6ms        | 5ms     | 6ms        | 5ms        |
| Update  262K entities with 2 systems | 28ms      | 24ms   | 24ms      | 25ms       | 23ms    | 23ms       | 25ms       |
| Update   ~1M entities with 2 systems | 115ms     | 98ms   | 98ms      | 101ms      | 101ms   | 95ms       | 107ms      |
| Update   ~2M entities with 2 systems | 236ms     | 191ms  | 213ms     | 203ms      | 194ms   | 196ms      | 209ms      |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update    16 entities with 2 systems | 1us       | 1us    | 1us       | 18us       | 2us     | 1us        | 1us        |
| Update    64 entities with 2 systems | 6us       | 5us    | 5us       | 23us       | 6us     | 4us        | 5us        |
| Update   256 entities with 2 systems | 28us      | 25us   | 24us      | 41us       | 25us    | 25us       | 25us       |
| Update   ~1K entities with 2 systems | 108us     | 95us   | 102us     | 115us      | 93us    | 95us       | 95us       |
| Update   ~4K entities with 2 systems | 435us     | 381us  | 385us     | 405us      | 367us   | 369us      | 371us      |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        | 1ms        |
| Update  ~65K entities with 2 systems | 7ms       | 6ms    | 6ms       | 6ms        | 5ms     | 5ms        | 6ms        |
| Update  262K entities with 2 systems | 28ms      | 24ms   | 24ms      | 25ms       | 23ms    | 23ms       | 25ms       |
| Update   ~1M entities with 2 systems | 113ms     | 96ms   | 100ms     | 102ms      | 98ms    | 95ms       | 104ms      |
| Update   ~2M entities with 2 systems | 229ms     | 192ms  | 197ms     | 202ms      | 189ms   | 190ms      | 205ms      |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 5 systems)


![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)

_(lower is better)_

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update    16 entities with 5 systems | 1us    | 3us              | 1us            | 1us             | 1us       | 38us       | 3us     | 1us        | 1us        | 1us              |
| Update    64 entities with 5 systems | 7us    | 11us             | 6us            | 7us             | 7us       | 43us       | 8us     | 6us        | 6us        | 6us              |
| Update   256 entities with 5 systems | 30us   | 48us             | 26us           | 27us            | 27us      | 62us       | 26us    | 27us       | 26us       | 25us             |
| Update   ~1K entities with 5 systems | 115us  | 190us            | 104us          | 113us           | 106us     | 137us      | 98us    | 104us      | 101us      | 100us            |
| Update   ~4K entities with 5 systems | 468us  | 730us            | 409us          | 423us           | 418us     | 454us      | 391us   | 413us      | 403us      | 395us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~16K entities with 5 systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        | 1ms        | 1ms              |
| Update  ~65K entities with 5 systems | 7ms    | 11ms             | 6ms            | 7ms             | 7ms       | 6ms        | 6ms     | 6ms        | 7ms        | 7ms              |
| Update  262K entities with 5 systems | 30ms   | 49ms             | 28ms           | 27ms            | 29ms      | 27ms       | 25ms    | 26ms       | 30ms       | 30ms             |
| Update   ~1M entities with 5 systems | 123ms  | 189ms            | 125ms          | 110ms           | 116ms     | 107ms      | 100ms   | 107ms      | 128ms      | 113ms            |
| Update   ~2M entities with 5 systems | 248ms  | 396ms            | 288ms          | 221ms           | 237ms     | 216ms      | 203ms   | 220ms      | 245ms      | 238ms            |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
    4. `HealthSystem`
    5. `DamageSystem`
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** gaia-ecs (SoA) iterate via [SoA Layout](https://github.com/richardbiely/gaia-ecs?tab=readme-ov-file#data-layouts) using an `PositionSoA`- und `VelocitySoA`-component



### Update systems (for-each entities (with mixed components) in 5 systems)


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update    16 entities with 5 Systems | 1us    | 2us              | 1us            | 1us             | 1us       | 42us       | 3us     | 1us        | 1us        | 1us              |
| Update    64 entities with 5 Systems | 6us    | 9us              | 6us            | 6us             | 6us       | 48us       | 7us     | 5us        | 6us        | 6us              |
| Update   256 entities with 5 Systems | 29us   | 43us             | 27us           | 26us            | 27us      | 65us       | 26us    | 26us       | 25us       | 25us             |
| Update   ~1K entities with 5 Systems | 118us  | 168us            | 100us          | 102us           | 107us     | 149us      | 101us   | 102us      | 99us       | 99us             |
| Update   ~4K entities with 5 Systems | 473us  | 667us            | 414us          | 396us           | 412us     | 480us      | 385us   | 404us      | 400us      | 407us            |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   | gaia-ecs   | gaia-ecs (SoA)   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|:-----------|:-----------------|
| Update  ~16K entities with 5 Systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        | 1ms        | 1ms              |
| Update  ~65K entities with 5 Systems | 7ms    | 11ms             | 6ms            | 6ms             | 6ms       | 6ms        | 6ms     | 6ms        | 7ms        | 6ms              |
| Update  262K entities with 5 Systems | 29ms   | 42ms             | 26ms           | 25ms            | 27ms      | 27ms       | 25ms    | 25ms       | 31ms       | 29ms             |
| Update   ~1M entities with 5 Systems | 116ms  | 173ms            | 112ms          | 103ms           | 118ms     | 108ms      | 102ms   | 109ms      | 128ms      | 112ms            |
| Update   ~2M entities with 5 Systems | 233ms  | 355ms            | 238ms          | 223ms           | 230ms     | 211ms      | 202ms   | 214ms      | 240ms      | 228ms            |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
    4. `HealthSystem`
    5. `DamageSystem`
* Not every entity has all three components, some got removed
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** gaia-ecs (SoA) iterate via [SoA Layout](https://github.com/richardbiely/gaia-ecs?tab=readme-ov-file#data-layouts) using an `PositionSoA`- und `VelocitySoA`-component


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

_You need python (>=3.8.0) and some [dependencies](scripts/gen-benchmark-report/requirements.txt) to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting), install [pipx](https://pipx.pypa.io/stable/installation/) and [poetry](https://python-poetry.org/docs/#installing-with-pipx) `pipx install poetry`._

Then install dependencies for the script:
```bash
cd ./scripts/gen-benchmark-report && poetry install
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

