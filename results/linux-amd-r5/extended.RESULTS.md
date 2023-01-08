# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update  ~16K entities with 3 systems | 1666ns   | 2043ns           | 1627ns         | 1579ns          | 1443ns    | 101691ns   | 2345ns   | 1506ns     |
| Update  ~65K entities with 3 systems | 6348ns   | 7998ns           | 6166ns         | 6018ns          | 5610ns    | 103423ns   | 6856ns   | 5940ns     |
| Update  262K entities with 3 systems | 24776ns  | 31727ns          | 24223ns        | 23344ns         | 22382ns   | 126647ns   | 24728ns  | 23620ns    |
| Update   ~1M entities with 3 systems | 98674ns  | 125218ns         | 96505ns        | 91802ns         | 89267ns   | 204558ns   | 94102ns  | 94276ns    |
| Update   ~2M entities with 3 systems | 389218ns | 487819ns         | 379311ns       | 360516ns        | 360383ns  | 477473ns   | 364371ns | 371452ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 1ms    | 1ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 systems | 5ms    | 7ms              | 5ms            | 5ms             | 5ms       | 5ms        | 5ms     | 5ms        |
| Update  262K entities with 3 systems | 24ms   | 30ms             | 25ms           | 22ms            | 23ms      | 24ms       | 23ms    | 23ms       |
| Update   ~1M entities with 3 systems | 96ms   | 119ms            | 109ms          | 90ms            | 91ms      | 96ms       | 91ms    | 90ms       |
| Update   ~2M entities with 3 systems | 194ms  | 239ms            | 270ms          | 181ms           | 183ms     | 191ms      | 181ms   | 182ms      |



## Benchmarks

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


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with two components | 9ns                        | 17ns                      | 7ns                           |
| Iterate over    64 entities with two components | 45ns                       | 82ns                      | 32ns                          |
| Iterate over   256 entities with two components | 144ns                      | 331ns                     | 114ns                         |
| Iterate over   ~1K entities with two components | 540ns                      | 1317ns                    | 430ns                         |
| Iterate over   ~4K entities with two components | 2127ns                     | 27944ns                   | 1698ns                        |

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with two components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with two components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with two components | 4ms                        | 14ms                      | 4ms                           |


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.png)

_(lower is better)_

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with three components | 7ns                        | 13ns                      | 7ns                           |
| Iterate over    64 entities with three components | 33ns                       | 51ns                      | 31ns                          |
| Iterate over   256 entities with three components | 144ns                      | 327ns                     | 144ns                         |
| Iterate over   ~1K entities with three components | 536ns                      | 1218ns                    | 537ns                         |
| Iterate over   ~4K entities with three components | 2110ns                     | 4856ns                    | 2109ns                        |

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with three components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with three components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with three components | 4ms                        | 14ms                      | 4ms                           |





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

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.1.3

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: v2.0.0




### Environment

* **OS:** Linux
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 15.55GB

