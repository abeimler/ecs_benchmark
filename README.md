# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/MacOS/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/Windows/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/Ubuntu/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![codecov](https://codecov.io/gh/abeimler/ecs_benchmark/branch/master/graph/badge.svg)](https://codecov.io/gh/abeimler/ecs_benchmark)
[![CodeQL](https://github.com/abeimler/ecs_benchmark/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions/workflows/codeql-analysis.yml)
![License](https://img.shields.io/github/license/abeimler/ecs_benchmark)

Simple Benchmarks of common ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [flecs](https://github.com/SanderMertens/flecs)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [OpenEcs](https://github.com/Gronis/OpenEcs)

## TL;DR Results

### Update Systems 

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)  
_(lower is faster)_  
_for-each entities (with mixed components) in 2 Systems, see [Notes]() for more details_


|                                      | EntityX   | EnTT    | Ginseng | mustache | OpenEcs   | Flecs    |
|:-------------------------------------|:----------|:--------|:--------|:---------|:----------|:---------|
| Update  ~16K entities with 2 Systems | 2ms       | **0ms** | **0ms** | **0ms**  | 1ms       | **0ms**  |
| Update  ~65K entities with 2 Systems | 8ms       | 2ms     | 2ms     | 2ms      | 6ms       | **1ms**  |
| Update  262K entities with 2 Systems | 33ms      | 9ms     | 10ms    | 9ms      | 23ms      | **7ms**  |
| Update  524K entities with 2 Systems | 64ms      | 18ms    | 20ms    | 17ms     | 45ms      | **15ms** |
| Update   ~1M entities with 2 Systems | 126ms     | 35ms    | 37ms    | 33ms     | 82ms      | **29ms** |
| Update   ~2M entities with 2 Systems | 252ms     | 61ms    | 66ms    | 59ms     | 170ms     | **53ms** |



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
* **CPU:** 3.10GHz @ 4Cores
* **RAM:** 8 GB

Run on my old Laptop :)


### Create Entities

![CreateEntities Plot](img/CreateEntities.png)  
_(lower is faster)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache | OpenEcs  | Flecs   |
|:------------------------------------------|:----------|:--------|:----------|:---------|:---------|:--------|
| Create  ~16K entities with two Components | 1ms       | **0ms** | 1ms       | **0ms**  | **0ms**  | 6ms     |
| Create  ~65K entities with two Components | 4ms       | 2ms     | 5ms       | 3ms      | **1ms**  | 25ms    |
| Create  262K entities with two Components | 19ms      | **8ms** | 22ms      | 15ms     | **8ms**  | 112ms   |
| Create  524K entities with two Components | 40ms      | 18ms    | 50ms      | 31ms     | **16ms** | 290ms   |
| Create   ~1M entities with two Components | 88ms      | 38ms    | 100ms     | 68ms     | **34ms** | 774ms   |
| Create   ~2M entities with two Components | 209ms     | 89ms    | 251ms     | 159ms    | **77ms** | 1543ms  |


### Destroy Entities

![DestroyEntities Plot](img/DestroyEntities.png)  
_(lower is faster)_

|                                            | EntityX | EnTT    | Ginseng   | mustache | OpenEcs  | Flecs   |
|:-------------------------------------------|:--------|:--------|:----------|:---------|:---------|:--------|
| Destroy  ~16K entities with two Components | **0ms** | **0ms** | 1ms       | **0ms**  | **0ms**  | 1ms     |
| Destroy  ~65K entities with two Components | 2ms     | 2ms     | 6ms       | 2ms      | **1ms**  | 4ms     |
| Destroy  262K entities with two Components | 8ms     | 9ms     | 27ms      | 9ms      | **4ms**  | 16ms    |
| Destroy  524K entities with two Components | 17ms    | 19ms    | 54ms      | 20ms     | **9ms**  | 34ms    |
| Destroy   ~1M entities with two Components | 35ms    | 39ms    | 124ms     | 42ms     | **19ms** | 73ms    |
| Destroy   ~2M entities with two Components | 76ms    | 85ms    | 311ms     | 89ms     | **40ms** | 173ms   |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)  
_(lower is faster)_  

|                                        | EntityX | EnTT    | Ginseng  | mustache | OpenEcs | Flecs   |
|:---------------------------------------|:--------|:--------|:---------|:---------|:--------|:--------|
| Unpack one Component in  ~16K entities | **0ms** | **0ms** | **0ms**  | **0ms**  | **0ms** | 2ms     |
| Unpack one Component in  ~65K entities | **0ms** | **0ms** | **0ms**  | 2ms      | 1ms     | 8ms     |
| Unpack one Component in  262K entities | **1ms** | 3ms     | **1ms**  | 8ms      | 5ms     | 33ms    |
| Unpack one Component in  524K entities | **3ms** | 7ms     | **3ms**  | 17ms     | 10ms    | 66ms    |
| Unpack one Component in   ~1M entities | **7ms** | 14ms    | **7ms**  | 35ms     | 21ms    | 135ms   |
| Unpack one Component in   ~2M entities | 15ms    | 28ms    | **14ms** | 70ms     | 43ms    | 265ms   |

**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)  
_(lower is faster)_

