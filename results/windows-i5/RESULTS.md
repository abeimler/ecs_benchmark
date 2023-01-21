# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is faster)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update  ~16K entities with 2 systems | 2685ns    | 1998ns   | 2230ns    | 49206ns    | 2795ns   | 1915ns     |
| Update  ~65K entities with 2 systems | 11177ns   | 7912ns   | 7576ns    | 58104ns    | 8621ns   | 7462ns     |
| Update  262K entities with 2 systems | 43609ns   | 30492ns  | 30147ns   | 83425ns    | 32978ns  | 30876ns    |
| Update   ~1M entities with 2 systems | 165056ns  | 122859ns | 122815ns  | 191628ns   | 132123ns | 124116ns   |
| Update   ~2M entities with 2 systems | 667007ns  | 475179ns | 496687ns  | 568669ns   | 505307ns | 509789ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 2ms       | 1ms    | 2ms       | 2ms        | 2ms     | 1ms        |
| Update  ~65K entities with 2 systems | 10ms      | 7ms    | 8ms       | 8ms        | 7ms     | 7ms        |
| Update  262K entities with 2 systems | 43ms      | 31ms   | 30ms      | 32ms       | 31ms    | 32ms       |
| Update   ~1M entities with 2 systems | 174ms     | 124ms  | 131ms     | 131ms      | 128ms   | 127ms      |
| Update   ~2M entities with 2 systems | 341ms     | 254ms  | 263ms     | 276ms      | 250ms   | 254ms      |



## Benchmarks

### Update systems (for-each entities in 2 systems) with zero entities

![SystemsUpdateNoEntities Plot](img/SystemsUpdateNoEntities.svg)

_(lower is better)_

|                                  | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update 0 entities with 2 systems | 60ns      | 28ns   | 9ns       | 871ns      | 171ns   | 17ns       |




### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 2685ns    | 1998ns   | 2230ns    | 49206ns    | 2795ns   | 1915ns     |
| Update    64 entities with 2 systems | 11177ns   | 7912ns   | 7576ns    | 58104ns    | 8621ns   | 7462ns     |
| Update   256 entities with 2 systems | 43609ns   | 30492ns  | 30147ns   | 83425ns    | 32978ns  | 30876ns    |
| Update   ~1K entities with 2 systems | 165056ns  | 122859ns | 122815ns  | 191628ns   | 132123ns | 124116ns   |
| Update   ~4K entities with 2 systems | 667007ns  | 475179ns | 496687ns  | 568669ns   | 505307ns | 509789ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 2ms       | 1ms    | 2ms       | 2ms        | 2ms     | 1ms        |
| Update  ~65K entities with 2 systems | 10ms      | 7ms    | 8ms       | 8ms        | 7ms     | 7ms        |
| Update  262K entities with 2 systems | 43ms      | 31ms   | 30ms      | 32ms       | 31ms    | 32ms       |
| Update   ~1M entities with 2 systems | 174ms     | 124ms  | 131ms     | 131ms      | 128ms   | 127ms      |
| Update   ~2M entities with 2 systems | 341ms     | 254ms  | 263ms     | 276ms      | 250ms   | 254ms      |


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 2346ns    | 1814ns   | 1906ns    | 52481ns    | 2658ns   | 1427ns     |
| Update    64 entities with 2 systems | 9585ns    | 6815ns   | 7887ns    | 59133ns    | 8529ns   | 5891ns     |
| Update   256 entities with 2 systems | 42767ns   | 29108ns  | 32694ns   | 86376ns    | 34004ns  | 31239ns    |
| Update   ~1K entities with 2 systems | 167940ns  | 123873ns | 129782ns  | 193138ns   | 133359ns | 117492ns   |
| Update   ~4K entities with 2 systems | 674415ns  | 498037ns | 530123ns  | 586558ns   | 533264ns | 505028ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 2ms       | 1ms    | 2ms       | 2ms        | 2ms     | 1ms        |
| Update  ~65K entities with 2 systems | 10ms      | 7ms    | 8ms       | 7ms        | 8ms     | 7ms        |
| Update  262K entities with 2 systems | 39ms      | 31ms   | 34ms      | 32ms       | 31ms    | 31ms       |
| Update   ~1M entities with 2 systems | 174ms     | 122ms  | 136ms     | 129ms      | 130ms   | 125ms      |
| Update   ~2M entities with 2 systems | 340ms     | 257ms  | 274ms     | 266ms      | 255ms   | 254ms      |





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

