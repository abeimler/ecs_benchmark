# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:----------|
| Update  ~16K entities with 3 systems | 5555ns    | 4065ns    | 5195ns           | 4044ns         | 4230ns          | 4048ns    | 40511ns    | 5235ns    | 6507ns    |
| Update  ~65K entities with 3 systems | 21302ns   | 16105ns   | 20700ns          | 15931ns        | 15736ns         | 17335ns   | 54309ns    | 21089ns   | 19348ns   |
| Update  262K entities with 3 systems | 87993ns   | 64472ns   | 83006ns          | 64075ns        | 63398ns         | 69292ns   | 102083ns   | 85306ns   | 65778ns   |
| Update   ~1M entities with 3 systems | 353422ns  | 260896ns  | 316467ns         | 259257ns       | 255070ns        | 261130ns  | 301350ns   | 314408ns  | 275614ns  |
| Update   ~2M entities with 3 systems | 1278713ns | 1081018ns | 1213939ns        | 997418ns       | 986995ns        | 1013263ns | 1113415ns  | 1207959ns | 1025800ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 systems | 5ms       | 4ms    | 4ms              | 3ms            | 3ms             | 4ms       | 4ms        | 4ms       | 4ms     |
| Update  ~65K entities with 3 systems | 20ms      | 16ms   | 21ms             | 17ms           | 17ms            | 16ms      | 16ms       | 19ms      | 15ms    |
| Update  262K entities with 3 systems | 90ms      | 67ms   | 81ms             | 74ms           | 65ms            | 72ms      | 66ms       | 85ms      | 64ms    |
| Update   ~1M entities with 3 systems | 335ms     | 267ms  | 324ms            | 300ms          | 260ms           | 268ms     | 276ms      | 321ms     | 258ms   |
| Update   ~2M entities with 3 systems | 670ms     | 539ms  | 650ms            | 675ms          | 560ms           | 541ms     | 524ms      | 690ms     | 515ms   |



## Benchmarks

### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:----------|
| Update    16 entities with 3 systems | 5555ns    | 4065ns    | 5195ns           | 4044ns         | 4230ns          | 4048ns    | 40511ns    | 5235ns    | 6507ns    |
| Update    64 entities with 3 systems | 21302ns   | 16105ns   | 20700ns          | 15931ns        | 15736ns         | 17335ns   | 54309ns    | 21089ns   | 19348ns   |
| Update   256 entities with 3 systems | 87993ns   | 64472ns   | 83006ns          | 64075ns        | 63398ns         | 69292ns   | 102083ns   | 85306ns   | 65778ns   |
| Update   ~1K entities with 3 systems | 353422ns  | 260896ns  | 316467ns         | 259257ns       | 255070ns        | 261130ns  | 301350ns   | 314408ns  | 275614ns  |
| Update   ~4K entities with 3 systems | 1278713ns | 1081018ns | 1213939ns        | 997418ns       | 986995ns        | 1013263ns | 1113415ns  | 1207959ns | 1025800ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 systems | 5ms       | 4ms    | 4ms              | 3ms            | 3ms             | 4ms       | 4ms        | 4ms       | 4ms     |
| Update  ~65K entities with 3 systems | 20ms      | 16ms   | 21ms             | 17ms           | 17ms            | 16ms      | 16ms       | 19ms      | 15ms    |
| Update  262K entities with 3 systems | 90ms      | 67ms   | 81ms             | 74ms           | 65ms            | 72ms      | 66ms       | 85ms      | 64ms    |
| Update   ~1M entities with 3 systems | 335ms     | 267ms  | 324ms            | 300ms          | 260ms           | 268ms     | 276ms      | 321ms     | 258ms   |
| Update   ~2M entities with 3 systems | 670ms     | 539ms  | 650ms            | 675ms          | 560ms           | 541ms     | 524ms      | 690ms     | 515ms   |


### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EntityX   | EnTT      | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:----------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:----------|
| Update    16 entities with 3 Systems | 4434ns    | 3791ns    | 4167ns           | 3811ns         | 3479ns          | 3524ns    | 39977ns    | 4160ns    | 6124ns    |
| Update    64 entities with 3 Systems | 18344ns   | 14761ns   | 18770ns          | 14738ns        | 14509ns         | 14791ns   | 51354ns    | 18651ns   | 17147ns   |
| Update   256 entities with 3 Systems | 82450ns   | 64531ns   | 78130ns          | 64149ns        | 63200ns         | 69407ns   | 108360ns   | 83445ns   | 65481ns   |
| Update   ~1K entities with 3 Systems | 330429ns  | 261323ns  | 314371ns         | 257994ns       | 254488ns        | 279095ns  | 316350ns   | 334947ns  | 274597ns  |
| Update   ~4K entities with 3 Systems | 1353928ns | 1008883ns | 1294181ns        | 1000632ns      | 984812ns        | 1080972ns | 1039849ns  | 1286302ns | 1001524ns |

|                                      | EntityX   | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:----------|:--------|
| Update  ~16K entities with 3 Systems | 5ms       | 4ms    | 4ms              | 4ms            | 3ms             | 4ms       | 3ms        | 5ms       | 4ms     |
| Update  ~65K entities with 3 Systems | 20ms      | 17ms   | 20ms             | 17ms           | 16ms            | 16ms      | 16ms       | 20ms      | 16ms    |
| Update  262K entities with 3 Systems | 90ms      | 72ms   | 81ms             | 68ms           | 65ms            | 67ms      | 65ms       | 80ms      | 68ms    |
| Update   ~1M entities with 3 Systems | 334ms     | 283ms  | 325ms            | 330ms          | 279ms           | 283ms     | 258ms      | 321ms     | 267ms   |
| Update   ~2M entities with 3 Systems | 671ms     | 540ms  | 648ms            | 740ms          | 578ms           | 585ms     | 520ms      | 644ms     | 515ms   |


### Iterate over entities with one component

![IterateSingleComponent Plot](img/IterateSingleComponent.png)

_(lower is better)_

|                                                | EntityX   | EnTT   | EnTT (runtime)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-----------------------------------------------|:----------|:-------|:-----------------|:----------------|:----------|:-----------|:--------|
| Iterate over    16 entities with one component | 214ns     | 15ns   | 163ns            | 15ns            | 16ns      | 12373ns    | 334ns   |
| Iterate over    64 entities with one component | 879ns     | 46ns   | 627ns            | 45ns            | 63ns      | 12361ns    | 373ns   |
| Iterate over   256 entities with one component | 3474ns    | 177ns  | 2492ns           | 177ns           | 260ns     | 12582ns    | 432ns   |
| Iterate over   ~1K entities with one component | 13130ns   | 678ns  | 9862ns           | 677ns           | 1071ns    | 11832ns    | 721ns   |
| Iterate over   ~4K entities with one component | 52961ns   | 2692ns | 38951ns          | 2692ns          | 4365ns    | 10008ns    | 2021ns  |

|                                                | EntityX   | EnTT   | EnTT (runtime)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-----------------------------------------------|:----------|:-------|:-----------------|:----------------|:----------|:-----------|:--------|
| Iterate over  ~16K entities with one component | 0ms       | 0ms    | 0ms              | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  ~65K entities with one component | 0ms       | 0ms    | 0ms              | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  262K entities with one component | 3ms       | 0ms    | 2ms              | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over   ~1M entities with one component | 13ms      | 1ms    | 10ms             | 1ms             | 1ms       | 1ms        | 1ms     |
| Iterate over   ~2M entities with one component | 27ms      | 2ms    | 20ms             | 2ms             | 3ms       | 2ms        | 2ms     |


### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:--------|
| Iterate over    16 entities with two components | 399ns     | 33ns   | 228ns            | 11ns                       | 24ns                      | 10ns                          | 35ns            | 28ns      | 12378ns    | 360ns   |
| Iterate over    64 entities with two components | 1516ns    | 127ns  | 869ns            | 45ns                       | 92ns                      | 42ns                          | 136ns           | 122ns     | 12496ns    | 376ns   |
| Iterate over   256 entities with two components | 6123ns    | 547ns  | 3434ns           | 186ns                      | 346ns                     | 175ns                         | 510ns           | 454ns     | 12858ns    | 478ns   |
| Iterate over   ~1K entities with two components | 24087ns   | 2154ns | 13826ns          | 723ns                      | 1386ns                    | 675ns                         | 2018ns          | 1812ns    | 12034ns    | 696ns   |
| Iterate over   ~4K entities with two components | 95780ns   | 8576ns | 54736ns          | 2752ns                     | 7268ns                    | 2681ns                        | 8603ns          | 7213ns    | 10095ns    | 1917ns  |

|                                                 | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:--------|
| Iterate over  ~16K entities with two components | 0ms       | 0ms    | 0ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  ~65K entities with two components | 1ms       | 0ms    | 0ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  262K entities with two components | 6ms       | 0ms    | 3ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over   ~1M entities with two components | 24ms      | 2ms    | 14ms             | 1ms                        | 2ms                       | 1ms                           | 2ms             | 3ms       | 1ms        | 1ms     |
| Iterate over   ~2M entities with two components | 49ms      | 5ms    | 29ms             | 2ms                        | 5ms                       | 2ms                           | 5ms             | 7ms       | 2ms        | 2ms     |


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.png)

_(lower is better)_

|                                                   | EntityX   | EnTT    | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------------|:----------|:--------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:--------|
| Iterate over    16 entities with three components | 390ns     | 53ns    | 257ns            | 11ns                       | 15ns                      | 7ns                           | 50ns            | 45ns      | 12585ns    | 374ns   |
| Iterate over    64 entities with three components | 1494ns    | 213ns   | 1102ns           | 44ns                       | 61ns                      | 30ns                          | 201ns           | 188ns     | 12777ns    | 413ns   |
| Iterate over   256 entities with three components | 8357ns    | 1008ns  | 5444ns           | 273ns                      | 342ns                     | 173ns                         | 1006ns          | 841ns     | 12643ns    | 465ns   |
| Iterate over   ~1K entities with three components | 35062ns   | 4276ns  | 20534ns          | 1059ns                     | 2643ns                    | 671ns                         | 4265ns          | 3594ns    | 12188ns    | 766ns   |
| Iterate over   ~4K entities with three components | 137177ns  | 16104ns | 82283ns          | 4219ns                     | 6967ns                    | 2841ns                        | 16137ns         | 14499ns   | 10495ns    | 1952ns  |

|                                                   | EntityX   | EnTT   | EnTT (runtime)   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------------|:----------|:-------|:-----------------|:---------------------------|:--------------------------|:------------------------------|:----------------|:----------|:-----------|:--------|
| Iterate over  ~16K entities with three components | 0ms       | 0ms    | 0ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  ~65K entities with three components | 2ms       | 0ms    | 1ms              | 0ms                        | 0ms                       | 0ms                           | 0ms             | 0ms       | 0ms        | 0ms     |
| Iterate over  262K entities with three components | 8ms       | 1ms    | 5ms              | 0ms                        | 0ms                       | 0ms                           | 1ms             | 1ms       | 0ms        | 0ms     |
| Iterate over   ~1M entities with three components | 34ms      | 4ms    | 23ms             | 1ms                        | 2ms                       | 1ms                           | 4ms             | 4ms       | 1ms        | 1ms     |
| Iterate over   ~2M entities with three components | 68ms      | 9ms    | 43ms             | 2ms                        | 5ms                       | 2ms                           | 9ms             | 8ms       | 2ms        | 2ms     |





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

