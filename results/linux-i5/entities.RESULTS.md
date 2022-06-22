# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)

_(lower is faster)_

None

None



## Benchmarks

### Create entities

![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|
| Create    16 entities with two Components | 3735ns    | 3475ns   | 18755ns   | 3159ns     | 780240ns  |
| Create    64 entities with two Components | 7888ns    | 4837ns   | 20660ns   | 6300ns     | 788278ns  |
| Create   256 entities with two Components | 27134ns   | 9722ns   | 27714ns   | 17077ns    | 880932ns  |
| Create   ~1K entities with two Components | 103331ns  | 30332ns  | 57441ns   | 63901ns    | 1105032ns |
| Create   ~4K entities with two Components | 373305ns  | 165795ns | 159683ns  | 245132ns   | 2207994ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Create  ~16K entities with two Components | 1ms       | 1ms    | 0ms       | 0ms        | 6ms     |
| Create  ~65K entities with two Components | 7ms       | 3ms    | 5ms       | 4ms        | 23ms    |
| Create  262K entities with two Components | 29ms      | 17ms   | 22ms      | 20ms       | 92ms    |
| Create   ~1M entities with two Components | 120ms     | 59ms   | 87ms      | 81ms       | 392ms   |
| Create   ~2M entities with two Components | 237ms     | 112ms  | 180ms     | 171ms      | 731ms   |


### Create empty entities

![CreateEmptyEntities Plot](img/CreateEmptyEntities.png)

_(lower is better)_

|                               | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Create    16 (empty) entities | 1736ns    | 806ns   | 848ns     | 2061ns     | 594627ns |
| Create    64 (empty) entities | 3443ns    | 1016ns  | 1343ns    | 3904ns     | 588790ns |
| Create   256 (empty) entities | 10549ns   | 1680ns  | 2886ns    | 12364ns    | 616074ns |
| Create   ~1K (empty) entities | 37229ns   | 4493ns  | 8513ns    | 41056ns    | 657697ns |
| Create   ~4K (empty) entities | 141323ns  | 16293ns | 30824ns   | 152756ns   | 839400ns |

|                               | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Create  ~16K (empty) entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Create  ~65K (empty) entities | 2ms       | 0ms    | 0ms       | 2ms        | 4ms     |
| Create  262K (empty) entities | 8ms       | 1ms    | 3ms       | 10ms       | 17ms    |
| Create   ~1M (empty) entities | 35ms      | 4ms    | 14ms      | 46ms       | 84ms    |
| Create   ~2M (empty) entities | 88ms      | 22ms   | 44ms      | 116ms      | 152ms   |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack one component in    16 entities | 35ns      | 71ns    | 40ns      | 231ns      | 791ns    |
| Unpack one component in    64 entities | 145ns     | 294ns   | 162ns     | 927ns      | 3501ns   |
| Unpack one component in   256 entities | 551ns     | 1155ns  | 659ns     | 3853ns     | 13470ns  |
| Unpack one component in   ~1K entities | 2274ns    | 5154ns  | 2505ns    | 14768ns    | 50901ns  |
| Unpack one component in   ~4K entities | 8733ns    | 17482ns | 10761ns   | 56918ns    | 206168ns |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 3ms     |
| Unpack one component in  262K entities | 0ms       | 1ms    | 0ms       | 4ms        | 13ms    |
| Unpack one component in   ~1M entities | 2ms       | 5ms    | 3ms       | 16ms       | 53ms    |
| Unpack one component in   ~2M entities | 5ms       | 10ms   | 7ms       | 31ms       | 132ms   |


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Get one (const) component in    16 entities | 36ns      | 60ns    | 40ns      | 131ns      | 600ns    |
| Get one (const) component in    64 entities | 145ns     | 262ns   | 151ns     | 485ns      | 2395ns   |
| Get one (const) component in   256 entities | 551ns     | 961ns   | 608ns     | 2059ns     | 9102ns   |
| Get one (const) component in   ~1K entities | 2319ns    | 3817ns  | 2644ns    | 8185ns     | 37473ns  |
| Get one (const) component in   ~4K entities | 9372ns    | 15534ns | 10593ns   | 31060ns    | 151054ns |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     |
| Get one (const) component in  262K entities | 0ms       | 1ms    | 0ms       | 2ms        | 9ms     |
| Get one (const) component in   ~1M entities | 2ms       | 5ms    | 3ms       | 9ms        | 40ms    |
| Get one (const) component in   ~2M entities | 5ms       | 9ms    | 7ms       | 17ms       | 80ms    |


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack two components in    16 entities | 73ns      | 130ns   | 79ns      | 353ns      | 1375ns   |
| Unpack two components in    64 entities | 299ns     | 494ns   | 304ns     | 1349ns     | 5471ns   |
| Unpack two components in   256 entities | 1172ns    | 1959ns  | 1232ns    | 5228ns     | 21600ns  |
| Unpack two components in   ~1K entities | 4640ns    | 8441ns  | 5262ns    | 20696ns    | 93303ns  |
| Unpack two components in   ~4K entities | 18691ns   | 33956ns | 20311ns   | 89579ns    | 347697ns |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 5ms     |
| Unpack two components in  262K entities | 1ms       | 2ms    | 1ms       | 5ms        | 24ms    |
| Unpack two components in   ~1M entities | 4ms       | 9ms    | 6ms       | 24ms       | 93ms    |
| Unpack two components in   ~2M entities | 9ms       | 18ms   | 13ms      | 45ms       | 183ms   |


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack three components in     8 entities | 62ns      | 101ns   | 60ns      | 213ns      | 1108ns   |
| Unpack three components in    32 entities | 259ns     | 445ns   | 238ns     | 820ns      | 4329ns   |
| Unpack three components in   128 entities | 1079ns    | 1760ns  | 970ns     | 3318ns     | 19157ns  |
| Unpack three components in   512 entities | 4300ns    | 6734ns  | 4108ns    | 13077ns    | 73840ns  |
| Unpack three components in   ~2K entities | 17094ns   | 26580ns | 16376ns   | 52467ns    | 295134ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 5ms     |
| Unpack three components in  131K entities | 1ms       | 1ms    | 1ms       | 3ms        | 19ms    |
| Unpack three components in  524K entities | 4ms       | 8ms    | 7ms       | 13ms       | 78ms    |
| Unpack three components in   ~1M entities | 9ms       | 18ms   | 14ms      | 29ms       | 156ms   |


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:----------|
| Remove and Add a Component in    16 entities | 409ns     | 475ns    | 186ns     | 1227ns     | 5248ns    |
| Remove and Add a Component in    64 entities | 1649ns    | 1864ns   | 748ns     | 4854ns     | 20759ns   |
| Remove and Add a Component in   256 entities | 6736ns    | 7465ns   | 3059ns    | 19530ns    | 91580ns   |
| Remove and Add a Component in   ~1K entities | 26865ns   | 29639ns  | 12191ns   | 79239ns    | 331497ns  |
| Remove and Add a Component in   ~4K entities | 102030ns  | 123328ns | 51761ns   | 304850ns   | 1333066ns |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 1ms        | 5ms     |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 5ms        | 21ms    |
| Remove and Add a Component in  262K entities | 6ms       | 7ms    | 3ms       | 20ms       | 86ms    |
| Remove and Add a Component in   ~1M entities | 26ms      | 31ms   | 14ms      | 86ms       | 370ms   |
| Remove and Add a Component in   ~2M entities | 56ms      | 63ms   | 27ms      | 192ms      | 686ms   |


### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Destroy    16 entities with two components | 1846ns    | 1516ns   | 2896ns    | 984ns      | 651772ns |
| Destroy    64 entities with two components | 3826ns    | 2987ns   | 8151ns    | 1181ns     | 644934ns |
| Destroy   256 entities with two components | 12362ns   | 9327ns   | 27284ns   | 1960ns     | 682378ns |
| Destroy   ~1K entities with two components | 50924ns   | 35755ns  | 104055ns  | 4939ns     | 700962ns |
| Destroy   ~4K entities with two components | 204983ns  | 134875ns | 428854ns  | 16774ns    | 930247ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 0ms        | 1ms     |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 6ms       | 0ms        | 4ms     |
| Destroy  262K entities with two components | 15ms      | 9ms    | 27ms      | 1ms        | 16ms    |
| Destroy   ~1M entities with two components | 70ms      | 41ms   | 122ms     | 8ms        | 71ms    |
| Destroy   ~2M entities with two components | 157ms     | 80ms   | 241ms     | 15ms       | 135ms   |


### Create entities at once

![CreateEntitiesInBulk Plot](img/CreateEntitiesInBulk.png)

_(lower is better)_

|                                                   | EnTT    |
|:--------------------------------------------------|:--------|
| Create    16 entities with two components at once | 3122ns  |
| Create    64 entities with two components at once | 3588ns  |
| Create   256 entities with two components at once | 5419ns  |
| Create   ~1K entities with two components at once | 13682ns |
| Create   ~4K entities with two components at once | 44691ns |

|                                                   | EnTT   |
|:--------------------------------------------------|:-------|
| Create  ~16K entities with two components at once | 0ms    |
| Create  ~65K entities with two components at once | 0ms    |
| Create  262K entities with two components at once | 4ms    |
| Create   ~1M entities with two components at once | 32ms   |
| Create   ~2M entities with two components at once | 81ms   |


### Create empty entities at once

![CreateEmptyEntitiesInBulk Plot](img/CreateEmptyEntitiesInBulk.png)

_(lower is better)_

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create    16 (empty) entities at once | 659ns  |
| Create    64 (empty) entities at once | 702ns  |
| Create   256 (empty) entities at once | 846ns  |
| Create   ~1K (empty) entities at once | 1282ns |
| Create   ~4K (empty) entities at once | 5962ns |

|                                       | EnTT   |
|:--------------------------------------|:-------|
| Create  ~16K (empty) entities at once | 0ms    |
| Create  ~65K (empty) entities at once | 0ms    |
| Create  262K (empty) entities at once | 0ms    |
| Create   ~1M (empty) entities at once | 3ms    |
| Create   ~2M (empty) entities at once | 13ms   |


### Destroy entities at once

![DestroyEntitiesInBulk Plot](img/DestroyEntitiesInBulk.png)

_(lower is better)_

|                                                    | EnTT     |
|:---------------------------------------------------|:---------|
| Destroy    16 entities with two components at once | 1454ns   |
| Destroy    64 entities with two components at once | 3000ns   |
| Destroy   256 entities with two components at once | 9091ns   |
| Destroy   ~1K entities with two components at once | 34277ns  |
| Destroy   ~4K entities with two components at once | 134301ns |

|                                                    | EnTT   |
|:---------------------------------------------------|:-------|
| Destroy  ~16K entities with two components at once | 0ms    |
| Destroy  ~65K entities with two components at once | 2ms    |
| Destroy  262K entities with two components at once | 9ms    |
| Destroy   ~1M entities with two components at once | 39ms   |
| Destroy   ~2M entities with two components at once | 79ms   |





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

