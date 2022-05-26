# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [OpenEcs](https://github.com/Gronis/OpenEcs)

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)
_(lower is better)_

|                                     | EntityX   | EnTT        | Ginseng     | mustache   | OOP     |
|:------------------------------------|:----------|:------------|:------------|:-----------|:--------|
| Update  10k entities with 2 Systems | 0.0010s   | **0.0002s** | **0.0002s** | 0.0007s    | 0.0002s |
| Update 100k entities with 2 Systems | 0.0096s   | 0.0026s     | **0.0025s** | 0.0069s    | 0.0022s |
| Update 500k entities with 2 Systems | 0.0472s   | 0.0125s     | **0.0122s** | 0.0340s    | 0.0117s |
| Update   1M entities with 2 Systems | 0.0924s   | **0.0218s** | 0.0243s     | 0.0645s    | 0.0242s |

### Environment

* **OS:** Linux
* **CPU:** 3.10GHz @ 4Cores
* **RAM:** 8 GB

## Details

All benchmarks are located in [`benchmark/benchmarks/`](benchmark/benchmarks/) and are written with [google/benchmark](https://github.com/google/benchmark).
Each benchmark must implement the template [ECSBenchmark.h](benchmark/benchmarks/ECSBenchmark.h).

Each framework has a sub-project in [`src/`](src) and must implement certain features (see [`src/base`](src/base)).

### Components

1. PositionComponent with `x` and `y` Coord.
2. DirectionComponent with `x` and `y` for movement
3. DataComponent with some non-sense data.

### Systems

1. MovementSystem: updates PositionComponent
2. DataSystem: updates DataComponent
3. MoreComplexSystem: updates Components with random data and stuff


## More Benchmarks

### Create Entities

![CreateEntities Plot](img/CreateEntities.png)
_(lower is better)_

|                                          | EntityX   | EnTT    | Ginseng   | mustache   | OOP         |
|:-----------------------------------------|:----------|:--------|:----------|:-----------|:------------|
| Create  10k entities with two Components | 0.0007s   | 0.0004s | 0.0009s   | 0.0003s    | **0.0001s** |
| Create 100k entities with two Components | 0.0070s   | 0.0034s | 0.0093s   | 0.0034s    | **0.0014s** |
| Create 500k entities with two Components | 0.0367s   | 0.0178s | 0.0502s   | 0.0164s    | **0.0081s** |
| Create   1M entities with two Components | 0.0798s   | 0.0372s | 0.0970s   | 0.0342s    | **0.0172s** |


### Destroy Entities

![DestroyEntities Plot](img/DestroyEntities.png)
_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache    | OOP       |
|:------------------------------------------|:----------|:--------|:----------|:------------|:----------|
| Destroy  10k entities with two Components | 0.0003s   | 0.0003s | 0.0012s   | **0.0002s** | 0.0344s   |
| Destroy 100k entities with two Components | 0.0032s   | 0.0031s | 0.0120s   | **0.0017s** | 6.8016s   |
| Destroy 500k entities with two Components | 0.0173s   | 0.0167s | 0.0644s   | **0.0088s** | 173.4660s |


### Get one component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)
_(lower is better)_

|                                       | EntityX   | EnTT    | Ginseng     | mustache   | OOP     |
|:--------------------------------------|:----------|:--------|:------------|:-----------|:--------|
| Unpack one Component in  10k entities | 0.0001s   | 0.0001s | **0.0000s** | 0.0002s    | 0.0002s |
| Unpack one Component in 100k entities | 0.0005s   | 0.0010s | **0.0006s** | 0.0020s    | 0.0020s |
| Unpack one Component in 500k entities | 0.0031s   | 0.0059s | **0.0034s** | 0.0103s    | 0.0103s |
| Unpack one Component in   1M entities | 0.0061s   | 0.0095s | **0.0068s** | 0.0206s    | 0.0206s |


### Get two components from Entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)
_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng     | mustache   | OOP     |
|:---------------------------------------|:----------|:--------|:------------|:-----------|:--------|
| Unpack two Components in  10k entities | 0.0001s   | 0.0002s | **0.0001s** | 0.0004s    | 0.0004s |
| Unpack two Components in 100k entities | 0.0011s   | 0.0020s | **0.0011s** | 0.0037s    | 0.0040s |
| Unpack two Components in 500k entities | 0.0053s   | 0.0102s | **0.0061s** | 0.0189s    | 0.0198s |
| Unpack two Components in   1M entities | 0.0105s   | 0.0206s | **0.0122s** | 0.0379s    | 0.0372s |


### Get three components from Entity

![UnpackThreeComponentsFromMixedEntities Plot](img/UnpackThreeComponentsFromMixedEntities.png)
_(lower is better)_

|                                          | EntityX   | EnTT    | Ginseng     | mustache   | OOP     |
|:-----------------------------------------|:----------|:--------|:------------|:-----------|:--------|
| Unpack three Components in  10k entities | 0.0002s   | 0.0002s | **0.0001s** | 0.0005s    | 0.0010s |
| Unpack three Components in 100k entities | 0.0017s   | 0.0025s | **0.0018s** | 0.0054s    | 0.0103s |
| Unpack three Components in 500k entities | 0.0088s   | 0.0130s | **0.0095s** | 0.0297s    | 0.0571s |
| Unpack three Components in   1M entities | 0.0176s   | 0.0261s | **0.0183s** | 0.0596s    | 0.1030s |


### System Updates (for-each entities with 2 Systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)
_(lower is better)_

|                                     | EntityX   | EnTT        | Ginseng     | mustache   | OOP     |
|:------------------------------------|:----------|:------------|:------------|:-----------|:--------|
| Update  10k entities with 2 Systems | 0.0010s   | **0.0002s** | **0.0002s** | 0.0007s    | 0.0002s |
| Update 100k entities with 2 Systems | 0.0096s   | 0.0026s     | **0.0025s** | 0.0069s    | 0.0022s |
| Update 500k entities with 2 Systems | 0.0472s   | 0.0125s     | **0.0122s** | 0.0340s    | 0.0117s |
| Update   1M entities with 2 Systems | 0.0924s   | **0.0218s** | 0.0243s     | 0.0645s    | 0.0242s |





## Contributing

I try to implement the ECS-examples as best as possible for each framework, if you have any improvements, feel free to make a PR or open an issue.

See frameworks example(s) in [`src/`](src/) and benchmark [`benchmarks/`](benchmarks/benchmarks/) for more details.  
You can also write tests for the framework example :)
Also add some meta data in [info.json](info.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

1. Configure and build benchmarks, see [Building Details](doc/README_building.md):
   1. `cmake -S . -B ./build`
   2. `cmake --build ./build`
2. Run benchmarks, with [`run-benchmarks.sh`](run-benchmarks.sh) or each:
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt` _(console output)_ _(optional)_
   * `./build/benchmark/benchmarks/entt/ecs-benchmark-entt --benchmark_format=json > ./reports/entt.json` _(write json report)_
3. Plot Reports, after generating json reports, see (`plot-results.sh`)[plot-results.sh]:
   1. `python3 ./scripts/gen-benchmark-report -i ./info.json gen-plot ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/oop.json ./reports/openecs.json` _(generate graphs)_
   2. `python3 ./scripts/gen-benchmark-report -i ./info.json gen-results-md ./reports/entityx.json ./reports/entt.json ./reports/ginseng.json ./reports/mustache.json ./reports/oop.json ./reports/openecs.json` _(generate full report)_

_You need python and some dependencies to run [gen-benchmark-report](scripts/gen-benchmark-report)_

## More Details

 * [Dependency Setup](doc/README_dependencies.md)
 * [Building Details](doc/README_building.md)
 * Project Template, mix of: [starter_template](https://github.com/cpp-best-practices/gui_starter_template) and [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
 * [Google benchmark](https://github.com/google/benchmark)
