# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems: 
[EnTT](https://github.com/skypjack/entt) vs. [entityx](https://github.com/alecthomas/entityx) vs. [anax](https://github.com/miguelmartin75/anax) vs. [Artemis-Cpp](https://github.com/vinova/Artemis-Cpp) vs. [Ginseng](https://github.com/apples/ginseng)

## Candidates

### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use entity-component system in modern C++.
> ECS is an architectural pattern used mostly in game development.
> I started using another well known Entity Component System named entityx.
> 
> While I was playing with it, I found that I didn't like that much the way it manages its memory. Moreover, I was pretty sure that one > could achieve better performance with a slightly modified pool under the hood.
> That's also the reason for which the interface is quite similar to the one of entityx, so that EnTT can be used as a drop-in > replacement for it with a minimal effort.

Version: 1.1.0 (September 2017)


### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. 
> The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.
> 
> EntityX is an EC system that uses C++11 features to provide type-safe component management, event delivery, etc. 
> It was built during the creation of a 2D space shooter.

Version: 1.1.2 (Juli 2017) and the [`compiler-time`](https://github.com/alecthomas/entityx/tree/experimental/compile_time) Version 2.0.0 (?) (August 2017)


### anax by @miguelmartin75

> anax is an open source C++ entity system designed to be portable, lightweight and easy to use. 
> It is aimed toward Game Development, however it would be possible to use it for other projects.

Version: 2.1.0 (Januar 2017)


### Artemis C++ by @vinova

> A C++ port of Artemis Entity System Framework.
> 
> The port was orignially written by Sidar Talei, in which he used several C++11 features such as deleted function, variadic templates, nullptr, etc… We wanted the framework to be portable, so we removed all C++11 feature usages.

Version: 1.x (October 2013)


### Ginseng by @apples

> Ginseng is an entity-component-system (ECS) library designed for use in games.
> 
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.
> 
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.x (Mai 2018)





## Benchmark-Framework: [benchpress](https://github.com/sbs-ableton/benchpress)

> Why benchpress?
> 
> The modern developer is faced with a rich variety of language alternatives to C++; however, C++ is still the choice of professionals facing demanding performance requirements. Despite this fact, there are few (if any) popular performance benchmarking frameworks.
> 
> Benchpress is inspired by Catch and by Golang's benchmark functionality.

It's simple, light and header-only.

Version: 1.x (Juni 2015)


I fork [benchpress](https://github.com/abeimler/benchpress) (add some utils and helper) to plot data for gnuplot.



## <a name="build"></a> Build

### CMake

I used CMake 3.9.3 for the build.
Minimum is 3.2.

 1. change directory to this Folder
 2. `mkdir ./build`
 3. `cmake -H. -B./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DANAX_DEFAULT_ENTITY_POOL_SIZE:STRING="2097152" -DENTITYX_BUILD_SHARED:BOOL="0" -DBUILD_SHARED_LIBS:BOOL="0" -DBUILD_TESTING:BOOL="0" -DENTITYX_BUILD_TESTING:BOOL="0" -DBUILD_TESTING:BOOL="0" -DBUILD_SHARED_LIBS:BOOL="0" -DENTITYX_BUILD_SHARED:BOOL="0" -DINSTALL_HEADERS:BOOL="0" -DINSTALL_GMOCK:BOOL="0" -DBUILD_GMOCK:BOOL="0" -DENTITYX_BUILD_TESTING:BOOL="0" -DINSTALL_GTEST:BOOL="0"`
 4. `cmake --build ./build --target ecs_benchmark`


#### C++ Compiler

 - modern C++14 Standard (`-std=c++14`)
 - Default CMake Release Flags (`-O3 -DNDEBUG`)
 - some Compiler Warnings (`-Wall -Wextra -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -pedantic`)
 - Threading (not used, yet?) (`-pthread`)


I used g++ 7.2.0, clang++ 3.8 should work, too.


#### Linked Libraries

 - entityx (1.x)
 - anax
 - ArtemisCpp

benchpress, entityx (compile-time), entt and ginseng are header-only.


#### CMake Configure

| Variable                        | Value    |
|---------------------------------|----------|
| ANAX_32_BIT_ENTITY_IDS          | OFF      |
| ANAX_DEFAULT_ENTITY_POOL_SIZE   | 2097152  |
| ANAX_MAX_AMOUNT_OF_COMPONENTS   | 64       |
| ANAX_USE_VARIADIC_TEMPLATES     | ON       |
| ANAX_VIRTUAL_DTORS_IN_COMPONENT | ON       |
| ENTITYX_DT_TYPE                 | double   |
| ENTITYX_MAX_COMPONENTS          | 64       |

 - Test and Examples are not build (`-DENTITYX_BUILD_TESTING:BOOL="0" -DBUILD_TESTING:BOOL="0"`)
 - Linked Libraries are static builds (`-DENTITYX_BUILD_SHARED:BOOL="0" -DBUILD_SHARED_LIBS:BOOL="0"`)

_EntityX2 has a Column Storage Capacity (`ColumnStorage<Components, INITIAL_CAPACITY>`) of `16777216`, to avoid `bad_alloc`-Errors_




## Benchmark

Date: Do 16. Aug 16:02:03 CEST 2018

### Environment

 - OS: 4.14.60-1-MANJARO x86_64 GNU/Linux
 - CPU: Intel(R) Core(TM) i7-3770K CPU @ 3.50GHz
 - RAM: 16G

### Results

#### Create, Destroying and Iterating over 10M entities

Benchmark                                              |  EntityX (master)  |  EntityX (experimental/compile_time)  |  EnTT    |  Ginseng
-------------------------------------------------------|--------------------|---------------------------------------|----------|---------
Creating 10M entities                                  |  0.126s            |  0.067s                               |  0.028s  |  0.047s
Destroying 10M entities                                |  0.282s            |  0.068s                               |  0.045s  |  1.997s
Iterating over 10M entities, unpacking one component   |  0.138s            |  0.011s                               |  0.009s  |  0.008s
Iterating over 10M entities, unpacking two components  |  0.299s            |  0.017s                               |  0.030s  |  N/A

_I didn't benchmark Anax and Artemis, because it causes some `bad_alloc`-Errors._


#### Systems update

![benchmark results systems update 1](https://raw.githubusercontent.com/abeimler/ecs_benchmark/master/doc/systems-update-result.png "Benchmark Results: Systems update #1")

![benchmark results systems update 2](https://raw.githubusercontent.com/abeimler/ecs_benchmark/master/doc/systems-update-result-2.png "Benchmark Results: Systems update #2")

_(lower is better :)_

Benchmark                           |  Anax    |  EntityX (master)  |  EntityX (experimental/compile_time)  |  EnTT    |  Ginseng
------------------------------------|----------|--------------------|---------------------------------------|----------|---------
Update  1M entities with 2 Systems  |  0.067s  |  0.059s            |  0.016s                               |  0.007s  |  0.007s
Update  2M entities with 2 Systems  |  0.223s  |  0.122s            |  0.032s                               |  0.013s  |  0.013s
Update  5M entities with 2 Systems  |  0.328s  |  0.082s            |  0.032s                               |  0.034s  |  N/A
Update 10M entities with 2 Systems  |  1.019s  |  0.171s            |  0.065s                               |  0.069s  |  N/A
Update 20M entities with 2 Systems  |  2.078s  |  0.368s            |  0.145s                               |  0.140s  |  N/A


#### Eventbus

![benchmark results eventbus](https://raw.githubusercontent.com/abeimler/ecs_benchmark/master/doc/eventbus-result.png "Benchmark Results: Eventbus")

Some bonus with EntityX (1.x) and [eventpp](https://github.com/skypjack/eventpp).

Benchmark                             |  entityx  |  eventpp
--------------------------------------|-----------|---------
publish EventA and EventB  20k times  |  0.001s   |  0.001s
publish EventA and EventB  50k times  |  0.002s   |  0.002s
publish EventA and EventB 100k times  |  0.004s   |  0.005s
publish EventA and EventB 200k times  |  0.007s   |  0.010s
publish EventA and EventB 500k times  |  0.018s   |  0.024s

_Listen to EventA EventB and EventC_




## Make your own Results

### before run benchmark

After you implemente the Benchmarks you need to config the python script.

_scripts/run_benchmark/config.json_
```js
{
    "updates": [
        "entityx1",
        "entityx2",
        "entt",
        "anax",
        "ginseng"
    ],
    "plotupdates": [
        "entityx1",
        "entityx2",
        "entt",
        "anax",
        "ginseng"
    ],
    "plotupdates2": [
        "entityx1",
        "entityx2",
        "entt",
        "anax",
        "ginseng",
        "artemis"
    ],
    "eventbus": [
        "entityx",
        "eventpp"
    ],
    "10Mentities": [
        "entityx1",
        "entityx2",
        "entt",
        "ginseng"
    ]
}
```

Depend on what you implemented and want, you must add your `frameworkname` to the list.

 * **updates**: just run benchmark for "Update Systems" without plot
 * **plotupdates**: run benchmark for "Update Systems" with plot
 * **plotupdates2**: run benchmark for "Update Systems" with plot (alternative)
 * **eventbus**: run benchmark for "Eventbus" with plot
 * **10Mentities**: run benchmark for "Creating, Destroying, ... 10M entities" with plot

_I use `plotupdates2` as alternative to exclude artemis from the "normal" benchmark, with artemis it takes a bit longer to benchmark_ 

Beware if you are implementing the Benchmarks, you must name the benchmarks right ...  
```
[1] frameworkname Creating 10M entities
[2] frameworkname Destroying 10M entities
[3] frameworkname Iterating over 10M entities, unpacking one component
[4] frameworkname Iterating over 10M entities, unpacking two components


[10] frameworkname entities component systems update
[25] frameworkname entities component systems update
[50] frameworkname entities component systems update
...


[10] frameworkname-eventbus listen to EventA EventB and EventC publish EventA and EventB
[25] frameworkname-eventbus listen to EventA EventB and EventC publish EventA and EventB
...

```
see other framework benchmark runner as example




_scripts/run_benchmark/config.json_
```js
{
    "benchmark": true,
    "runbenchmark_update2": false,
    "gencsvfiles": true,
    "plot": true,
    "genreadme": true
}
```

 * **benchmark**: just run benchmarks for "Update Systems" without plot
 * **runbenchmark_update2**: run benchmarks for "Update Systems" from 'plotupdates2'
 * **gencsvfiles**: generate .csv-files (needed for plot and readme)
 * **plot**: generate (gnuplot) .plt-scripts and plot graphs from .csv-files
 * **genreadme**: generate README.md with new results (tables from .csv-files)


### run benchmark

 1. Build this Project, see [Build](#build)
 2. run `python3 ./scripts/run_benchmark > ./doc/output.txt 2>&1` to print all kind of stuff - _Note: artemis is disabled, it takes to long, but you can uncomment it_
	2.1. OR just run the direct benchmark with plotdata,
		`./build/ecs_benchmark --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*" --bench ".*entt.*update.*" --plotdata > ./doc/data.dat`
		Now you got the `data.dat`
 	2.2. use `gnuplot` and the [gnuplot-script](scripts/data-systems-update.plt) to print the plot, _or use this site [http://gnuplot.respawned.com/]()_


### edit gnuplot (data-systems-update.plt) DEPRECATED

**you don't need to edit the .plt-file, the python script generate one**

```gnuplot
## 1:1 are Headers
plot  "data.dat" using 1:2 title 'EntityX1' with lines, \  # 1. Col
	"data.dat" using 1:3 title 'EntityX2' with lines, \    # 2. Col
	"data.dat" using 1:4 title 'EnTT' with lines           # 3. Col
```

You can edit the `gnuplot`-script to add new cols.










## What to Benchmark

Benchmarks:

 - creating, destroy and unpacking Entities
 - Systems update


### Setup

#### 3 Components
 - PositionComponent
	- `float x` 
	- `float y` 
 - DirectionComponent
	- `float x` 
	- `float y` 
 - ComflabulationComponent
	- `float thingy`
	- `int dingy`
	- `bool mingy`
	- `std::string stringy`

#### 2 Systems
 - MovementSystem
```cpp
void update() {
	position.x += direction.x * dt;
	position.y += direction.y * dt;
}
```

 - ComflabSystem
```cpp
void update() {
	comflab.thingy *= 1.000001f;
	comflab.mingy = !comflab.mingy;
	comflab.dingy++;
}
```




### Benchmark: create Entities

Benchmark Code (1 iteration):
```cpp
auto entity = entitymanager.create();

entity.addComponent<PositionComponent>();
entity.addComponent<DirectionComponent>();
entity.addComponent<ComflabulationComponent>();

entity.destroy();
```

### Benchmark: update system

Run the "update system"-benchmark with different number of entities.
 - 25, 50, 100, 200, 400, 800
 - 1600, 3200, 5000
 - 10000, 30000, 100000, 500000
 - 1000000 (1M), 2000000 (2M), 5000000 (5M)
 - 10000000 (10M) and 20000000 (20M) _in some cases, if possible_


Setup Benchmark:
```cpp
// create application/world with systems

// create entities
for (size_t i = 0; i < nentities; i++) {
	auto entity = entitymanager.create();

	entity.addComponent<PositionComponent>();
	entity.addComponent<DirectionComponent>();

	if (i % 2) {
		entity.addComponent<ComflabulationComponent>();
	}
}
```

Benchmark Code (1 iteration):
```cpp
world.update(fakeDeltaTime);
```



## Links

 - [https://github.com/blockchaindev/benchpress/blob/master/docs/getting_started.md]()
 - [https://github.com/miguelmartin75/anax/wiki/Using-the-Library]()


#### Reference:

 - [http://tilemapkit.com/2015/10/entity-component-systems-compared-benchmarked-entityx-anax-artemis/]()
 - [https://github.com/LearnCocos2D/LearnCocos2D/tree/master/EntityComponentSystemsTest]()


##### This file is genrated via python and pystache, you can find the template in [scripts/run_benchmark/README.md.tmpl](scripts/run_benchmark/README.md.tmpl)
 - https://github.com/defunkt/pystache
 - https://github.com/mplewis/csvtomd