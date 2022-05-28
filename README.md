# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems:

* [EntityX](https://github.com/alecthomas/entityx)
* [EnTT](https://github.com/skypjack/entt)
* [flecs](https://github.com/SanderMertens/flecs)
* [Ginseng](https://github.com/apples/ginseng)
* [mustache](https://github.com/kirillochnev/mustache)
* [OpenEcs](https://github.com/Gronis/OpenEcs)

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)  
_(lower is faster)_


|                                      | EntityX   | EnTT    | Ginseng   | mustache   | Flecs       |
|:-------------------------------------|:----------|:--------|:----------|:-----------|:------------|
| Update   16K entities with 2 Systems | 0.0022s   | 0.0004s | 0.0017s   | 0.0011s    | **0.0003s** |
| Update   65K entities with 2 Systems | 0.0090s   | 0.0016s | 0.0053s   | 0.0052s    | **0.0012s** |
| Update  262K entities with 2 Systems | 0.0339s   | 0.0062s | 0.0166s   | 0.0199s    | **0.0045s** |
| Update  524K entities with 2 Systems | 0.0681s   | 0.0132s | 0.0336s   | 0.0357s    | **0.0089s** |
| Update    1M entities with 2 Systems | 0.1069s   | 0.0264s | 0.0579s   | 0.0683s    | **0.0175s** |
| Update    2M entities with 2 Systems | 0.2929s   | 0.0508s | 0.1374s   | 0.1323s    | **0.0329s** |

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

|                                           | EntityX   | EnTT    | Ginseng   | mustache    | Flecs   |
|:------------------------------------------|:----------|:--------|:----------|:------------|:--------|
| Create   16K entities with two Components | 0.0012s   | 0.0006s | 0.0012s   | **0.0005s** | 0.0065s |
| Create   65K entities with two Components | 0.0048s   | 0.0023s | 0.0069s   | **0.0020s** | 0.0256s |
| Create  262K entities with two Components | 0.0200s   | 0.0089s | 0.0244s   | **0.0081s** | 0.1498s |
| Create  524K entities with two Components | 0.0395s   | 0.0180s | 0.0502s   | **0.0161s** | 0.2904s |
| Create    1M entities with two Components | 0.0923s   | 0.0385s | 0.1250s   | **0.0349s** | 0.8126s |
| Create    2M entities with two Components | 0.2191s   | 0.0855s | 0.2793s   | **0.0762s** | 1.6758s |


### Destroy Entities

![DestroyEntities Plot](img/DestroyEntities.png)  
_(lower is faster)_

|                                            | EntityX   | EnTT    | Ginseng   | mustache    | Flecs   |
|:-------------------------------------------|:----------|:--------|:----------|:------------|:--------|
| Destroy   16K entities with two Components | 0.0006s   | 0.0006s | 0.0020s   | **0.0003s** | 0.0013s |
| Destroy   65K entities with two Components | 0.0023s   | 0.0029s | 0.0070s   | **0.0011s** | 0.0050s |
| Destroy  262K entities with two Components | 0.0092s   | 0.0099s | 0.0308s   | **0.0046s** | 0.0213s |
| Destroy  524K entities with two Components | 0.0195s   | 0.0199s | 0.0660s   | **0.0093s** | 0.0435s |
| Destroy    1M entities with two Components | 0.0388s   | 0.0452s | 0.2165s   | **0.0193s** | 0.1073s |
| Destroy    2M entities with two Components | 0.0831s   | 0.1056s | 0.3556s   | **0.0396s** | 0.2116s |


### Get one component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)  
_(lower is faster)_

|                                        | EntityX     | EnTT    | Ginseng     | mustache   | Flecs   |
|:---------------------------------------|:------------|:--------|:------------|:-----------|:--------|
| Unpack one Component in   16K entities | **0.0001s** | 0.0002s | **0.0001s** | 0.0003s    | 0.0020s |
| Unpack one Component in   65K entities | **0.0003s** | 0.0006s | 0.0006s     | 0.0013s    | 0.0082s |
| Unpack one Component in  262K entities | **0.0015s** | 0.0032s | 0.0062s     | 0.0054s    | 0.0330s |
| Unpack one Component in  524K entities | **0.0028s** | 0.0058s | 0.0109s     | 0.0108s    | 0.0681s |
| Unpack one Component in    1M entities | **0.0061s** | 0.0108s | 0.0206s     | 0.0219s    | 0.1342s |
| Unpack one Component in    2M entities | **0.0117s** | 0.0216s | 0.0430s     | 0.0434s    | 0.2719s |


### Get two components from Entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)  
_(lower is faster)_

|                                        | EntityX     | EnTT    | Ginseng   | mustache   | Flecs   |
|:---------------------------------------|:------------|:--------|:----------|:-----------|:--------|
| Unpack two Component in   16K entities | **0.0003s** | 0.0003s | 0.0004s   | 0.0006s    | 0.0040s |
| Unpack two Component in   65K entities | **0.0008s** | 0.0013s | 0.0023s   | 0.0024s    | 0.0162s |
| Unpack two Component in  262K entities | **0.0033s** | 0.0052s | 0.0081s   | 0.0099s    | 0.0657s |
| Unpack two Component in  524K entities | **0.0078s** | 0.0102s | 0.0185s   | 0.0201s    | 0.1312s |
| Unpack two Component in    1M entities | **0.0137s** | 0.0216s | 0.0481s   | 0.0398s    | 0.2708s |
| Unpack two Component in    2M entities | **0.0268s** | 0.0420s | 0.0675s   | 0.0800s    | 0.5280s |


### Get three components from Entity

![UnpackThreeComponentsFromMixedEntities Plot](img/UnpackThreeComponentsFromMixedEntities.png)  
_(lower is faster)_

|                                          | EntityX     | EnTT    | Ginseng   | mustache   | Flecs   |
|:-----------------------------------------|:------------|:--------|:----------|:-----------|:--------|
| Unpack three Component in   16K entities | **0.0004s** | 0.0005s | 0.0010s   | 0.0008s    | 0.0064s |
| Unpack three Component in   65K entities | **0.0011s** | 0.0019s | 0.0035s   | 0.0034s    | 0.0265s |
| Unpack three Component in  262K entities | **0.0062s** | 0.0081s | 0.0143s   | 0.0170s    | 0.1237s |
| Unpack three Component in  524K entities | **0.0091s** | 0.0174s | 0.0268s   | 0.0324s    | 0.2544s |
| Unpack three Component in    1M entities | **0.0199s** | 0.0318s | 0.0563s   | 0.0624s    | 0.6363s |
| Unpack three Component in    2M entities | **0.0391s** | 0.0625s | 0.1550s   | 0.1247s    | 1.2613s |


### System Updates (for-each entities with 2 Systems)

![SystemsUpdate Plot](img/SystemsUpdate.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | Ginseng   | mustache   | Flecs       |
|:-------------------------------------|:----------|:--------|:----------|:-----------|:------------|
| Update   16K entities with 2 Systems | 0.0022s   | 0.0004s | 0.0017s   | 0.0011s    | **0.0003s** |
| Update   65K entities with 2 Systems | 0.0090s   | 0.0016s | 0.0053s   | 0.0052s    | **0.0012s** |
| Update  262K entities with 2 Systems | 0.0339s   | 0.0062s | 0.0166s   | 0.0199s    | **0.0045s** |
| Update  524K entities with 2 Systems | 0.0681s   | 0.0132s | 0.0336s   | 0.0357s    | **0.0089s** |
| Update    1M entities with 2 Systems | 0.1069s   | 0.0264s | 0.0579s   | 0.0683s    | **0.0175s** |
| Update    2M entities with 2 Systems | 0.2929s   | 0.0508s | 0.1374s   | 0.1323s    | **0.0329s** |


### System Updates (for-each entities with 3 Systems)

![ComplexSystemsUpdate Plot](img/ComplexSystemsUpdate.png)  
_(lower is faster)_

|                                      | EntityX   | EnTT    | Ginseng   | mustache   | Flecs       | _OOP_       |
|:-------------------------------------|:----------|:--------|:----------|:-----------|:------------|:------------|
| Update   16K entities with 3 Systems | 0.0031s   | 0.0016s | 0.0014s   | 0.0024s    | **0.0012s** | **0.0003s** |
| Update   65K entities with 3 Systems | 0.0125s   | 0.0056s | 0.0059s   | 0.0097s    | **0.0048s** | **0.0014s** |
| Update  262K entities with 3 Systems | 0.0506s   | 0.0231s | 0.0240s   | 0.0404s    | **0.0200s** | **0.0061s** |
| Update  524K entities with 3 Systems | 0.1008s   | 0.0462s | 0.0589s   | 0.0806s    | **0.0399s** | **0.0124s** |
| Update    1M entities with 3 Systems | 0.2011s   | 0.0919s | 0.0958s   | 0.1794s    | **0.0797s** | **0.0250s** |
| Update    2M entities with 3 Systems | 0.3981s   | 0.1977s | 0.1929s   | 0.3626s    | **0.1574s** | **0.0511s** |




## Contributing

I try to implement the ECS-examples as good as possible for each framework, if you have any improvements, feel free to make a PR or open an issue.

You can find the frameworks example(s) in [`src/`](src/) and benchmark [`benchmarks/`](benchmarks/benchmarks/) for more details.  
Also you can write tests for the framework example :)
and add some metadata in [info.json](info.json).

_TODO: make more detailed "how to add framework"_

Read [CONTRIBUTING.md](CONTRIBUTING) for more details.

## Run Benchmarks

1. Configure and build benchmarks, see [Building Details](doc/README_building.md):
   1. `cmake -S . -B ./build`
   2. `cmake --build ./build`
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
