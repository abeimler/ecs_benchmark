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


![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs     |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-------------|
| Update    16 entities with 3 Systems | 1455ns   | 1761ns           | 1420ns         | 1382ns          | 1269ns    | 103681ns   | 2259ns   | **1070ns**   |
| Update    64 entities with 3 Systems | 5868ns   | 7347ns           | 5633ns         | 5563ns          | 5177ns    | 108972ns   | 6460ns   | **4171ns**   |
| Update   256 entities with 3 Systems | 24910ns  | 31782ns          | 24361ns        | 23341ns         | 22304ns   | 130812ns   | 24695ns  | **23512ns**  |
| Update   ~1K entities with 3 Systems | 99885ns  | 125085ns         | 95682ns        | 91612ns         | 89084ns   | 201275ns   | 94927ns  | **93549ns**  |
| Update   ~4K entities with 3 Systems | 390637ns | 490440ns         | 378259ns       | 360928ns        | 360946ns  | 490916ns   | 363548ns | **367681ns** |

|                                      | EnTT    | EnTT (runtime) | EnTT (group) | EnTT (stable) | Ginseng | mustache | Flecs     | pico_ecs |
|:-------------------------------------|:--------|:---------------|:-------------|:--------------|:--------|:---------|:----------|:---------|
| Update  ~16K entities with 3 Systems | **1ms** | **1ms**        | **1ms**      | **1ms**       | **1ms** | **1ms**  | **1ms**   | **1ms**  |
| Update  ~65K entities with 3 Systems | **5ms** | 7ms            | **5ms**      | **5ms**       | **5ms** | **5ms**  | **5ms**   | **5ms**  |
| Update  262K entities with 3 Systems | 24ms    | 30ms           | 25ms         | **22ms**      | 23ms    | 24ms     | 23ms      | **22ms** |
| Update   ~1M entities with 3 Systems | 95ms    | 119ms          | 110ms        | **90ms**      | 93ms    | 96ms     | **90ms**  | **90ms** |
| Update   ~2M entities with 3 Systems | 193ms   | 239ms          | 285ms        | **180ms**     | 185ms   | 191ms    | **180ms** | 181ms    |



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

* **OS:** Linux (Kernel: 6.1.3)
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 16GB
* **Compiler:** gcc (GCC) 12.2.0


---

### Create entities


![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     | pico_ecs   |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|:-----------|
| Create    16 entities with two Components | 2628ns    | 2748ns   | 10581ns   | 2985ns     | 652407ns  | 593ns      |
| Create    64 entities with two Components | 6082ns    | 4309ns   | 11995ns   | 5983ns     | 665214ns  | 1025ns     |
| Create   256 entities with two Components | 19214ns   | 10152ns  | 16463ns   | 17605ns    | 739886ns  | 2782ns     |
| Create   ~1K entities with two Components | 71351ns   | 32864ns  | 32361ns   | 62070ns    | 896714ns  | 9716ns     |
| Create   ~4K entities with two Components | 278867ns  | 141754ns | 96061ns   | 237707ns   | 1532600ns | 88776ns    |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 0ms        | 4ms     | 0ms        |
| Create  ~65K entities with two Components | 4ms       | 2ms    | 3ms       | 4ms        | 14ms    | 1ms        |
| Create  262K entities with two Components | 20ms      | 12ms   | 14ms      | 18ms       | 55ms    | 7ms        |
| Create   ~1M entities with two Components | 83ms      | 48ms   | 49ms      | 72ms       | 208ms   | 23ms       |
| Create   ~2M entities with two Components | 164ms     | 91ms   | 94ms      | 143ms      | 402ms   | 46ms       |



### Destroy entities


![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Destroy    16 entities with two components | 1451ns    | 1075ns   | 1970ns    | 671ns      | 393841ns | 545ns      |
| Destroy    64 entities with two components | 3464ns    | 2537ns   | 5391ns    | 807ns      | 396080ns | 725ns      |
| Destroy   256 entities with two components | 11681ns   | 8528ns   | 18841ns   | 1287ns     | 402022ns | 1435ns     |
| Destroy   ~1K entities with two components | 45895ns   | 32234ns  | 72359ns   | 3046ns     | 428988ns | 4301ns     |
| Destroy   ~4K entities with two components | 186443ns  | 127482ns | 285900ns  | 9703ns     | 537208ns | 15811ns    |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 0ms        | 0ms     | 0ms        |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 4ms       | 0ms        | 2ms     | 0ms        |
| Destroy  262K entities with two components | 13ms      | 8ms    | 19ms      | 0ms        | 9ms     | 0ms        |
| Destroy   ~1M entities with two components | 58ms      | 35ms   | 77ms      | 4ms        | 41ms    | 5ms        |
| Destroy   ~2M entities with two components | 117ms     | 72ms   | 154ms     | 8ms        | 79ms    | 10ms       |



### Get one (non-const) component from Entity


![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack one component in    16 entities | 22ns      | 45ns    | 27ns      | 183ns      | 419ns    | 10ns       |
| Unpack one component in    64 entities | 96ns      | 184ns   | 112ns     | 707ns      | 1640ns   | 46ns       |
| Unpack one component in   256 entities | 367ns     | 724ns   | 437ns     | 2720ns     | 6586ns   | 171ns      |
| Unpack one component in   ~1K entities | 1452ns    | 2874ns  | 1748ns    | 10621ns    | 26356ns  | 675ns      |
| Unpack one component in   ~4K entities | 5796ns    | 11562ns | 6948ns    | 44903ns    | 104202ns | 2701ns     |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Unpack one component in  262K entities | 0ms       | 0ms    | 0ms       | 2ms        | 6ms     | 0ms        |
| Unpack one component in   ~1M entities | 1ms       | 3ms    | 1ms       | 11ms       | 26ms    | 0ms        |
| Unpack one component in   ~2M entities | 3ms       | 6ms    | 3ms       | 22ms       | 53ms    | 1ms        |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity


![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:--------|:-----------|
| Get one (const) component in    16 entities | 22ns      | 46ns    | 27ns      | 93ns       | 252ns   | 12ns       |
| Get one (const) component in    64 entities | 95ns      | 190ns   | 112ns     | 359ns      | 988ns   | 55ns       |
| Get one (const) component in   256 entities | 365ns     | 748ns   | 437ns     | 1420ns     | 3947ns  | 211ns      |
| Get one (const) component in   ~1K entities | 1450ns    | 3015ns  | 1751ns    | 5675ns     | 15830ns | 837ns      |
| Get one (const) component in   ~4K entities | 5797ns    | 12041ns | 6990ns    | 22702ns    | 63153ns | 3346ns     |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     | 0ms        |
| Get one (const) component in  262K entities | 0ms       | 0ms    | 0ms       | 1ms        | 4ms     | 0ms        |
| Get one (const) component in   ~1M entities | 1ms       | 3ms    | 1ms       | 5ms        | 16ms    | 0ms        |
| Get one (const) component in   ~2M entities | 3ms       | 6ms    | 3ms       | 11ms       | 32ms    | 1ms        |


**Note:**
* Get one const component
  1. `const PositionComponent`


### Get two components from entity


![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack two components in    16 entities | 41ns      | 93ns    | 54ns      | 360ns      | 676ns    | 22ns       |
| Unpack two components in    64 entities | 172ns     | 365ns   | 221ns     | 1023ns     | 2672ns   | 95ns       |
| Unpack two components in   256 entities | 671ns     | 1450ns  | 875ns     | 4090ns     | 10606ns  | 374ns      |
| Unpack two components in   ~1K entities | 2668ns    | 5804ns  | 3488ns    | 16335ns    | 42460ns  | 1483ns     |
| Unpack two components in   ~4K entities | 10674ns   | 23247ns | 13967ns   | 65838ns    | 169089ns | 5910ns     |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 2ms     | 0ms        |
| Unpack two components in  262K entities | 0ms       | 1ms    | 0ms       | 4ms        | 10ms    | 0ms        |
| Unpack two components in   ~1M entities | 2ms       | 6ms    | 3ms       | 18ms       | 43ms    | 1ms        |
| Unpack two components in   ~2M entities | 5ms       | 12ms   | 7ms       | 37ms       | 86ms    | 3ms        |



**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity


![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|:-----------|
| Unpack three components in     8 entities | 32ns      | 77ns    | 48ns      | 127ns      | 592ns    | 16ns       |
| Unpack three components in    32 entities | 135ns     | 299ns   | 197ns     | 502ns      | 2347ns   | 70ns       |
| Unpack three components in   128 entities | 524ns     | 1193ns  | 777ns     | 1986ns     | 9363ns   | 272ns      |
| Unpack three components in   512 entities | 2083ns    | 4796ns  | 3099ns    | 7971ns     | 37002ns  | 1076ns     |
| Unpack three components in   ~2K entities | 8293ns    | 19090ns | 12407ns   | 31775ns    | 149878ns | 4306ns     |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     | 0ms        |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Unpack three components in  131K entities | 0ms       | 1ms    | 0ms       | 2ms        | 9ms     | 0ms        |
| Unpack three components in  524K entities | 2ms       | 5ms    | 3ms       | 8ms        | 37ms    | 1ms        |
| Unpack three components in   ~1M entities | 4ms       | 10ms   | 6ms       | 17ms       | 74ms    | 2ms        |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component


![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Remove and Add a Component in    16 entities | 294ns     | 427ns    | 187ns     | 958ns      | 2689ns   | 94ns       |
| Remove and Add a Component in    64 entities | 1170ns    | 1674ns   | 736ns     | 3799ns     | 10589ns  | 362ns      |
| Remove and Add a Component in   256 entities | 4681ns    | 6655ns   | 2937ns    | 15180ns    | 42112ns  | 1427ns     |
| Remove and Add a Component in   ~1K entities | 18717ns   | 26667ns  | 11910ns   | 60647ns    | 170502ns | 5690ns     |
| Remove and Add a Component in   ~4K entities | 75062ns   | 105841ns | 47867ns   | 242589ns   | 683467ns | 23006ns    |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     | 0ms        |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 3ms        | 10ms    | 0ms        |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 15ms       | 43ms    | 1ms        |
| Remove and Add a Component in   ~1M entities | 19ms      | 28ms   | 12ms      | 65ms       | 174ms   | 5ms        |
| Remove and Add a Component in   ~2M entities | 38ms      | 55ms   | 24ms      | 140ms      | 348ms   | 13ms       |



**Note:**
* Remove and add `PositionComponent`



### Update systems (for-each entities in 2 systems)


![SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 1781ns    | 1601ns   | 1901ns    | 67473ns    | 2068ns   | 1492ns     |
| Update    64 entities with 2 systems | 6986ns    | 6028ns   | 6889ns    | 74531ns    | 6202ns   | 5926ns     |
| Update   256 entities with 2 systems | 27604ns   | 24079ns  | 27438ns   | 89616ns    | 22681ns  | 23490ns    |
| Update   ~1K entities with 2 systems | 109156ns  | 93349ns  | 103881ns  | 164338ns   | 88204ns  | 93159ns    |
| Update   ~4K entities with 2 systems | 431842ns  | 370726ns | 422970ns  | 428359ns   | 348574ns | 366802ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 6ms       | 5ms    | 6ms       | 6ms        | 5ms     | 5ms        |
| Update  262K entities with 2 systems | 27ms      | 22ms   | 26ms      | 23ms       | 21ms    | 22ms       |
| Update   ~1M entities with 2 systems | 109ms     | 89ms   | 104ms     | 92ms       | 86ms    | 89ms       |
| Update   ~2M entities with 2 systems | 218ms     | 179ms  | 211ms     | 185ms      | 174ms   | 179ms      |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


### Update systems (for-each entities (with mixed components) in 2 systems)


![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 1542ns    | 1347ns   | 1682ns    | 69758ns    | 2006ns   | 1055ns     |
| Update    64 entities with 2 systems | 6385ns    | 5531ns   | 6620ns    | 76723ns    | 5895ns   | 4171ns     |
| Update   256 entities with 2 systems | 27578ns   | 23531ns  | 27584ns   | 93017ns    | 22738ns  | 23526ns    |
| Update   ~1K entities with 2 systems | 108889ns  | 92464ns  | 105542ns  | 176507ns   | 88207ns  | 92361ns    |
| Update   ~4K entities with 2 systems | 430554ns  | 362892ns | 421684ns  | 539253ns   | 352383ns | 362030ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 6ms       | 5ms    | 6ms       | 5ms        | 5ms     | 5ms        |
| Update  262K entities with 2 systems | 27ms      | 22ms   | 26ms      | 23ms       | 21ms    | 22ms       |
| Update   ~1M entities with 2 systems | 108ms     | 89ms   | 99ms      | 92ms       | 86ms    | 88ms       |
| Update   ~2M entities with 2 systems | 218ms     | 179ms  | 183ms     | 184ms      | 172ms   | 180ms      |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)


![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 systems | 1666ns   | 2043ns           | 1627ns         | 1579ns          | 1443ns    | 101691ns   | 2345ns   | 1506ns     |
| Update    64 entities with 3 systems | 6348ns   | 7998ns           | 6166ns         | 6018ns          | 5610ns    | 103423ns   | 6856ns   | 5940ns     |
| Update   256 entities with 3 systems | 24776ns  | 31727ns          | 24223ns        | 23344ns         | 22382ns   | 126647ns   | 24728ns  | 23620ns    |
| Update   ~1K entities with 3 systems | 98674ns  | 125218ns         | 96505ns        | 91802ns         | 89267ns   | 204558ns   | 94102ns  | 94276ns    |
| Update   ~4K entities with 3 systems | 389218ns | 487819ns         | 379311ns       | 360516ns        | 360383ns  | 477473ns   | 364371ns | 371452ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 1ms    | 1ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 systems | 5ms    | 7ms              | 5ms            | 5ms             | 5ms       | 5ms        | 5ms     | 5ms        |
| Update  262K entities with 3 systems | 24ms   | 30ms             | 25ms           | 22ms            | 23ms      | 24ms       | 23ms    | 23ms       |
| Update   ~1M entities with 3 systems | 96ms   | 119ms            | 109ms          | 90ms            | 91ms      | 96ms       | 91ms    | 90ms       |
| Update   ~2M entities with 3 systems | 194ms  | 239ms            | 270ms          | 181ms           | 183ms     | 191ms      | 181ms   | 182ms      |



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

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 Systems | 1455ns   | 1761ns           | 1420ns         | 1382ns          | 1269ns    | 103681ns   | 2259ns   | 1070ns     |
| Update    64 entities with 3 Systems | 5868ns   | 7347ns           | 5633ns         | 5563ns          | 5177ns    | 108972ns   | 6460ns   | 4171ns     |
| Update   256 entities with 3 Systems | 24910ns  | 31782ns          | 24361ns        | 23341ns         | 22304ns   | 130812ns   | 24695ns  | 23512ns    |
| Update   ~1K entities with 3 Systems | 99885ns  | 125085ns         | 95682ns        | 91612ns         | 89084ns   | 201275ns   | 94927ns  | 93549ns    |
| Update   ~4K entities with 3 Systems | 390637ns | 490440ns         | 378259ns       | 360928ns        | 360946ns  | 490916ns   | 363548ns | 367681ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 Systems | 1ms    | 1ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 Systems | 5ms    | 7ms              | 5ms            | 5ms             | 5ms       | 5ms        | 5ms     | 5ms        |
| Update  262K entities with 3 Systems | 24ms   | 30ms             | 25ms           | 22ms            | 23ms      | 24ms       | 23ms    | 22ms       |
| Update   ~1M entities with 3 Systems | 95ms   | 119ms            | 110ms          | 90ms            | 93ms      | 96ms       | 90ms    | 90ms       |
| Update   ~2M entities with 3 Systems | 193ms  | 239ms            | 285ms          | 180ms           | 185ms     | 191ms      | 180ms   | 181ms      |



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
Also you can write tests for the framework example :)
and add some metadata in [plot.config.json](plot.config.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

### Using [Taskfile](https://taskfile.dev/installation/)

1. `git submodule update --init --recursive`
2. Build: `task build`
3. Run (All) Benchmarks: `task benchmark`
4. Plot Graphs: `task plot:all`

You can now find you benchmarks results in [`reports/`](reports/).

_You need python (>=3.9.0) and some [dependencies](scripts/gen-benchmark-report/requirements.txt) to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting)_

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

Version: v3.11.1

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.

The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.

Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Aug 2022)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. 
> It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.1.3

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. 
> Pure and simple ECS.

Version: v2.0.0



#### _Deprecated_

I removed [anax](https://github.com/miguelmartin75/anax) and [Artemis-Cpp](https://github.com/matachi/Artemis-Cpp), they are out-of-date and didn't receive any updates in the last time.
You can still checkout the old versions and branches.
