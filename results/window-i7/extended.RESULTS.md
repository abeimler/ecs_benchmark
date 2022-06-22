# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:----------|
| Update  ~16K entities with 3 systems | 11692ns   | 9440ns    | 11098ns          | 8050ns         | 8862ns          | 9029ns    | 88231ns    | 11943ns   | 13558ns   |
| Update  ~65K entities with 3 systems | 43626ns   | 36785ns   | 43828ns          | 31634ns        | 35211ns         | 35630ns   | 112388ns   | 44968ns   | 40464ns   |
| Update  262K entities with 3 systems | 173383ns  | 141796ns  | 169792ns         | 124748ns       | 139559ns        | 142625ns  | 222066ns   | 178552ns  | 151251ns  |
| Update   ~1M entities with 3 systems | 694543ns  | 569244ns  | 673371ns         | 502709ns       | 557537ns        | 556947ns  | 647644ns   | 714996ns  | 592964ns  |
| Update   ~2M entities with 3 systems | 2878674ns | 2355741ns | 2699398ns        | 2028502ns      | 2286205ns       | 2290036ns | 2093706ns  | 2889629ns | 2397974ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 systems | 11ms      | 9ms    | 10ms             | 8ms            | 9ms             | 9ms       | 8ms        | 11ms      | 9ms     |
| Update  ~65K entities with 3 systems | 44ms      | 42ms   | 43ms             | 32ms           | 36ms            | 36ms      | 32ms       | 48ms      | 38ms    |
| Update  262K entities with 3 systems | 178ms     | 148ms  | 170ms            | 137ms          | 142ms           | 143ms     | 128ms      | 189ms     | 150ms   |
| Update   ~1M entities with 3 systems | 716ms     | 593ms  | 697ms            | 625ms          | 569ms           | 587ms     | 519ms      | 730ms     | 509ms   |
| Update   ~2M entities with 3 systems | 1418ms    | 1191ms | 1377ms           | 1243ms         | 1148ms          | 1186ms    | 1046ms     | 1494ms    | 1018ms  |



## Benchmarks

### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:----------|
| Update    16 entities with 3 systems | 11692ns   | 9440ns    | 11098ns          | 8050ns         | 8862ns          | 9029ns    | 88231ns    | 11943ns   | 13558ns   |
| Update    64 entities with 3 systems | 43626ns   | 36785ns   | 43828ns          | 31634ns        | 35211ns         | 35630ns   | 112388ns   | 44968ns   | 40464ns   |
| Update   256 entities with 3 systems | 173383ns  | 141796ns  | 169792ns         | 124748ns       | 139559ns        | 142625ns  | 222066ns   | 178552ns  | 151251ns  |
| Update   ~1K entities with 3 systems | 694543ns  | 569244ns  | 673371ns         | 502709ns       | 557537ns        | 556947ns  | 647644ns   | 714996ns  | 592964ns  |
| Update   ~4K entities with 3 systems | 2878674ns | 2355741ns | 2699398ns        | 2028502ns      | 2286205ns       | 2290036ns | 2093706ns  | 2889629ns | 2397974ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 systems | 11ms      | 9ms    | 10ms             | 8ms            | 9ms             | 9ms       | 8ms        | 11ms      | 9ms     |
| Update  ~65K entities with 3 systems | 44ms      | 42ms   | 43ms             | 32ms           | 36ms            | 36ms      | 32ms       | 48ms      | 38ms    |
| Update  262K entities with 3 systems | 178ms     | 148ms  | 170ms            | 137ms          | 142ms           | 143ms     | 128ms      | 189ms     | 150ms   |
| Update   ~1M entities with 3 systems | 716ms     | 593ms  | 697ms            | 625ms          | 569ms           | 587ms     | 519ms      | 730ms     | 509ms   |
| Update   ~2M entities with 3 systems | 1418ms    | 1191ms | 1377ms           | 1243ms         | 1148ms          | 1186ms    | 1046ms     | 1494ms    | 1018ms  |


### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:----------|
| Update    16 entities with 3 Systems | 9561ns    | 8089ns    | 9140ns           | 7016ns         | 7775ns          | 7756ns    | 88893ns    | 9801ns    | 10002ns   |
| Update    64 entities with 3 Systems | 39776ns   | 33367ns   | 39097ns          | 28283ns        | 32176ns         | 32392ns   | 117110ns   | 40011ns   | 31996ns   |
| Update   256 entities with 3 Systems | 172841ns  | 144813ns  | 169627ns         | 124698ns       | 139788ns        | 141888ns  | 217666ns   | 176447ns  | 127142ns  |
| Update   ~1K entities with 3 Systems | 696880ns  | 570857ns  | 670592ns         | 503420ns       | 551486ns        | 557960ns  | 636303ns   | 721395ns  | 502292ns  |
| Update   ~4K entities with 3 Systems | 2824212ns | 2322159ns | 2707465ns        | 2034778ns      | 2230426ns       | 2311024ns | 2164733ns  | 2876703ns | 2024610ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 Systems | 11ms      | 9ms    | 10ms             | 8ms            | 9ms             | 9ms       | 8ms        | 12ms      | 7ms     |
| Update  ~65K entities with 3 Systems | 44ms      | 38ms   | 43ms             | 32ms           | 37ms            | 36ms      | 32ms       | 56ms      | 31ms    |
| Update  262K entities with 3 Systems | 176ms     | 147ms  | 176ms            | 134ms          | 144ms           | 146ms     | 139ms      | 221ms     | 127ms   |
| Update   ~1M entities with 3 Systems | 703ms     | 594ms  | 703ms            | 626ms          | 582ms           | 582ms     | 531ms      | 900ms     | 499ms   |
| Update   ~2M entities with 3 Systems | 1417ms    | 1194ms | 1383ms           | 1266ms         | 1159ms          | 1156ms    | 1067ms     | 1798ms    | 1016ms  |


### Iterate over entities with one component

![IterateSingleComponent Plot](img/IterateSingleComponent.png)

_(lower is better)_

|                                                | EntityX   | EnTT    | EnTT (runtime)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-----------------------------------------------|:----------|:--------|:-----------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over    16 entities with one component | 402ns     | 77ns    | 315ns            | 77ns            | 18ns      | 24130ns    | 649ns     | 308ns   |
| Iterate over    64 entities with one component | 1538ns    | 230ns   | 1169ns           | 225ns           | 65ns      | 24177ns    | 2419ns    | 316ns   |
| Iterate over   256 entities with one component | 6039ns    | 864ns   | 4578ns           | 827ns           | 254ns     | 24023ns    | 9691ns    | 371ns   |
| Iterate over   ~1K entities with one component | 24727ns   | 3483ns  | 18355ns          | 3256ns          | 1016ns    | 24669ns    | 38666ns   | 562ns   |
| Iterate over   ~4K entities with one component | 98420ns   | 13704ns | 73473ns          | 11497ns         | 4248ns    | 25406ns    | 156340ns  | 1645ns  |

|                                                | EntityX   | EnTT   | EnTT (runtime)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-----------------------------------------------|:----------|:-------|:-----------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over  ~16K entities with one component | 0ms       | 0ms    | 0ms              | 0ms             | 0ms       | 0ms        | 0ms       | 0ms     |
| Iterate over  ~65K entities with one component | 1ms       | 0ms    | 1ms              | 0ms             | 0ms       | 0ms        | 2ms       | 0ms     |
| Iterate over  262K entities with one component | 6ms       | 0ms    | 4ms              | 0ms             | 0ms       | 0ms        | 9ms       | 0ms     |
| Iterate over   ~1M entities with one component | 25ms      | 3ms    | 19ms             | 2ms             | 1ms       | 0ms        | 39ms      | 0ms     |
| Iterate over   ~2M entities with one component | 50ms      | 7ms    | 40ms             | 6ms             | 2ms       | 1ms        | 80ms      | 1ms     |


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EntityX   | EnTT    | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------------|:----------|:--------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over    16 entities with two components | 735ns     | 116ns   | 574ns            | 37ns                       | 68ns                      | 37ns                          | 87ns            | 36ns      | 24410ns    | 685ns     | 321ns   |
| Iterate over    64 entities with two components | 2885ns    | 415ns   | 2155ns           | 145ns                      | 234ns                     | 146ns                         | 298ns           | 132ns     | 24409ns    | 2634ns    | 340ns   |
| Iterate over   256 entities with two components | 11364ns   | 1578ns  | 8543ns           | 552ns                      | 889ns                     | 549ns                         | 1133ns          | 517ns     | 24851ns    | 10339ns   | 392ns   |
| Iterate over   ~1K entities with two components | 45657ns   | 6452ns  | 34505ns          | 2193ns                     | 3618ns                    | 2164ns                        | 4480ns          | 2230ns    | 24833ns    | 41675ns   | 593ns   |
| Iterate over   ~4K entities with two components | 183215ns  | 25362ns | 141048ns         | 8763ns                     | 14689ns                   | 8651ns                        | 18193ns         | 8748ns    | 26031ns    | 168455ns  | 1655ns  |