|                                                | EntityX | EnTT    | Ginseng  | mustache | OpenEcs | Flecs   |
|:-----------------------------------------------|:--------|:--------|:---------|:---------|:--------|:--------|
| Unpack one (const) Component in  ~16K entities | **0ms** | **0ms** | **0ms**  | **0ms**  | **0ms** | 1ms     |
| Unpack one (const) Component in  ~65K entities | **0ms** | **0ms** | **0ms**  | 1ms      | 1ms     | 5ms     |
| Unpack one (const) Component in  262K entities | **1ms** | 3ms     | **1ms**  | 4ms      | 5ms     | 22ms    |
| Unpack one (const) Component in  524K entities | **3ms** | 6ms     | **3ms**  | 8ms      | 10ms    | 45ms    |
| Unpack one (const) Component in   ~1M entities | **7ms** | 13ms    | **7ms**  | 16ms     | 20ms    | 93ms    |
| Unpack one (const) Component in   ~2M entities | 15ms    | 27ms    | **14ms** | 32ms     | 40ms    | 182ms   |

**Note:**
* Get one const component
  1. `const PositionComponent`


### Get two components from Entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)  
_(lower is faster)_

|                                        | EntityX  | EnTT    | Ginseng | mustache | OpenEcs | Flecs   |
|:---------------------------------------|:---------|:--------|:--------|:---------|:--------|:--------|
| Unpack two Component in  ~16K entities | **0ms**  | **0ms** | **0ms** | **0ms**  | **0ms** | 3ms     |
| Unpack two Component in  ~65K entities | **0ms**  | 1ms     | **0ms** | 3ms      | 2ms     | 13ms    |
| Unpack two Component in  262K entities | **2ms**  | 6ms     | 3ms     | 13ms     | 9ms     | 57ms    |
| Unpack two Component in  524K entities | **5ms**  | 13ms    | 6ms     | 26ms     | 18ms    | 110ms   |
| Unpack two Component in   ~1M entities | **11ms** | 27ms    | 13ms    | 53ms     | 37ms    | 219ms   |
| Unpack two Component in   ~2M entities | **23ms** | 54ms    | 27ms    | 106ms    | 75ms    | 438ms   |

