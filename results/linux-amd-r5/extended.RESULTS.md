# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is faster)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update  ~16K entities with 3 systems | 1783ns   | 2419ns           | 1630ns         | 1703ns          | 1722ns    | 16772ns    | 3053ns   | 1714ns     |
| Update  ~65K entities with 3 systems | 6654ns   | 10194ns          | 6668ns         | 6251ns          | 7042ns    | 20810ns    | 7686ns   | 7361ns     |
| Update  262K entities with 3 systems | 27624ns  | 37992ns          | 25053ns        | 24801ns         | 26410ns   | 38904ns    | 26957ns  | 26056ns    |
| Update   ~1M entities with 3 systems | 107331ns | 158191ns         | 98966ns        | 94128ns         | 106460ns  | 107507ns   | 100699ns | 103664ns   |
| Update   ~2M entities with 3 systems | 408430ns | 589992ns         | 390686ns       | 375524ns        | 419782ns  | 385067ns   | 402372ns | 444529ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 systems | 7ms    | 10ms             | 6ms            | 6ms             | 7ms       | 6ms        | 6ms     | 6ms        |
| Update  262K entities with 3 systems | 31ms   | 38ms             | 31ms           | 25ms            | 26ms      | 24ms       | 26ms    | 27ms       |
| Update   ~1M entities with 3 systems | 116ms  | 148ms            | 107ms          | 98ms            | 105ms     | 100ms      | 99ms    | 103ms      |
| Update   ~2M entities with 3 systems | 227ms  | 300ms            | 233ms          | 195ms           | 222ms     | 195ms      | 235ms   | 231ms      |



## Benchmarks

### Update systems (for-each entities in 3 systems) with zero entities

![ComplexSystemsUpdateNoEntities Plot](img/ComplexSystemsUpdateNoEntities.svg)

_(lower is better)_

|                                  | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update 0 entities with 3 systems | 37ns   | 15ns             | 23ns           | 37ns            | 12ns      | 517ns      | 367ns   | 14ns       |




### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 systems | 1783ns   | 2419ns           | 1630ns         | 1703ns          | 1722ns    | 16772ns    | 3053ns   | 1714ns     |
| Update    64 entities with 3 systems | 6654ns   | 10194ns          | 6668ns         | 6251ns          | 7042ns    | 20810ns    | 7686ns   | 7361ns     |
| Update   256 entities with 3 systems | 27624ns  | 37992ns          | 25053ns        | 24801ns         | 26410ns   | 38904ns    | 26957ns  | 26056ns    |
| Update   ~1K entities with 3 systems | 107331ns | 158191ns         | 98966ns        | 94128ns         | 106460ns  | 107507ns   | 100699ns | 103664ns   |
| Update   ~4K entities with 3 systems | 408430ns | 589992ns         | 390686ns       | 375524ns        | 419782ns  | 385067ns   | 402372ns | 444529ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 systems | 7ms    | 10ms             | 6ms            | 6ms             | 7ms       | 6ms        | 6ms     | 6ms        |
| Update  262K entities with 3 systems | 31ms   | 38ms             | 31ms           | 25ms            | 26ms      | 24ms       | 26ms    | 27ms       |
| Update   ~1M entities with 3 systems | 116ms  | 148ms            | 107ms          | 98ms            | 105ms     | 100ms      | 99ms    | 103ms      |
| Update   ~2M entities with 3 systems | 227ms  | 300ms            | 233ms          | 195ms           | 222ms     | 195ms      | 235ms   | 231ms      |


### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 Systems | 1859ns   | 2164ns           | 1810ns         | 1452ns          | 1429ns    | 17379ns    | 2948ns   | 1169ns     |
| Update    64 entities with 3 Systems | 6676ns   | 8988ns           | 6081ns         | 5688ns          | 6042ns    | 22029ns    | 7731ns   | 5463ns     |
| Update   256 entities with 3 Systems | 31071ns  | 38832ns          | 25234ns        | 27911ns         | 26494ns   | 38854ns    | 27001ns  | 25862ns    |
| Update   ~1K entities with 3 Systems | 117242ns | 146701ns         | 104298ns       | 101484ns        | 103017ns  | 115266ns   | 100549ns | 101012ns   |
| Update   ~4K entities with 3 Systems | 437934ns | 623621ns         | 379911ns       | 382385ns        | 424739ns  | 391316ns   | 403532ns | 397232ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 Systems | 1ms    | 2ms              | 1ms            | 1ms             | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 3 Systems | 7ms    | 9ms              | 6ms            | 6ms             | 6ms       | 6ms        | 6ms     | 6ms        |
| Update  262K entities with 3 Systems | 32ms   | 37ms             | 26ms           | 25ms            | 27ms      | 25ms       | 25ms    | 26ms       |
| Update   ~1M entities with 3 Systems | 113ms  | 150ms            | 126ms          | 107ms           | 106ms     | 98ms       | 99ms    | 104ms      |
| Update   ~2M entities with 3 Systems | 225ms  | 356ms            | 272ms          | 205ms           | 211ms     | 208ms      | 200ms   | 213ms      |


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.svg)

_(lower is better)_

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with two components | 8ns                        | 119ns                     | 8ns                           |
| Iterate over    64 entities with two components | 38ns                       | 480ns                     | 38ns                          |
| Iterate over   256 entities with two components | 137ns                      | 1914ns                    | 137ns                         |
| Iterate over   ~1K entities with two components | 534ns                      | 7667ns                    | 533ns                         |
| Iterate over   ~4K entities with two components | 2153ns                     | 30681ns                   | 2138ns                        |

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with two components | 0ms                        | 2ms                       | 0ms                           |
| Iterate over   ~1M entities with two components | 2ms                        | 8ms                       | 2ms                           |
| Iterate over   ~2M entities with two components | 4ms                        | 16ms                      | 4ms                           |


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.svg)

_(lower is better)_

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with three components | 7ns                        | 32ns                      | 6ns                           |
| Iterate over    64 entities with three components | 32ns                       | 119ns                     | 32ns                          |
| Iterate over   256 entities with three components | 146ns                      | 790ns                     | 145ns                         |
| Iterate over   ~1K entities with three components | 542ns                      | 2935ns                    | 539ns                         |
| Iterate over   ~4K entities with three components | 2122ns                     | 11454ns                   | 2173ns                        |

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with three components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with three components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with three components | 4ms                        | 15ms                      | 4ms                           |





### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: v3.12.2

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.

The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.

Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Apr 2023)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v3.2.4

#### pico_ecs by @empyreanx 

> A collection of cross-platform single header libraries written in C. Pure and simple ECS.

Version: 2.2 (Mai 2023)




### Environment

* **OS:** Linux
* **CPU:** 3.44GHz @ 12Cores
* **RAM:** 46.98GB

