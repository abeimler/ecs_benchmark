# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/ci/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)
![Standard](https://img.shields.io/badge/c%2B%2B-20-blue)

Simple Benchmarks of common ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [flecs](https://github.com/SanderMertens/flecs)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [OpenEcs](https://github.com/Gronis/OpenEcs)

## TL;DR Results

### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 Systems | 3060ns   | 3511ns           | 2988ns         | 3029ns          | 3032ns    | 111552ns   | 3956ns   |
| Update    64 entities with 3 Systems | 13060ns  | 15271ns          | 12677ns        | 13032ns         | 13179ns   | 129333ns   | 14082ns  |
| Update   256 entities with 3 Systems | 55713ns  | 65685ns          | 54073ns        | 55158ns         | 56406ns   | 154110ns   | 55632ns  |
| Update   ~1K entities with 3 Systems | 219349ns | 253519ns         | 215628ns       | 217068ns        | 227745ns  | 325840ns   | 225262ns |
| Update   ~4K entities with 3 Systems | 857519ns | 980429ns         | 837731ns       | 849060ns        | 881086ns  | 971967ns   | 854226ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 Systems | 13ms   | 15ms             | 13ms           | 14ms            | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 3 Systems | 58ms   | 64ms             | 58ms           | 54ms            | 56ms      | 53ms       | 54ms    |
| Update   ~1M entities with 3 Systems | 220ms  | 256ms            | 270ms          | 222ms           | 223ms     | 216ms      | 219ms   |
| Update   ~2M entities with 3 Systems | 439ms  | 518ms            | 648ms          | 440ms           | 445ms     | 439ms      | 441ms   |



This is a very little Benchmark with three simple components and three small systems. In wild Entity-Component-Systems can have hundreds of components and a lot of systems and even more complex systems.
So always benchmarks YOUR special cases and systems, when needed and compare.

Some frameworks are faster in adding/removing components, others in creating or destroying entities, it always depends on what you need the most.
Always choose an ECS-Framework by features, for example EnTT has some great features like a 
[resource-management](https://github.com/skypjack/entt/wiki/Crash-Course:-resource-management) or [events](https://github.com/skypjack/entt/wiki/Crash-Course:-events,-signals-and-everything-in-between), 
flecs has some nice [add-ons](https://github.com/SanderMertens/flecs#addons) and EntityX has a build-in [world/system-manager](https://github.com/alecthomas/entityx#manager-tying-it-all-together=).

Pick and evaluate a framework you like and have a look at the examples and API design.


## Details

### Features

All benchmarks are located in [`benchmark/benchmarks/`](benchmark/benchmarks/) and are written with [google/benchmark](https://github.com/google/benchmark).
Each benchmark must implement the template [ECSBenchmark.h](benchmark/benchmarks/ECSBenchmark.h).

Each framework has a sub-project in [`src/`](src) and must implement certain features (see [`src/base`](src/base)).

#### Components

1. `PositionComponent` with `x` and `y` coord.
2. `VelocityComponent` with `x` and `y` for movement.
3. `DataComponent` with some nonsense data.

#### Systems

1. `MovementSystem`: updates `PositionComponent` with (const) `VelocityComponent`
2. `DataSystem`: updates `DataComponent` with nonsense
3. `MoreComplexSystem`: updates Components with random data and nonsense



## More Benchmarks

Benchmarks of more common features, like "Creating entities", "Add and remove components", etc.

### Features tested

* Create Entities
* Destroy Entities
* Get Component(s)
* Remove and add component
* Systems (for-each entities)


### Environment

* **OS:** Linux
* **CPU:** 3.13GHz @ 12Cores
* **RAM:** 15.55GB
* **Compiler:** gcc (GCC) 12.2.0


### Create entities

![CreateEntities Plot](img/CreateEntities.png)

_(lower is better)_

|                                           | EntityX   | EnTT     | Ginseng   | mustache   | Flecs     |
|:------------------------------------------|:----------|:---------|:----------|:-----------|:----------|
| Create    16 entities with two Components | 2716ns    | 2750ns   | 10472ns   | 2993ns     | 692709ns  |
| Create    64 entities with two Components | 6567ns    | 4352ns   | 11832ns   | 5894ns     | 694854ns  |
| Create   256 entities with two Components | 21436ns   | 10215ns  | 16207ns   | 16732ns    | 743310ns  |
| Create   ~1K entities with two Components | 81265ns   | 32936ns  | 32101ns   | 59557ns    | 851549ns  |
| Create   ~4K entities with two Components | 314925ns  | 141350ns | 96077ns   | 229287ns   | 1454413ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Create  ~16K entities with two Components | 1ms       | 0ms    | 0ms       | 0ms        | 4ms     |
| Create  ~65K entities with two Components | 5ms       | 2ms    | 3ms       | 4ms        | 14ms    |
| Create  262K entities with two Components | 23ms      | 12ms   | 14ms      | 18ms       | 54ms    |
| Create   ~1M entities with two Components | 92ms      | 48ms   | 49ms      | 72ms       | 202ms   |
| Create   ~2M entities with two Components | 183ms     | 93ms   | 94ms      | 145ms      | 395ms   |



### Destroy entities

![DestroyEntities Plot](img/DestroyEntities.png)

_(lower is better)_

|                                            | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:-------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Destroy    16 entities with two components | 1416ns    | 1075ns   | 1978ns    | 682ns      | 396515ns |
| Destroy    64 entities with two components | 3421ns    | 2540ns   | 5515ns    | 819ns      | 398124ns |
| Destroy   256 entities with two components | 11662ns   | 8462ns   | 19184ns   | 1294ns     | 404232ns |
| Destroy   ~1K entities with two components | 46007ns   | 32197ns  | 73215ns   | 3061ns     | 428263ns |
| Destroy   ~4K entities with two components | 187868ns  | 127435ns | 288918ns  | 9721ns     | 518695ns |

|                                            | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Destroy  ~16K entities with two components | 0ms       | 0ms    | 1ms       | 0ms        | 0ms     |
| Destroy  ~65K entities with two components | 3ms       | 2ms    | 4ms       | 0ms        | 2ms     |
| Destroy  262K entities with two components | 13ms      | 8ms    | 19ms      | 0ms        | 8ms     |
| Destroy   ~1M entities with two components | 58ms      | 35ms   | 78ms      | 4ms        | 34ms    |
| Destroy   ~2M entities with two components | 119ms     | 74ms   | 157ms     | 8ms        | 70ms    |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)

_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Unpack one component in    16 entities | 22ns      | 45ns    | 27ns      | 162ns      | 354ns   |
| Unpack one component in    64 entities | 96ns      | 184ns   | 112ns     | 730ns      | 1393ns  |
| Unpack one component in   256 entities | 366ns     | 725ns   | 441ns     | 2752ns     | 5561ns  |
| Unpack one component in   ~1K entities | 1456ns    | 2887ns  | 1763ns    | 10906ns    | 22790ns |
| Unpack one component in   ~4K entities | 5786ns    | 11572ns | 7039ns    | 45466ns    | 91112ns |

|                                        | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack one component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack one component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack one component in  262K entities | 0ms       | 0ms    | 0ms       | 3ms        | 5ms     |
| Unpack one component in   ~1M entities | 1ms       | 3ms    | 1ms       | 11ms       | 22ms    |
| Unpack one component in   ~2M entities | 3ms       | 6ms    | 3ms       | 25ms       | 45ms    |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)

_(lower is better)_

|                                             | EntityX   | EnTT    | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Get one (const) component in    16 entities | 22ns      | 47ns    | 27ns      | 93ns       | 252ns   |
| Get one (const) component in    64 entities | 96ns      | 190ns   | 112ns     | 360ns      | 988ns   |
| Get one (const) component in   256 entities | 366ns     | 750ns   | 444ns     | 1424ns     | 3929ns  |
| Get one (const) component in   ~1K entities | 1454ns    | 2985ns  | 1748ns    | 5670ns     | 15717ns |
| Get one (const) component in   ~4K entities | 5789ns    | 11989ns | 6968ns    | 22700ns    | 62789ns |

|                                             | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:--------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Get one (const) component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Get one (const) component in  ~65K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Get one (const) component in  262K entities | 0ms       | 0ms    | 0ms       | 1ms        | 4ms     |
| Get one (const) component in   ~1M entities | 1ms       | 3ms    | 1ms       | 5ms        | 16ms    |
| Get one (const) component in   ~2M entities | 3ms       | 6ms    | 3ms       | 11ms       | 32ms    |


**Note:**
* Get one const component
  1. `const PositionComponent`


### Get two components from entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)

_(lower is better)_

|                                         | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:----------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack two components in    16 entities | 41ns      | 93ns    | 54ns      | 257ns      | 618ns    |
| Unpack two components in    64 entities | 172ns     | 365ns   | 222ns     | 1022ns     | 2471ns   |
| Unpack two components in   256 entities | 672ns     | 1457ns  | 877ns     | 4090ns     | 9818ns   |
| Unpack two components in   ~1K entities | 2674ns    | 5809ns  | 3500ns    | 16350ns    | 39301ns  |
| Unpack two components in   ~4K entities | 10707ns   | 23174ns | 14009ns   | 65442ns    | 157353ns |

|                                         | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:----------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack two components in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack two components in  ~65K entities | 0ms       | 0ms    | 0ms       | 1ms        | 2ms     |
| Unpack two components in  262K entities | 0ms       | 1ms    | 0ms       | 4ms        | 10ms    |
| Unpack two components in   ~1M entities | 2ms       | 6ms    | 3ms       | 17ms       | 40ms    |
| Unpack two components in   ~2M entities | 5ms       | 12ms   | 7ms       | 34ms       | 80ms    |


**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`


### Get three components from entity

![UnpackThreeComponents Plot](img/UnpackThreeComponents.png)

_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | Flecs    |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:---------|
| Unpack three components in     8 entities | 33ns      | 73ns    | 47ns      | 129ns      | 505ns    |
| Unpack three components in    32 entities | 143ns     | 296ns   | 191ns     | 522ns      | 1971ns   |
| Unpack three components in   128 entities | 538ns     | 1177ns  | 751ns     | 2018ns     | 7909ns   |
| Unpack three components in   512 entities | 2133ns    | 4700ns  | 2986ns    | 8071ns     | 31638ns  |
| Unpack three components in   ~2K entities | 8523ns    | 18743ns | 12002ns   | 32199ns    | 125618ns |

|                                           | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Unpack three components in   ~8K entities | 0ms       | 0ms    | 0ms       | 0ms        | 0ms     |
| Unpack three components in  ~32K entities | 0ms       | 0ms    | 0ms       | 0ms        | 1ms     |
| Unpack three components in  131K entities | 0ms       | 1ms    | 0ms       | 2ms        | 7ms     |
| Unpack three components in  524K entities | 2ms       | 5ms    | 3ms       | 8ms        | 31ms    |
| Unpack three components in   ~1M entities | 4ms       | 10ms   | 6ms       | 17ms       | 62ms    |



**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component

![RemoveAddComponent Plot](img/RemoveAddComponent.png)

_(lower is better)_

|                                              | EntityX   | EnTT     | Ginseng   | mustache   | Flecs    |
|:---------------------------------------------|:----------|:---------|:----------|:-----------|:---------|
| Remove and Add a Component in    16 entities | 300ns     | 426ns    | 208ns     | 880ns      | 2700ns   |
| Remove and Add a Component in    64 entities | 1176ns    | 1684ns   | 737ns     | 3463ns     | 10838ns  |
| Remove and Add a Component in   256 entities | 4691ns    | 6692ns   | 2947ns    | 13810ns    | 42652ns  |
| Remove and Add a Component in   ~1K entities | 18746ns   | 26836ns  | 12003ns   | 56276ns    | 170747ns |
| Remove and Add a Component in   ~4K entities | 74966ns   | 107751ns | 52925ns   | 221859ns   | 681861ns |

|                                              | EntityX   | EnTT   | Ginseng   | mustache   | Flecs   |
|:---------------------------------------------|:----------|:-------|:----------|:-----------|:--------|
| Remove and Add a Component in  ~16K entities | 0ms       | 0ms    | 0ms       | 0ms        | 2ms     |
| Remove and Add a Component in  ~65K entities | 1ms       | 1ms    | 0ms       | 3ms        | 10ms    |
| Remove and Add a Component in  262K entities | 4ms       | 6ms    | 3ms       | 14ms       | 43ms    |
| Remove and Add a Component in   ~1M entities | 19ms      | 27ms   | 12ms      | 64ms       | 175ms   |
| Remove and Add a Component in   ~2M entities | 38ms      | 55ms   | 27ms      | 136ms      | 347ms   |


**Note:**
* Remove and add `PositionComponent`



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


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`


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


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update systems (for-each entities in 3 systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 systems | 3491ns   | 4048ns           | 3462ns         | 3416ns          | 3476ns    | 104112ns   | 4271ns   |
| Update    64 entities with 3 systems | 14197ns  | 16855ns          | 14286ns        | 14028ns         | 14345ns   | 124710ns   | 15006ns  |
| Update   256 entities with 3 systems | 55721ns  | 65505ns          | 54760ns        | 54997ns         | 56989ns   | 168987ns   | 55906ns  |
| Update   ~1K entities with 3 systems | 217934ns | 254836ns         | 214747ns       | 221677ns        | 228271ns  | 323446ns   | 216283ns |
| Update   ~4K entities with 3 systems | 859448ns | 987339ns         | 839617ns       | 856380ns        | 868681ns  | 950704ns   | 855218ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 systems | 13ms   | 15ms             | 13ms           | 13ms            | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 3 systems | 55ms   | 64ms             | 57ms           | 55ms            | 56ms      | 53ms       | 55ms    |
| Update   ~1M entities with 3 systems | 223ms  | 258ms            | 263ms          | 220ms           | 223ms     | 215ms      | 220ms   |
| Update   ~2M entities with 3 systems | 440ms  | 535ms            | 610ms          | 442ms           | 446ms     | 435ms      | 438ms   |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)




### Update systems (for-each entities (with mixed components) in 3 systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)

_(lower is better)_

|                                      | EnTT     | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs    |
|:-------------------------------------|:---------|:-----------------|:---------------|:----------------|:----------|:-----------|:---------|
| Update    16 entities with 3 Systems | 3060ns   | 3511ns           | 2988ns         | 3029ns          | 3032ns    | 111552ns   | 3956ns   |
| Update    64 entities with 3 Systems | 13060ns  | 15271ns          | 12677ns        | 13032ns         | 13179ns   | 129333ns   | 14082ns  |
| Update   256 entities with 3 Systems | 55713ns  | 65685ns          | 54073ns        | 55158ns         | 56406ns   | 154110ns   | 55632ns  |
| Update   ~1K entities with 3 Systems | 219349ns | 253519ns         | 215628ns       | 217068ns        | 227745ns  | 325840ns   | 225262ns |
| Update   ~4K entities with 3 Systems | 857519ns | 980429ns         | 837731ns       | 849060ns        | 881086ns  | 971967ns   | 854226ns |

|                                      | EnTT   | EnTT (runtime)   | EnTT (group)   | EnTT (stable)   | Ginseng   | mustache   | Flecs   |
|:-------------------------------------|:-------|:-----------------|:---------------|:----------------|:----------|:-----------|:--------|
| Update  ~16K entities with 3 Systems | 3ms    | 3ms              | 3ms            | 3ms             | 3ms       | 3ms        | 3ms     |
| Update  ~65K entities with 3 Systems | 13ms   | 15ms             | 13ms           | 14ms            | 13ms      | 13ms       | 13ms    |
| Update  262K entities with 3 Systems | 58ms   | 64ms             | 58ms           | 54ms            | 56ms      | 53ms       | 54ms    |
| Update   ~1M entities with 3 Systems | 220ms  | 256ms            | 270ms          | 222ms           | 223ms     | 216ms      | 219ms   |
| Update   ~2M entities with 3 Systems | 439ms  | 518ms            | 648ms          | 440ms           | 445ms     | 439ms      | 441ms   |



**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* Not every entity has all three components, some got removed
* \*   EnTT iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use `registry.view<DataComponent>`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \**** EnTT iterate components via view and uses a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)



### Iterate over entities with two components

![IterateTwoComponents Plot](img/IterateTwoComponents.png)

_(lower is better)_

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with two components | 9ns                        | 17ns                      | 9ns                           |
| Iterate over    64 entities with two components | 45ns                       | 83ns                      | 45ns                          |
| Iterate over   256 entities with two components | 144ns                      | 331ns                     | 145ns                         |
| Iterate over   ~1K entities with two components | 542ns                      | 1319ns                    | 541ns                         |
| Iterate over   ~4K entities with two components | 2126ns                     | 8393ns                    | 2125ns                        |

|                                                 | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with two components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with two components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with two components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with two components | 4ms                        | 14ms                      | 4ms                           |


**Notes:**
* pre create views/query when possible
* \* EnTT Full-owning group, `registry.group<PositionComponent, VelocityComponent>()`
* \** EnTT Non-owning group, `registry.group(entt::get<<PositionComponent, VelocityComponent>>)`
* \*** EnTT Partial-owning group, `registry.group<PositionComponent>(entt::get<VelocityComponent>)`
* \**** EnTT uses `registry.view` and a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** flecs Frameworks, iterate components via [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)


### Iterate over entities with three components

![IterateThreeComponentsWithMixedEntities Plot](img/IterateThreeComponentsWithMixedEntities.png)

_(lower is better)_

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over    16 entities with three components | 6ns                        | 13ns                      | 6ns                           |
| Iterate over    64 entities with three components | 33ns                       | 51ns                      | 33ns                          |
| Iterate over   256 entities with three components | 144ns                      | 326ns                     | 144ns                         |
| Iterate over   ~1K entities with three components | 536ns                      | 1217ns                    | 537ns                         |
| Iterate over   ~4K entities with three components | 2109ns                     | 4876ns                    | 2111ns                        |

|                                                   | EnTT (full-owning group)   | EnTT (non-owning group)   | EnTT (partial-owning group)   |
|:--------------------------------------------------|:---------------------------|:--------------------------|:------------------------------|
| Iterate over  ~16K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  ~65K entities with three components | 0ms                        | 0ms                       | 0ms                           |
| Iterate over  262K entities with three components | 0ms                        | 1ms                       | 0ms                           |
| Iterate over   ~1M entities with three components | 2ms                        | 7ms                       | 2ms                           |
| Iterate over   ~2M entities with three components | 4ms                        | 14ms                      | 4ms                           |


**Notes:**
* Not every entity has all three components, some got removed
* pre create views/query when possible
* \* EnTT Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* \** EnTT Non-owning group, `registry.group(entt::get<<PositionComponent, VelocityComponent, DataComponent>>)`
* \*** EnTT Partial-owning group, `registry.group<PositionComponent, VelocityComponent>(entt::get<DataComponent>)`
* \**** EnTT uses `registry.view` and a [stable component](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#pointer-stability=) (`StablePositionComponent`)
* \***** flecs Frameworks, iterate components via [queries](https://github.com/SanderMertens/flecs/blob/master/docs/Queries.md)



## Contributing

I try to implement the ECS-examples as good as possible for each framework, if you have any improvements, feel free to make a PR or open an issue.

You can find the frameworks example(s) in [`src/`](src/) and benchmark [`benchmarks/`](benchmarks/benchmarks/) for more details.  
Also you can write tests for the framework example :)
and add some metadata in [plot.config.json](plot.config.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

### Using [Taskfile](https://taskfile.dev/installation/)

1. `git submodule update --init --recursive`
2. Build: `task build`
3. Run (All) Benchmarks: `task benchmark`
4. Plot Graphs: `task plot:all`

You can now find you benchmarks results in [`reports/`](reports/).

_You need python and some dependencies to run [gen-benchmark-report](scripts/gen-benchmark-report) (plotting)_

### ~~Step-by-Step~~

1. Configure and build benchmarks, see [Building Details](doc/README_building.md):
   1. `git submodule update --init --recursive` 
   2. `cmake -S . -B ./build`
   3. `cmake --build ./build`
2. Run benchmark(s), with [`run-benchmarks.sh`](run-benchmarks.sh) or each:
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt` _(console output)_ _(optional)_
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json` _(write json report)_
3. Plot Reports, after generating json reports, see [`plot-results.sh`](plot-results.sh):
   1. `python3 ./scripts/gen-benchmark-report -i ./info.json gen-plot ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate graphs)_
   2. `python3 ./scripts/gen-benchmark-report -i ./info.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/openecs.json ./reports/flecs.json` _(generate full report)_


## Links and More

* [Dependency Setup](doc/README_dependencies.md)
* [Building Details](doc/README_building.md)
* Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
  * [Forked cpp_vcpkg_project](https://github.com/abeimler/cpp_vcpkg_project)
* [Google benchmark](https://github.com/google/benchmark)
* https://github.com/SanderMertens/ecs-faq
* https://github.com/jslee02/awesome-entity-component-system


### Candidates

#### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: v3.11.1

#### Ginseng by @apples

> Ginseng is an entity-component-system (ECS) library designed for use in games.
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

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


#### _Deprecated_

I removed [anax](https://github.com/miguelmartin75/anax) and [Artemis-Cpp](https://github.com/matachi/Artemis-Cpp), they are out-of-date and didn't receive any updates in the last time.  
You can still checkout the old versions and branches.