**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const VelocityComponent`

### Get three components from Entity

![UnpackThreeComponentsFromMixedEntities Plot](img/UnpackThreeComponentsFromMixedEntities.png)  
_(lower is faster)_

|                                          | EntityX  | EnTT    | Ginseng | mustache   | OpenEcs | Flecs   |
|:-----------------------------------------|:---------|:--------|:--------|:-----------|:--------|:--------|
| Unpack three Component in  ~16K entities | **0ms**  | **0ms** | **0ms** | 1ms        | **0ms** | 5ms     |
| Unpack three Component in  ~65K entities | **1ms**  | 2ms     | **1ms** | 4ms        | 3ms     | 22ms    |
| Unpack three Component in  262K entities | **4ms**  | 9ms     | 6ms     | 18ms       | 14ms    | 96ms    |
| Unpack three Component in  524K entities | **9ms**  | 18ms    | 12ms    | 38ms       | 28ms    | 219ms   |
| Unpack three Component in   ~1M entities | **19ms** | 36ms    | 25ms    | 77ms       | 58ms    | 584ms   |
| Unpack three Component in   ~2M entities | **38ms** | 73ms    | 51ms    | 154ms      | 116ms   | 1208ms  |

**Note:**
* Not every entity has three components, some has only two
* Get two non-const- and const-component(s)
   1. `PositionComponent`
   2. `const VelocityComponent`
   3. `DataComponent` (optional)


### Remove and add component from Entity

![RemoveAddComponent Plot](img/RemoveAddComponent.png)  
_(lower is faster)_

|                                              | EntityX | EnTT   | Ginseng  | mustache   | OpenEcs  | Flecs   |
|:---------------------------------------------|:--------|:-------|:---------|:-----------|:---------|:--------|
| Remove and Add a Component in  ~16K entities | **0ms** | 1ms    | **0ms**  | 5ms        | **0ms**  | 12ms    |
| Remove and Add a Component in  ~65K entities | 3ms     | 4ms    | **1ms**  | 22ms       | 2ms      | 49ms    |
| Remove and Add a Component in  262K entities | 15ms    | 16ms   | **8ms**  | 92ms       | **8ms**  | 196ms   |
| Remove and Add a Component in  524K entities | 30ms    | 33ms   | 21ms     | 183ms      | **16ms** | 392ms   |
| Remove and Add a Component in   ~1M entities | 61ms    | 67ms   | **32ms** | 370ms      | 33ms     | 787ms   |
| Remove and Add a Component in   ~2M entities | 122ms   | 134ms  | **64ms** | 736ms      | 67ms     | 1590ms  |

**Note:**
* Remove and add `PositionComponent`


### Update Systems (for-each entities in 2 Systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | Ginseng | mustache | OpenEcs   | Flecs    |
|:-------------------------------------|:----------|:--------|:--------|:---------|:----------|:---------|
| Update  ~16K entities with 2 Systems | 1ms       | **0ms** | **0ms** | **0ms**  | 1ms       | **0ms**  |
| Update  ~65K entities with 2 Systems | 6ms       | **1ms** | **1ms** | **1ms**  | 4ms       | **1ms**  |
| Update  262K entities with 2 Systems | 25ms      | 5ms     | 6ms     | 5ms      | 17ms      | **4ms**  |
| Update  524K entities with 2 Systems | 49ms      | 11ms    | 13ms    | **9ms**  | 34ms      | **9ms**  |
| Update   ~1M entities with 2 Systems | 97ms      | 23ms    | 25ms    | 19ms     | 66ms      | **17ms** |
| Update   ~2M entities with 2 Systems | 195ms     | 43ms    | 47ms    | 36ms     | 128ms     | **33ms** |

**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`

### Update Systems (for-each entities (with mixed components) in 2 Systems)

