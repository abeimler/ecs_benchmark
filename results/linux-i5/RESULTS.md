# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

None

None



## Benchmarks

### Update systems (for-each entities in 2 systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:----------|:----------|:-----------|:---------|
| Update    16 entities with 2 systems | 4583ns    | 3930ns    | 4237ns    | 29076ns    | 5938ns   |
| Update    64 entities with 2 systems | 18142ns   | 16065ns   | 15883ns   | 40558ns    | 17545ns  |
| Update   256 entities with 2 systems | 72598ns   | 62608ns   | 62870ns   | 88057ns    | 63986ns  |
| Update   ~1K entities with 2 systems | 293879ns  | 252387ns  | 271564ns  | 285355ns   | 250973ns |
| Update   ~4K entities with 2 systems | 1120748ns | 1052854ns | 1053486ns | 1024286ns  | 968006ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 4ms       | 4ms    | 3ms       | 3ms        | 4ms     |
| Update  ~65K entities with 2 systems | 19ms      | 17ms   | 16ms      | 15ms       | 15ms    |
| Update  262K entities with 2 systems | 80ms      | 65ms   | 65ms      | 68ms       | 67ms    |
| Update   ~1M entities with 2 systems | 298ms     | 277ms  | 261ms     | 256ms      | 272ms   |
| Update   ~2M entities with 2 systems | 601ms     | 528ms  | 523ms     | 516ms      | 509ms   |


### Update systems (for-each entities (with mixed components) in 2 systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:----------|:----------|:----------|:-----------|:---------|
| Update    16 entities with 2 systems | 4014ns    | 3694ns    | 3808ns    | 23653ns    | 6146ns   |
| Update    64 entities with 2 systems | 17622ns   | 14390ns   | 15512ns   | 34366ns    | 16599ns  |
| Update   256 entities with 2 systems | 72753ns   | 63009ns   | 67528ns   | 96210ns    | 64041ns  |
| Update   ~1K entities with 2 systems | 292561ns  | 252674ns  | 253654ns  | 286156ns   | 250901ns |
| Update   ~4K entities with 2 systems | 1117589ns | 1050923ns | 1010579ns | 1079594ns  | 965099ns |

|                                      | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Update  ~16K entities with 2 systems | 4ms       | 3ms    | 3ms       | 4ms        | 3ms     |
| Update  ~65K entities with 2 systems | 18ms      | 16ms   | 15ms      | 17ms       | 16ms    |
| Update  262K entities with 2 systems | 74ms      | 69ms   | 69ms      | 64ms       | 63ms    |
| Update   ~1M entities with 2 systems | 323ms     | 260ms  | 277ms     | 256ms      | 252ms   |
| Update   ~2M entities with 2 systems | 600ms     | 534ms  | 572ms     | 563ms      | 506ms   |





### Candidates

#### EntityX by @alecthomas 

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack 

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: 3.10.1

#### Ginseng by @apples 

> Ginseng is an entity-component-system (ECS) library designed for use in games.

The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.

Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (Dec 2021)

#### mustache by @kirillochnev 

> A fast, modern C++ Entity Component System

Version: 0.2 (Feb 2022)

#### OpenEcs by @Gronis 

> Open Ecs is an Entity Component System that uses metaprogramming, cache coherency, and other useful tricks to maximize performance and configurability. It is written in c++11 without further dependencies.

Version: Beta (Apr 2017)

#### Flecs by @SanderMertens 

> Flecs is a fast and lightweight Entity Component System that lets you build games and simulations with millions of entities.

Version: v2.4.8 (Mai 2022)




### Environment

* **OS:** Linux
* **CPU:** 3.10GHz @ 4Cores
* **RAM:** 7.64GB

