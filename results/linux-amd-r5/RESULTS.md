# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is faster)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update  ~16K entities with 2 systems | 1896ns    | 1582ns   | 1513ns    | 10693ns    | 3046ns   | 1509ns     |
| Update  ~65K entities with 2 systems | 7021ns    | 6370ns   | 5972ns    | 15035ns    | 8567ns   | 5931ns     |
| Update  262K entities with 2 systems | 27914ns   | 24363ns  | 23848ns   | 31699ns    | 28082ns  | 23732ns    |
| Update   ~1M entities with 2 systems | 107835ns  | 93592ns  | 95078ns   | 97670ns    | 105934ns | 91998ns    |
| Update   ~2M entities with 2 systems | 464062ns  | 366421ns | 382524ns  | 361184ns   | 416798ns | 366435ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 7ms       | 5ms    | 6ms       | 5ms        | 6ms     | 5ms        |
| Update  262K entities with 2 systems | 27ms      | 25ms   | 25ms      | 23ms       | 25ms    | 24ms       |
| Update   ~1M entities with 2 systems | 113ms     | 96ms   | 96ms      | 92ms       | 102ms   | 95ms       |
| Update   ~2M entities with 2 systems | 233ms     | 193ms  | 196ms     | 185ms      | 206ms   | 191ms      |



## Benchmarks

### Update systems (for-each entities in 2 systems) with zero entities

![SystemsUpdateNoEntities Plot](img/SystemsUpdateNoEntities.svg)

_(lower is better)_

|                                  | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:---------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update 0 entities with 2 systems | 36ns      | 19ns   | 8ns       | 298ns      | 357ns   | 10ns       |




### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 1896ns    | 1582ns   | 1513ns    | 10693ns    | 3046ns   | 1509ns     |
| Update    64 entities with 2 systems | 7021ns    | 6370ns   | 5972ns    | 15035ns    | 8567ns   | 5931ns     |
| Update   256 entities with 2 systems | 27914ns   | 24363ns  | 23848ns   | 31699ns    | 28082ns  | 23732ns    |
| Update   ~1K entities with 2 systems | 107835ns  | 93592ns  | 95078ns   | 97670ns    | 105934ns | 91998ns    |
| Update   ~4K entities with 2 systems | 464062ns  | 366421ns | 382524ns  | 361184ns   | 416798ns | 366435ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 7ms       | 5ms    | 6ms       | 5ms        | 6ms     | 5ms        |
| Update  262K entities with 2 systems | 27ms      | 25ms   | 25ms      | 23ms       | 25ms    | 24ms       |
| Update   ~1M entities with 2 systems | 113ms     | 96ms   | 96ms      | 92ms       | 102ms   | 95ms       |
| Update   ~2M entities with 2 systems | 233ms     | 193ms  | 196ms     | 185ms      | 206ms   | 191ms      |


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.svg)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    | pico_ecs   |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|:-----------|
| Update    16 entities with 2 systems | 1741ns    | 1382ns   | 1314ns    | 12076ns    | 2901ns   | 1082ns     |
| Update    64 entities with 2 systems | 7357ns    | 5892ns   | 5498ns    | 15774ns    | 7967ns   | 4392ns     |
| Update   256 entities with 2 systems | 27980ns   | 24349ns  | 23812ns   | 32926ns    | 28531ns  | 24260ns    |
| Update   ~1K entities with 2 systems | 112417ns  | 94608ns  | 94073ns   | 99601ns    | 106679ns | 91252ns    |
| Update   ~4K entities with 2 systems | 442703ns  | 365843ns | 375218ns  | 362228ns   | 412745ns | 369230ns   |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   | pico_ecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|:-----------|
| Update  ~16K entities with 2 systems | 1ms       | 1ms    | 1ms       | 1ms        | 1ms     | 1ms        |
| Update  ~65K entities with 2 systems | 6ms       | 5ms    | 6ms       | 5ms        | 6ms     | 5ms        |
| Update  262K entities with 2 systems | 28ms      | 23ms   | 24ms      | 23ms       | 25ms    | 29ms       |
| Update   ~1M entities with 2 systems | 119ms     | 93ms   | 96ms      | 92ms       | 103ms   | 98ms       |
| Update   ~2M entities with 2 systems | 227ms     | 184ms  | 194ms     | 184ms      | 210ms   | 197ms      |





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
* **CPU:** 3.38GHz @ 12Cores
* **RAM:** 46.98GB