![SystemsUpdateMixedEntities Plot](img/SystemsUpdateMixedEntities.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | Ginseng | mustache | OpenEcs   | Flecs    |
|:-------------------------------------|:----------|:--------|:--------|:---------|:----------|:---------|
| Update  ~16K entities with 2 Systems | 2ms       | **0ms** | **0ms** | **0ms**  | 1ms       | **0ms**  |
| Update  ~65K entities with 2 Systems | 8ms       | 2ms     | 2ms     | 2ms      | 6ms       | **1ms**  |
| Update  262K entities with 2 Systems | 33ms      | 9ms     | 10ms    | 9ms      | 23ms      | **7ms**  |
| Update  524K entities with 2 Systems | 64ms      | 18ms    | 20ms    | 17ms     | 45ms      | **15ms** |
| Update   ~1M entities with 2 Systems | 126ms     | 35ms    | 37ms    | 33ms     | 82ms      | **29ms** |
| Update   ~2M entities with 2 Systems | 252ms     | 61ms    | 66ms    | 59ms     | 170ms     | **53ms** |

**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
* Not every entity has all three components, some got removed


### Update Systems (for-each entities in 3 Systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | EnTT (runtime)   | EnTT (group) | Ginseng | mustache | OpenEcs   | Flecs     | _OOP_      |
|:-------------------------------------|:----------|:--------|:-----------------|:-------------|:--------|:---------|:----------|:----------|:-----------|
| Update  ~16K entities with 3 Systems | 3ms       | **1ms** | 2ms              | **1ms**      | **1ms** | **1ms**  | 2ms       | **1ms**   | _**0ms**_  |
| Update  ~65K entities with 3 Systems | 12ms      | 5ms     | 11ms             | 5ms          | 5ms     | **4ms**  | 9ms       | **4ms**   | _**1ms**_  |
| Update  262K entities with 3 Systems | 50ms      | 23ms    | 44ms             | 22ms         | 23ms    | **19ms** | 41ms      | **19ms**  | _**6ms**_  |
| Update  524K entities with 3 Systems | 101ms     | 46ms    | 89ms             | 47ms         | 47ms    | 40ms     | 82ms      | **38ms**  | _**12ms**_ |
| Update   ~1M entities with 3 Systems | 201ms     | 93ms    | 177ms            | 106ms        | 94ms    | 79ms     | 164ms     | **76ms**  | _**24ms**_ |
| Update   ~2M entities with 3 Systems | 397ms     | 184ms   | 352ms            | 292ms        | 187ms   | 156ms    | 324ms     | **151ms** | _**49ms**_ |

**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* \*   EnTT Framework, iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT Framework, iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT Framework, iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
   1. `DataSystem`: No Group, use normal `view`. _(Can't group a single component)_
   2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(::entt::get<const VelocityComponent>)`
   3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`
* You can ignore the Object-Oriented-Solution (_OOP_) ;) ... I just add them for fun, focus more on the ECS-Frameworks
  * ECS CAN be fast then the OO-Solution, it really depends on how big and complex the Architecture is
  * However, ECS has some other advantages over OOP, see [FAQ from SanderMertens](https://github.com/SanderMertens/ecs-faq#how-is-ecs-different-from-oop=)


### Update Systems (for-each entities (with mixed components) in 3 Systems)

![ComplexSystemsUpdateMixedEntities Plot](img/ComplexSystemsUpdateMixedEntities.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | EnTT (runtime)   | EnTT (group) | Ginseng | mustache | OpenEcs   | Flecs     |
|:-------------------------------------|:----------|:--------|:-----------------|:-------------|:--------|:---------|:----------|:----------|
| Update  ~16K entities with 3 Systems | 5ms       | **2ms** | 4ms              | **2ms**      | **2ms** | **2ms**  | 4ms       | **2ms**   |
| Update  ~65K entities with 3 Systems | 20ms      | 11ms    | 18ms             | 10ms         | 10ms    | **9ms**  | 16ms      | **9ms**   |
| Update  262K entities with 3 Systems | 82ms      | 43ms    | 74ms             | 42ms         | 42ms    | 38ms     | 68ms      | **37ms**  |
| Update  524K entities with 3 Systems | 163ms     | 86ms    | 148ms            | 91ms         | 84ms    | 76ms     | 136ms     | **74ms**  |
| Update   ~1M entities with 3 Systems | 323ms     | 170ms   | 292ms            | 216ms        | 166ms   | 151ms    | 271ms     | **146ms** |
| Update   ~2M entities with 3 Systems | 639ms     | 335ms   | 577ms            | 718ms        | 328ms   | 297ms    | 531ms     | **288ms** |


**Note:**
* Systems used
    1. `MovementSystem`
    2. `DataSystem`
    3. `MoreComplexSystem`
* Not every entity has all three components, some got removed
* \*   EnTT Framework, iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
* \**  EnTT Framework, iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
* \*** EnTT Framework, iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
    1. `DataSystem`: No Group, use normal `view`. _(Can't group a single component)_
    2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(::entt::get<const VelocityComponent>)`
    3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, VelocityComponent, DataComponent>()`




## Contributing

I try to implement the ECS-examples as good as possible for each framework, if you have any improvements, feel free to make a PR or open an issue.

You can find the frameworks example(s) in [`src/`](src/) and benchmark [`benchmarks/`](benchmarks/benchmarks/) for more details.  
Also you can write tests for the framework example :)
and add some metadata in [info.json](info.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

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

_You need python and some dependencies to run [gen-benchmark-report](scripts/gen-benchmark-report)_

## Links and More

* [Dependency Setup](doc/README_dependencies.md)
* [Building Details](doc/README_building.md)
* Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
* [Google benchmark](https://github.com/google/benchmark)
* https://github.com/SanderMertens/ecs-faq
* https://github.com/jslee02/awesome-entity-component-system


### Candidates

#### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.

Version: 1.1.2 (Dec 2021)

#### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++.

Version: 3.10.1

#### Ginseng by @apples

> Ginseng is an entity-component-system (ECS) library designed for use in games.  
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.  
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

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


#### _Deprecated_

I removed [anax](https://github.com/miguelmartin75/anax) and [Artemis-Cpp](https://github.com/matachi/Artemis-Cpp), they are out-of-date and didn't receive any updates in the last time.  
You can still checkout the old versions and branches.