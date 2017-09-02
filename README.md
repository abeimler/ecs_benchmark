# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems: 
[EnTT](https://github.com/skypjack/entt) vs. [entityx](https://github.com/alecthomas/entityx) vs. [anax](https://github.com/miguelmartin75/anax) vs. [Artemis-Cpp](https://github.com/vinova/Artemis-Cpp)

## Candidates

### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use entity-component system in modern C++.
> ECS is an architectural pattern used mostly in game development.
> I started using another well known Entity Component System named entityx.
> 
> While I was playing with it, I found that I didn't like that much the way it manages its memory. Moreover, I was pretty sure that one > could achieve better performance with a slightly modified pool under the hood.
> That's also the reason for which the interface is quite similar to the one of entityx, so that EnTT can be used as a drop-in > replacement for it with a minimal effort.

Version: 1.0.0 (2017)


### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. 
> The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.
> 
> EntityX is an EC system that uses C++11 features to provide type-safe component management, event delivery, etc. 
> It was built during the creation of a 2D space shooter.

Version: 1.x (2017) and the [`compiler-time`](https://github.com/alecthomas/entityx/tree/experimental/compile_time) Version 2.0 (?) (2017)


### anax by @miguelmartin75

> anax is an open source C++ entity system designed to be portable, lightweight and easy to use. 
> It is aimed toward Game Development, however it would be possible to use it for other projects.

Version: 1.x (2017)


### Artemis C++ by @vinova

> A C++ port of Artemis Entity System Framework.
> 
> The port was orignially written by Sidar Talei, in which he used several C++11 features such as deleted function, variadic templates, nullptr, etc… We wanted the framework to be portable, so we removed all C++11 feature usages.

Version: 1.x (2013)





## Benchmark-Framework: [benchpress](https://github.com/sbs-ableton/benchpress)

> Why benchpress?
> 
> The modern developer is faced with a rich variety of language alternatives to C++; however, C++ is still the choice of professionals facing demanding performance requirements. Despite this fact, there are few (if any) popular performance benchmarking frameworks.
> 
> Benchpress is inspired by Catch and by Golang's benchmark functionality.

It's simple, light and header-only.

Version: 1.x (2014)


I fork [benchpress](https://github.com/abeimler/benchpress) (add some utils and helper) to plot data for gnuplot.



## <a name="build"></a> Build

### CMake

I used CMake 3.2 for the build.

 1. change directory to this Folder
 2. `mkdir ./build`
 3. `cmake -H. -B./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DANAX_DEFAULT_ENTITY_POOL_SIZE:STRING="2097152" -DENTITYX_BUILD_SHARED:BOOL="0" -DBUILD_SHARED_LIBS:BOOL="0" -DBUILD_TESTING:BOOL="0" -DENTITYX_BUILD_TESTING:BOOL="0" -DBUILD_TESTING:BOOL="0" -DBUILD_SHARED_LIBS:BOOL="0" -DENTITYX_BUILD_SHARED:BOOL="0" -DINSTALL_HEADERS:BOOL="0" -DINSTALL_GMOCK:BOOL="0" -DBUILD_GMOCK:BOOL="0" -DENTITYX_BUILD_TESTING:BOOL="0" -DINSTALL_GTEST:BOOL="0"`
 4. `cmake --build ./build --target ecs_benchmark`


### C++ Compiler

 - modern C++14 Standard (`-std=c++14`)
 - Default CMake Release Flags (`-O3 -DNDEBUG`)
 - some Compiler Warnings (`-Wall -Wextra -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -pedantic`)
 - Threading (not used, yet?) (`-pthread`)


I used g++ 6.4.0, clang++ 3.8 should work, too.


#### Linked Libraries

 - entityx (1.x)
 - anax
 - ArtemisCpp

benchpress, entityx (compile-time) and entt are header-only.


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
 - 10000000 (10M) _in some cases, if possible_


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




## Benchmark

### Environment

 - OS: Antergos Linux (4.10.4-1-ARCH) 64-Bit
 - CPU: 4x Intel® Core™ i5 CPU 760 @ 2.80GHz
 - RAM: 8 GB

### Results

#### Create, Destroying and Iterating over 10M entities

| Benchmark                                             | EntityX (master) | EntityX (experimental/compile_time) | EnTT (master) |
|:------------------------------------------------------|-----------------:|------------------------------------:|--------------:|
| Creating 10M entities                                 |            0.21s |                               0.12s |     **0.04s** |
| Destroying 10M entities                               |            0.42s |                               0.16s |     **0.09s** |
| Iterating over 10M entities, unpacking one component  |            0.22s |                               0.06s |     **0.01s** |
| Iterating over 10M entities, unpacking two components |            0.35s |                               0.08s |     **0.06s** |

_I didn't benchmark Anax and Artemis, because it causes some `bad_alloc`-Errors._


#### Systems update

![benchmark results systems update 1](https://raw.githubusercontent.com/abeimler/ecs_benchmark/master/doc/systems-update-result.png "Benchmark Results: Systems update #1")

![benchmark results systems update 2](https://raw.githubusercontent.com/abeimler/ecs_benchmark/master/doc/systems-update-result-2.png "Benchmark Results: Systems update #2")

_(lower is better :)_

| Benchmark                          | Artemis |  Anax | EntityX (master) | EntityX (experimental/compile_time) | EnTT (master) |
|:-----------------------------------|--------:|------:|-----------------:|------------------------------------:|--------------:|
| Update  1M entities with 2 Systems | 195.88s | 0.21s |            0.09s |                               0.02s |     **0.01s** |
| Update  2M entities with 2 Systems |     N/A | 1.06s |            0.21s |                               0.04s |     **0.03s** |
| Update 10M entities with 2 Systems |     N/A |   N/A |            0.52s |                               0.11s |     **0.07s** |
| Update 20M entities with 2 Systems |     N/A |   N/A |            1.70s |                               0.23s |     **0.13s** |


#### Eventbus

![benchmark results eventbus](https://raw.githubusercontent.com/abeimler/ecs_benchmark/master/doc/eventbus-result.png "Benchmark Results: Eventbus")

Some bonus with EntityX (1.x) and [eventpp](https://github.com/skypjack/eventpp).

| Benchmark                                             | EntityX (master) |   Eventpp |
|:------------------------------------------------------|-----------------:|----------:|
| publish EventA and EventB  20k times                  |              1ms |       1ms |
| publish EventA and EventB  50k times                  |              3ms |       3ms |
| publish EventA and EventB 100k times                  |          **6ms** |       7ms |
| publish EventA and EventB 200k times                  |         **12ms** |      15ms |
| publish EventA and EventB 500k times                  |         **30ms** |      37ms |

_Listen to EventA EventB and EventC_



## Make your own Results

 1. Build this Project, see [Build](#build)
 2. Goto the `scripts/`-folder
 	1. run `./run_benchmark.sh` to print all kind of stuff- _Note: artemis is disabled, it takes to long, but you can uncomment it_
 3. OR just run the direct benchmark with plotdata,
    `../build/ecs_benchmark --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*" --bench ".*entt.*update.*" --plotdata > data.dat`
	Now you got the `data.dat`
 4. `gnuplot` and the [gnuplot-script](scripts/data-systems-update.plt) to print plot, _or use this site [http://gnuplot.respawned.com/]()_


### edit gnuplot (data-systems-update.plt)

```gnuplot
## 1:1 are Headers
plot  "data.dat" using 1:2 title 'EntityX1' with lines, \  # 1. Col
	"data.dat" using 1:3 title 'EntityX2' with lines, \    # 2. Col
	"data.dat" using 1:4 title 'EnTT' with lines           # 3. Col
```

You can edit the `gnuplot`-script to add new cols.






## Links

 - [https://github.com/blockchaindev/benchpress/blob/master/docs/getting_started.md]()
 - [https://github.com/miguelmartin75/anax/wiki/Using-the-Library]()


#### Reference:

 - [http://tilemapkit.com/2015/10/entity-component-systems-compared-benchmarked-entityx-anax-artemis/]()
 - [https://github.com/LearnCocos2D/LearnCocos2D/tree/master/EntityComponentSystemsTest]()