|                                                 | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over  ~16K entities with two components | 0ms       | 0ms    | 0ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms       | 0ms     |
| Iterate over  ~65K entities with two components | 2ms       | 0ms    | 2ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 2ms       | 0ms     |
| Iterate over  262K entities with two components | 11ms      | 1ms    | 8ms              | 0ms                        | 1ms                       | 0ms                           | 1ms             | 0ms       | 0ms        | 11ms      | 0ms     |
| Iterate over   ~1M entities with two components | 47ms      | 6ms    | 36ms             | 2ms                        | 4ms                       | 2ms                           | 5ms             | 3ms       | 0ms        | 46ms      | 0ms     |
| Iterate over   ~2M entities with two components | 95ms      | 14ms   | 73ms             | 4ms                        | 8ms                       | 4ms                           | 10ms            | 7ms       | 1ms        | 95ms      | 1ms     |


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.png)

_(lower is better)_

|                                                   | EntityX   | EnTT    | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:--------------------------------------------------|:----------|:--------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over    16 entities with three components | 764ns     | 90ns    | 471ns            | 27ns                       | 53ns                      | 27ns                          | 81ns            | 50ns      | 25139ns    | 618ns     | 338ns   |
| Iterate over    64 entities with three components | 3062ns    | 347ns   | 1838ns           | 84ns                       | 171ns                     | 83ns                          | 289ns           | 163ns     | 24298ns    | 2515ns    | 351ns   |
| Iterate over   256 entities with three components | 15960ns   | 1455ns  | 8858ns           | 423ns                      | 906ns                     | 419ns                         | 1316ns          | 798ns     | 24631ns    | 11961ns   | 412ns   |
| Iterate over   ~1K entities with three components | 63840ns   | 6010ns  | 36107ns          | 1643ns                     | 3629ns                    | 1621ns                        | 4862ns          | 3175ns    | 24698ns    | 46672ns   | 614ns   |
| Iterate over   ~4K entities with three components | 255433ns  | 23248ns | 144752ns         | 6570ns                     | 14406ns                   | 6368ns                        | 20990ns         | 13023ns   | 26889ns    | 188002ns  | 1667ns  |

|                                                   | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:--------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:----------|:--------|
| Iterate over  ~16K entities with three components | 1ms       | 0ms    | 0ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms       | 0ms     |
| Iterate over  ~65K entities with three components | 4ms       | 0ms    | 2ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 2ms       | 0ms     |
| Iterate over  262K entities with three components | 16ms      | 1ms    | 9ms              | 0ms                        | 0ms                       | 0ms                           | 1ms             | 0ms       | 0ms        | 11ms      | 0ms     |
| Iterate over   ~1M entities with three components | 65ms      | 6ms    | 38ms             | 1ms                        | 4ms                       | 1ms                           | 6ms             | 4ms       | 0ms        | 45ms      | 0ms     |
| Iterate over   ~2M entities with three components | 131ms     | 13ms   | 76ms             | 3ms                        | 8ms                       | 3ms                           | 12ms            | 8ms       | 1ms        | 90ms      | 1ms     |





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

* **OS:** Windows 10
* **CPU:** 2.30GHz @ 8Cores
* **RAM:** 16GB

