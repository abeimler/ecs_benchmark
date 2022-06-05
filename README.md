# Entity-Component-System Benchmarks

[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/MacOS/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/Windows/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![Actions Status](https://github.com/abeimler/ecs_benchmark/workflows/Ubuntu/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions)
[![codecov](https://codecov.io/gh/abeimler/ecs_benchmark/branch/master/graph/badge.svg)](https://codecov.io/gh/abeimler/ecs_benchmark)
[![CodeQL](https://github.com/abeimler/ecs_benchmark/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/abeimler/ecs_benchmark/actions/workflows/codeql-analysis.yml)

Simple Benchmarks of common ECS (Entity-Component-System) Frameworks:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [flecs](https://github.com/SanderMertens/flecs)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [OpenEcs](https://github.com/Gronis/OpenEcs)

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)  
_(lower is faster)_


|                                      | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Update   16K entities with 2 Systems | 0.0013s   | 0.0004s | 0.0004s   | 0.0003s    | 0.0011s   | **0.0002s** |
| Update   65K entities with 2 Systems | 0.0051s   | 0.0014s | 0.0018s   | 0.0010s    | 0.0044s   | **0.0010s** |
| Update  262K entities with 2 Systems | 0.0204s   | 0.0058s | 0.0072s   | 0.0049s    | 0.0178s   | **0.0044s** |
| Update  524K entities with 2 Systems | 0.0402s   | 0.0115s | 0.0138s   | 0.0086s    | 0.0347s   | **0.0087s** |
| Update    1M entities with 2 Systems | 0.0780s   | 0.0225s | 0.0243s   | **0.0166s**    | 0.0656s   | **0.0166s** |
| Update    2M entities with 2 Systems | 0.1580s   | 0.0421s | 0.0466s   | **0.0315s**    | 0.1294s   | 0.0338s |

### Environment

* **OS:** Linux
* **CPU:** 3.10GHz @ 4Cores
* **RAM:** 8 GB

## Details

All benchmarks are located in [`benchmark/benchmarks/`](benchmark/benchmarks/) and are written with [google/benchmark](https://github.com/google/benchmark).
Each benchmark must implement the template [ECSBenchmark.h](benchmark/benchmarks/ECSBenchmark.h).

Each framework has a sub-project in [`src/`](src) and must implement certain features (see [`src/base`](src/base)).

### Components

1. `PositionComponent` with `x` and `y` coord.
2. `DirectionComponent` with `x` and `y` for movement.
3. `DataComponent` with some nonsense data.

### Systems

1. `MovementSystem`: updates `PositionComponent` with (const) `DirectionComponent`
2. `DataSystem`: updates `DataComponent` with nonsense
3. `MoreComplexSystem`: updates Components with random data and nonsense


## More Benchmarks

Benchmarks of more common features, like "Creating entities", "Add and remove components", etc.

### Create Entities

![CreateEntities Plot](img/CreateEntities.png)  
_(lower is faster)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Create   16K entities with two Components | 0.0010s   | **0.0003s** | 0.0011s   | 0.0010s    | 0.0005s   | 0.0059s |
| Create   65K entities with two Components | 0.0042s   | **0.0012s** | 0.0050s   | 0.0038s    | 0.0021s   | 0.0222s |
| Create  262K entities with two Components | 0.0170s   | **0.0049s** | 0.0209s   | 0.0156s    | 0.0083s   | 0.0969s |
| Create  524K entities with two Components | 0.0362s   | **0.0101s** | 0.0454s   | 0.0321s    | 0.0170s   | 0.2572s |
| Create    1M entities with two Components | 0.0745s   | **0.0209s** | 0.0869s   | 0.0703s    | 0.0357s   | 0.6864s |
| Create    2M entities with two Components | 0.1752s   | **0.0469s** | 0.2019s   | 0.1691s    | 0.0814s   | 1.3725s |



### Destroy Entities

![DestroyEntities Plot](img/DestroyEntities.png)  
_(lower is faster)_

|                                            | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Destroy   16K entities with two Components | 0.0005s   | 0.0006s | 0.0018s   | 0.0007s    | **0.0003s**   | 0.0011s |
| Destroy   65K entities with two Components | 0.0020s   | 0.0025s | 0.0069s   | 0.0027s    | **0.0012s**   | 0.0045s |
| Destroy  262K entities with two Components | 0.0081s   | 0.0095s | 0.0289s   | 0.0110s    | **0.0046s**   | 0.0189s |
| Destroy  524K entities with two Components | 0.0164s   | 0.0193s | 0.0641s   | 0.0227s    | **0.0093s**   | 0.0364s |
| Destroy    1M entities with two Components | 0.0339s   | 0.0395s | 0.1519s   | 0.0452s    | **0.0186s**   | 0.0775s |
| Destroy    2M entities with two Components | 0.0720s   | 0.0853s | 0.3407s   | 0.0924s    | **0.0384s**   | 0.1841s |


### Get one (non-const) component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)  
_(lower is faster)_  

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Unpack one Component in   16K entities | **0.0001s**   | 0.0002s | **0.0001s**   | 0.0006s    | 0.0003s   | 0.0024s |
| Unpack one Component in   65K entities | **0.0005s**   | 0.0010s | **0.0005s**   | 0.0029s    | 0.0014s   | 0.0099s |
| Unpack one Component in  262K entities | **0.0022s**   | 0.0040s | 0.0023s   | 0.0095s    | 0.0068s   | 0.0360s |
| Unpack one Component in  524K entities | **0.0041s**   | 0.0100s | 0.0049s   | 0.0189s    | 0.0116s   | 0.0705s |
| Unpack one Component in    1M entities | **0.0088s**   | 0.0161s | 0.0093s   | 0.0374s    | 0.0232s   | 0.1405s |
| Unpack one Component in    2M entities | **0.0170s**   | 0.0321s | 0.0274s   | 0.0747s    | 0.0467s   | 0.2755s |


**Note:**
* Get one non-const component
   1. `PositionComponent`


### Get one (const) component from Entity

![UnpackOneComponentConst Plot](img/UnpackOneComponentConst.png)  
_(lower is faster)_

|                                                | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-----------------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Unpack one (const) Component in   16K entities | **0.0001s**   | 0.0002s | **0.0001s**   | 0.0003s    | 0.0003s   | 0.0015s |
| Unpack one (const) Component in   65K entities | 0.0006s   | 0.0009s | **0.0005s**   | 0.0011s    | 0.0013s   | 0.0061s |
| Unpack one (const) Component in  262K entities | **0.0023s**   | 0.0037s | **0.0023s**   | 0.0046s    | 0.0055s   | 0.0247s |
| Unpack one (const) Component in  524K entities | **0.0042s**   | 0.0090s | 0.0048s   | 0.0092s    | 0.0141s   | 0.0554s |
| Unpack one (const) Component in    1M entities | **0.0086s**   | 0.0148s | 0.0097s   | 0.0178s    | 0.0219s   | 0.0982s |
| Unpack one (const) Component in    2M entities | **0.0165s**   | 0.0297s | 0.0237s   | 0.0380s    | 0.0429s   | 0.1935s |


**Note:**
 * Get one const component
   1. `const PositionComponent`


### Get two components from Entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)  
_(lower is faster)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Unpack two Component in   16K entities | **0.0002s**   | 0.0004s | **0.0002s**   | 0.0009s    | 0.0006s   | 0.0045s |
| Unpack two Component in   65K entities | **0.0007s**   | 0.0016s | 0.0008s   | 0.0039s    | 0.0025s   | 0.0150s |
| Unpack two Component in  262K entities | **0.0029s**   | 0.0066s | 0.0040s   | 0.0140s    | 0.0102s   | 0.0596s |
| Unpack two Component in  524K entities | **0.0057s**   | 0.0139s | 0.0078s   | 0.0295s    | 0.0234s   | 0.1183s |
| Unpack two Component in    1M entities | **0.0116s**   | 0.0272s | 0.0156s   | 0.0569s    | 0.0401s   | 0.2501s |
| Unpack two Component in    2M entities | **0.0234s**   | 0.0529s | 0.0357s   | 0.1114s    | 0.0799s   | 0.5049s |


**Note:**
* Get non-const- and const-component
   1. `PositionComponent`
   2. `const DirectionComponent`

### Get three components from Entity

![UnpackThreeComponentsFromMixedEntities Plot](img/UnpackThreeComponentsFromMixedEntities.png)  
_(lower is faster)_

|                                          | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-----------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Unpack three Component in   16K entities | **0.0002s**   | 0.0005s | 0.0003s   | 0.0013s    | 0.0008s   | 0.0060s |
| Unpack three Component in   65K entities | **0.0009s**   | 0.0023s | 0.0014s   | 0.0051s    | 0.0037s   | 0.0242s |
| Unpack three Component in  262K entities | **0.0040s**   | 0.0097s | 0.0058s   | 0.0220s    | 0.0161s   | 0.1066s |
| Unpack three Component in  524K entities | **0.0084s**   | 0.0182s | 0.0123s   | 0.0424s    | 0.0417s   | 0.3030s |
| Unpack three Component in    1M entities | **0.0161s**   | 0.0462s | 0.0359s   | 0.0838s    | 0.0627s   | 0.6558s |
| Unpack three Component in    2M entities | **0.0325s**   | 0.0740s | 0.0483s   | 0.1640s    | 0.1247s   | 1.3012s |


**Note:**
* Get two non-const- and const- component(s)
   1. `PositionComponent`
   2. `const DirectionComponent`
   3. `DataComponent` (optional)


### Remove and add component from Entity

![RemoveAddComponent Plot](img/RemoveAddComponent.png)  
_(lower is faster)_

|                                              | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:---------------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Remove and Add a Component in   16K entities | 0.0010s   | 0.0010s | **0.0005s**   | 0.0057s    | **0.0005s**   | 0.0124s |
| Remove and Add a Component in   65K entities | 0.0039s   | 0.0040s | **0.0021s**   | 0.0229s    | **0.0021s**   | 0.0494s |
| Remove and Add a Component in  262K entities | 0.0156s   | 0.0167s | 0.0088s   | 0.0922s    | **0.0084s**   | 0.1978s |
| Remove and Add a Component in  524K entities | 0.0319s   | 0.0328s | 0.0171s   | 0.1844s    | **0.0168s**   | 0.3955s |
| Remove and Add a Component in    1M entities | 0.0640s   | 0.0655s | 0.0357s   | 0.3685s    | **0.0338s**   | 0.7882s |
| Remove and Add a Component in    2M entities | 0.1280s   | 0.1320s | 0.0708s   | 0.7376s    | **0.0676s**   | 1.5826s |


### System Updates (for-each entities with 2 Systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | Ginseng   | mustache   | OpenEcs   | Flecs   |
|:-------------------------------------|:----------|:--------|:----------|:-----------|:----------|:--------|
| Update   16K entities with 2 Systems | 0.0013s   | 0.0004s | 0.0004s   | 0.0003s    | 0.0011s   | **0.0002s** |
| Update   65K entities with 2 Systems | 0.0051s   | 0.0014s | 0.0018s   | **0.0010s**    | 0.0044s   | **0.0010s** |
| Update  262K entities with 2 Systems | 0.0204s   | 0.0058s | 0.0072s   | 0.0049s    | 0.0178s   | **0.0044s** |
| Update  524K entities with 2 Systems | 0.0402s   | 0.0115s | 0.0138s   | 0.0086s    | 0.0347s   | **0.0087s** |
| Update    1M entities with 2 Systems | 0.0780s   | 0.0225s | 0.0243s   | **0.0166s**    | 0.0656s   | **0.0166s** |
| Update    2M entities with 2 Systems | 0.1580s   | 0.0421s | 0.0466s   | **0.0315s**    | 0.1294s   | 0.0338s |


### System Updates (for-each entities with 3 Systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT\*    | EnTT (runtime)\** | EnTT (group)\*** | Ginseng   | mustache   | OpenEcs   | Flecs   | _OOP_     |
|:-------------------------------------|:----------|:--------|:-----------------|:----------------|:----------|:-----------|:----------|:--------|:--------|
| Update   16K entities with 3 Systems | 0.0033s   | **0.0013s** | 0.0027s          | **0.0013s**     | 0.0015s   | 0.0015s    | 0.0025s   | **0.0013s** | _**0.0004s**_ |
| Update   65K entities with 3 Systems | 0.0135s   | 0.0057s | 0.0113s          | **0.0054s**     | 0.0066s   | 0.0058s    | 0.0105s   | 0.0055s | _**0.0018s**_ |
| Update  262K entities with 3 Systems | 0.0538s   | 0.0232s | 0.0456s          | **0.0231s**     | 0.0264s   | 0.0220s    | 0.0440s   | 0.0288s | _**0.0077s**_ |
| Update  524K entities with 3 Systems | 0.1060s   | 0.0467s | 0.0912s          | 0.0487s         | 0.0528s   | 0.0596s    | 0.0883s   | **0.0445s** | _**0.0179s**_ |
| Update    1M entities with 3 Systems | 0.2542s   | 0.0922s | 0.1811s          | 0.1125s         | 0.1177s   | 0.0871s    | 0.1743s   | **0.0849s** | _**0.0318s**_ |
| Update    2M entities with 3 Systems | 0.4243s   | 0.1828s | 0.3591s          | 0.2974s         | 0.2129s   | 0.1783s    | 0.3397s   | **0.1671s** | _**0.0624s**_ |

**Notes:**
   * \*   EnTT Framework, iterate components via [views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#views=)
   * \**  EnTT Framework, iterate components via [runtime views](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#runtime-views=)
   * \*** EnTT Framework, iterate components via [groups](https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system#groups=):
      1. `DataSystem`: No Group, use normal `view`. _(Can't group a single component)_
      2. `MovementSystem`: Partial-owning group, `registry.group<PositionComponent>(::entt::get<const DirectionComponent>)`
      3. `MoreComplexSystem`: Full-owning group, `registry.group<PositionComponent, DirectionComponent, DataComponent>()`



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

## More Details

 * [Dependency Setup](doc/README_dependencies.md)
 * [Building Details](doc/README_building.md)
 * Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
 * [Google benchmark](https://github.com/google/benchmark)
 * https://github.com/SanderMertens/ecs-faq
