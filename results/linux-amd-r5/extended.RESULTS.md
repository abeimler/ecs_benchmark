# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update  ~16K entities with 3 systems | 3491ns   | 4048ns           | 3462ns         | 3416ns          | 3476ns    | 104112ns   | 4271ns   |
| Update  ~65K entities with 3 systems | 14197ns  | 16855ns          | 14286ns        | 14028ns         | 14345ns   | 124710ns   | 15006ns  |
| Update  262K entities with 3 systems | 55721ns  | 65505ns          | 54760ns        | 54997ns         | 56989ns   | 168987ns   | 55906ns  |
| Update   ~1M entities with 3 systems | 217934ns | 254836ns         | 214747ns       | 221677ns        | 228271ns  | 323446ns   | 216283ns |
| Update   ~2M entities with 3 systems | 859448ns | 987339ns         | 839617ns       | 856380ns        | 868681ns  | 950704ns   | 855218ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 systems | 13ms   | 15ms             | 13ms           | 13ms            | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 3 systems | 55ms   | 64ms             | 57ms           | 55ms            | 56ms      | 53ms       | 55ms    |
| Update   ~1M entities with 3 systems | 223ms  | 258ms            | 263ms          | 220ms           | 223ms     | 215ms      | 220ms   |
| Update   ~2M entities with 3 systems | 440ms  | 535ms            | 610ms          | 442ms           | 446ms     | 435ms      | 438ms   |



## Benchmarks

### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 systems | 3491ns   | 4048ns           | 3462ns         | 3416ns          | 3476ns    | 104112ns   | 4271ns   |
| Update    64 entities with 3 systems | 14197ns  | 16855ns          | 14286ns        | 14028ns         | 14345ns   | 124710ns   | 15006ns  |
| Update   256 entities with 3 systems | 55721ns  | 65505ns          | 54760ns        | 54997ns         | 56989ns   | 168987ns   | 55906ns  |
| Update   ~1K entities with 3 systems | 217934ns | 254836ns         | 214747ns       | 221677ns        | 228271ns  | 323446ns   | 216283ns |
| Update   ~4K entities with 3 systems | 859448ns | 987339ns         | 839617ns       | 856380ns        | 868681ns  | 950704ns   | 855218ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 systems | 13ms   | 15ms             | 13ms           | 13ms            | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 3 systems | 55ms   | 64ms             | 57ms           | 55ms            | 56ms      | 53ms       | 55ms    |
| Update   ~1M entities with 3 systems | 223ms  | 258ms            | 263ms          | 220ms           | 223ms     | 215ms      | 220ms   |
| Update   ~2M entities with 3 systems | 440ms  | 535ms            | 610ms          | 442ms           | 446ms     | 435ms      | 438ms   |


### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 Systems | 3060ns   | 3511ns           | 2988ns         | 3029ns          | 3032ns    | 111552ns   | 3956ns   |
| Update    64 entities with 3 Systems | 13060ns  | 15271ns          | 12677ns        | 13032ns         | 13179ns   | 129333ns   | 14082ns  |
| Update   256 entities with 3 Systems | 55713ns  | 65685ns          | 54073ns        | 55158ns         | 56406ns   | 154110ns   | 55632ns  |
| Update   ~1K entities with 3 Systems | 219349ns | 253519ns         | 215628ns       | 217068ns        | 227745ns  | 325840ns   | 225262ns |
| Update   ~4K entities with 3 Systems | 857519ns | 980429ns         | 837731ns       | 849060ns        | 881086ns  | 971967ns   | 854226ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 Systems | 13ms   | 15ms             | 13ms           | 14ms            | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 3 Systems | 58ms   | 64ms             | 58ms           | 54ms            | 56ms      | 53ms       | 54ms    |
| Update   ~1M entities with 3 Systems | 220ms  | 256ms            | 270ms          | 222ms           | 223ms     | 216ms      | 219ms   |
| Update   ~2M entities with 3 Systems | 439ms  | 518ms            | 648ms          | 440ms           | 445ms     | 439ms      | 441ms   |


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with two components | 9ns                        | 17ns                      | 9ns                           |
| Iterate over    64 entities with two components | 45ns                       | 83ns                      | 45ns                          |
| Iterate over   256 entities with two components | 144ns                      | 331ns                     | 145ns                         |
| Iterate over   ~1K entities with two components | 542ns                      | 1319ns                    | 541ns                         |
| Iterate over   ~4K entities with two components | 2126ns                     | 8393ns                    | 2125ns                        |

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
| Iterate over    16 entities with three components | 6ns                        | 13ns                      | 6ns                           |
| Iterate over    64 entities with three components | 33ns                       | 51ns                      | 33ns                          |
| Iterate over   256 entities with three components | 144ns                      | 326ns                     | 144ns                         |
| Iterate over   ~1K entities with three components | 536ns                      | 1217ns                    | 537ns                         |
| Iterate over   ~4K entities with three components | 2109ns                     | 4876ns                    | 2111ns                        |

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




### Environment

* **OS:** Linux
* **CPU:** 3.36GHz @ 12Cores
* **RAM:** 15.55GB

