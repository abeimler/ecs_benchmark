# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is faster)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update  ~16K entities with 3 systems | 2291ns   | 2788ns           | 2219ns         | 2037ns          | 2185ns    | 60460ns    | 2875ns   | 2176ns     |
| Update  ~65K entities with 3 systems | 8966ns   | 10222ns          | 8661ns         | 8199ns          | 8997ns    | 66032ns    | 8897ns   | 8669ns     |
| Update  262K entities with 3 systems | 34637ns  | 44062ns          | 34748ns        | 32032ns         | 32982ns   | 90770ns    | 34325ns  | 31171ns    |
| Update   ~1M entities with 3 systems | 142269ns | 154320ns         | 125597ns       | 116920ns        | 141298ns  | 222356ns   | 137301ns | 134072ns   |
| Update   ~2M entities with 3 systems | 543869ns | 660151ns         | 523573ns       | 504384ns        | 524008ns  | 653492ns   | 511592ns | 515628ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 2ms    | 2ms              | 1ms            | 1ms             | 2ms       | 2ms        | 2ms     | 2ms        |
| Update  ~65K entities with 3 systems | 8ms    | 10ms             | 8ms            | 8ms             | 8ms       | 8ms        | 8ms     | 8ms        |
| Update  262K entities with 3 systems | 35ms   | 40ms             | 35ms           | 32ms            | 37ms      | 35ms       | 32ms    | 34ms       |
| Update   ~1M entities with 3 systems | 139ms  | 169ms            | 140ms          | 135ms           | 141ms     | 140ms      | 134ms   | 131ms      |
| Update   ~2M entities with 3 systems | 281ms  | 333ms            | 314ms          | 253ms           | 289ms     | 274ms      | 258ms   | 267ms      |



## Benchmarks

### Update systems (for-each entities in 3 systems) with zero entities

![ComplexSystemsUpdateNoEntities Plot](img/ComplexSystemsUpdateNoEntities.svg)

_(lower is better)_

|                                  | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update 0 entities with 3 systems | 58ns   | 58ns             | 72ns           | 55ns            | 17ns      | 1206ns     | 182ns   | 20ns       |




### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 systems | 2291ns   | 2788ns           | 2219ns         | 2037ns          | 2185ns    | 60460ns    | 2875ns   | 2176ns     |
| Update    64 entities with 3 systems | 8966ns   | 10222ns          | 8661ns         | 8199ns          | 8997ns    | 66032ns    | 8897ns   | 8669ns     |
| Update   256 entities with 3 systems | 34637ns  | 44062ns          | 34748ns        | 32032ns         | 32982ns   | 90770ns    | 34325ns  | 31171ns    |
| Update   ~1K entities with 3 systems | 142269ns | 154320ns         | 125597ns       | 116920ns        | 141298ns  | 222356ns   | 137301ns | 134072ns   |
| Update   ~4K entities with 3 systems | 543869ns | 660151ns         | 523573ns       | 504384ns        | 524008ns  | 653492ns   | 511592ns | 515628ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 systems | 2ms    | 2ms              | 1ms            | 1ms             | 2ms       | 2ms        | 2ms     | 2ms        |
| Update  ~65K entities with 3 systems | 8ms    | 10ms             | 8ms            | 8ms             | 8ms       | 8ms        | 8ms     | 8ms        |
| Update  262K entities with 3 systems | 35ms   | 40ms             | 35ms           | 32ms            | 37ms      | 35ms       | 32ms    | 34ms       |
| Update   ~1M entities with 3 systems | 139ms  | 169ms            | 140ms          | 135ms           | 141ms     | 140ms      | 134ms   | 131ms      |
| Update   ~2M entities with 3 systems | 281ms  | 333ms            | 314ms          | 253ms           | 289ms     | 274ms      | 258ms   | 267ms      |


### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 3 Systems | 1999ns   | 2393ns           | 1802ns         | 1941ns          | 1982ns    | 76626ns    | 2882ns   | 1491ns     |
| Update    64 entities with 3 Systems | 7983ns   | 10009ns          | 7635ns         | 7741ns          | 8096ns    | 84918ns    | 8584ns   | 6019ns     |
| Update   256 entities with 3 Systems | 36375ns  | 41837ns          | 32447ns        | 33191ns         | 34553ns   | 141405ns   | 34176ns  | 32490ns    |
| Update   ~1K entities with 3 Systems | 135318ns | 168011ns         | 125215ns       | 129986ns        | 137297ns  | 230756ns   | 131291ns | 131605ns   |
| Update   ~4K entities with 3 Systems | 546840ns | 625270ns         | 527831ns       | 525150ns        | 532250ns  | 660085ns   | 510250ns | 511695ns   |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 3 Systems | 2ms    | 2ms              | 1ms            | 1ms             | 2ms       | 2ms        | 1ms     | 2ms        |
| Update  ~65K entities with 3 Systems | 8ms    | 10ms             | 8ms            | 8ms             | 8ms       | 8ms        | 7ms     | 8ms        |
| Update  262K entities with 3 Systems | 34ms   | 39ms             | 32ms           | 32ms            | 35ms      | 33ms       | 32ms    | 33ms       |
| Update   ~1M entities with 3 Systems | 137ms  | 165ms            | 163ms          | 130ms           | 146ms     | 135ms      | 127ms   | 132ms      |
| Update   ~2M entities with 3 Systems | 273ms  | 340ms            | 328ms          | 253ms           | 285ms     | 268ms      | 261ms   | 264ms      |


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.svg)

_(lower is better)_

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with two components | 23ns                       | 27ns                      | 22ns                          |
| Iterate over    64 entities with two components | 55ns                       | 80ns                      | 55ns                          |
| Iterate over   256 entities with two components | 181ns                      | 408ns                     | 186ns                         |
| Iterate over   ~1K entities with two components | 703ns                      | 1153ns                    | 747ns                         |
| Iterate over   ~4K entities with two components | 2795ns                     | 4507ns                    | 2873ns                        |

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over   ~1M entities with two components | 0ms                        | 2ms                       | 0ms                           |
| Iterate over   ~2M entities with two components | 1ms                        | 4ms                       | 1ms                           |


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.svg)

_(lower is better)_

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with three components | 20ns                       | 22ns                      | 19ns                          |
| Iterate over    64 entities with three components | 42ns                       | 58ns                      | 42ns                          |
| Iterate over   256 entities with three components | 186ns                      | 282ns                     | 183ns                         |
| Iterate over   ~1K entities with three components | 699ns                      | 1132ns                    | 708ns                         |
| Iterate over   ~4K entities with three components | 2797ns                     | 4487ns                    | 2803ns                        |

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over   ~1M entities with three components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~2M entities with three components | 1ms                        | 5ms                       | 1ms                           |





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
* **CPU:** 2.31GHz @ 8Cores
* **RAM:** 7.63GB

