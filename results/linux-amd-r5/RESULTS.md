# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Update  ~16K entities with 2 systems | 3721ns    | 3384ns   | 3393ns    | 75296ns    | 4119ns   |
| Update  ~65K entities with 2 systems | 15002ns   | 14123ns  | 13820ns   | 79924ns    | 14207ns  |
| Update  262K entities with 2 systems | 58597ns   | 55094ns  | 54361ns   | 118376ns   | 53516ns  |
| Update   ~1M entities with 2 systems | 231826ns  | 222801ns | 218470ns  | 281026ns   | 207993ns |
| Update   ~2M entities with 2 systems | 925195ns  | 865798ns | 839382ns  | 906501ns   | 825537ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 3ms       | 3ms    | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 2 systems | 14ms      | 13ms   | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 2 systems | 59ms      | 54ms   | 54ms      | 53ms       | 52ms    |
| Update   ~1M entities with 2 systems | 236ms     | 259ms  | 220ms     | 215ms      | 219ms   |
| Update   ~2M entities with 2 systems | 474ms     | 441ms  | 447ms     | 434ms      | 436ms   |



## Benchmarks

### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Update    16 entities with 2 systems | 3721ns    | 3384ns   | 3393ns    | 75296ns    | 4119ns   |
| Update    64 entities with 2 systems | 15002ns   | 14123ns  | 13820ns   | 79924ns    | 14207ns  |
| Update   256 entities with 2 systems | 58597ns   | 55094ns  | 54361ns   | 118376ns   | 53516ns  |
| Update   ~1K entities with 2 systems | 231826ns  | 222801ns | 218470ns  | 281026ns   | 207993ns |
| Update   ~4K entities with 2 systems | 925195ns  | 865798ns | 839382ns  | 906501ns   | 825537ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 3ms       | 3ms    | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 2 systems | 14ms      | 13ms   | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 2 systems | 59ms      | 54ms   | 54ms      | 53ms       | 52ms    |
| Update   ~1M entities with 2 systems | 236ms     | 259ms  | 220ms     | 215ms      | 219ms   |
| Update   ~2M entities with 2 systems | 474ms     | 441ms  | 447ms     | 434ms      | 436ms   |


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Update    16 entities with 2 systems | 3182ns    | 3018ns   | 2966ns    | 74918ns    | 3829ns   |
| Update    64 entities with 2 systems | 13531ns   | 12930ns  | 12740ns   | 76463ns    | 13244ns  |
| Update   256 entities with 2 systems | 58837ns   | 55892ns  | 54348ns   | 115454ns   | 53971ns  |
| Update   ~1K entities with 2 systems | 230471ns  | 217400ns | 212944ns  | 276312ns   | 206945ns |
| Update   ~4K entities with 2 systems | 901751ns  | 866759ns | 839655ns  | 902958ns   | 828308ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 3ms       | 3ms    | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 2 systems | 14ms      | 13ms   | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 2 systems | 58ms      | 55ms   | 54ms      | 53ms       | 53ms    |
| Update   ~1M entities with 2 systems | 235ms     | 237ms  | 219ms     | 216ms      | 219ms   |
| Update   ~2M entities with 2 systems | 474ms     | 486ms  | 446ms     | 433ms      | 423ms   |





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
* **CPU:** 3.11GHz @ 12Cores
* **RAM:** 15.55GB

