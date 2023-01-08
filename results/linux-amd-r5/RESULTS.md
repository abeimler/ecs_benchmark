# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update  ~16K entities with 2 systems | 1781ns    | 1601ns   | 1901ns    | 67473ns    | 2068ns   | 1492ns     |
| Update  ~65K entities with 2 systems | 6986ns    | 6028ns   | 6889ns    | 74531ns    | 6202ns   | 5926ns     |
| Update  262K entities with 2 systems | 27604ns   | 24079ns  | 27438ns   | 89616ns    | 22681ns  | 23490ns    |
| Update   ~1M entities with 2 systems | 109156ns  | 93349ns  | 103881ns  | 164338ns   | 88204ns  | 93159ns    |
| Update   ~2M entities with 2 systems | 431842ns  | 370726ns | 422970ns  | 428359ns   | 348574ns | 366802ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 6ms       | 5ms    | 6ms       | 6ms        | 5ms     | 5ms        |
| Update  262K entities with 2 systems | 27ms      | 22ms   | 26ms      | 23ms       | 21ms    | 22ms       |
| Update   ~1M entities with 2 systems | 109ms     | 89ms   | 104ms     | 92ms       | 86ms    | 89ms       |
| Update   ~2M entities with 2 systems | 218ms     | 179ms  | 211ms     | 185ms      | 174ms   | 179ms      |



## Benchmarks

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
* **CPU:** 3.89GHz @ 12Cores
* **RAM:** 15.55GB

