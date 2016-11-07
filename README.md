# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems: 
[entityx](https://github.com/alecthomas/entityx) vs. [anax](https://github.com/miguelmartin75/anax) vs. [Artemis-Cpp](https://github.com/vinova/Artemis-Cpp)

## Candidates

### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity "objects" themselves. 
> The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.
> 
> EntityX is an EC system that uses C++11 features to provide type-safe component management, event delivery, etc. 
> It was built during the creation of a 2D space shooter.

Version: 1.x and the [`compiler-time`](https://github.com/alecthomas/entityx/tree/experimental/compile_time) Version (2.0 ?)


### anax by @miguelmartin75

> anax is an open source C++ entity system designed to be portable, lightweight and easy to use. 
> It is aimed toward Game Development, however it would be possible to use it for other projects.

Version: 1.x


### Artemis C++ by @vinova

> A C++ port of Artemis Entity System Framework.
> 
> The port was orignially written by Sidar Talei, in which he used several C++11 features such as deleted function, variadic templates, nullptr, etc… We wanted the framework to be portable, so we removed all C++11 feature usages.

Version: 1.x (2012)





## Benchmark-Framework: [benchpress](https://github.com/blockchaindev/benchpress)

> Why benchpress?
> 
> The modern developer is faced with a rich variety of language alternatives to C++; however, C++ is still the choice of professionals facing demanding performance requirements. Despite this fact, there are few (if any) popular performance benchmarking frameworks.
> 
> Benchpress is inspired by Catch and by Golang's benchmark functionality.

It's simple, light and header-only.

Version: 1.x (2014)






## Compiling

### CMake

I used CMake 3.2 for the build.

 1. change directory to this Folder
 2. `mkdir ./build`
 3. ``cmake -H. -B./build -C./build/CMakeTools/InitializeCache.cmake -DCMAKE_BUILD_TYPE=Release``
 4. `cd ./build`
 5. `make ecs_benchmark`


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

benchpress and entityx (compile-time) are header-only.


#### CMake Configure

| Variable                        | Value   |
|---------------------------------|---------|
| ANAX_32_BIT_ENTITY_IDS          | OFF     |
| ANAX_DEFAULT_ENTITY_POOL_SIZE   | 2097152 |
| ANAX_MAX_AMOUNT_OF_COMPONENTS   | 64      |
| ANAX_USE_VARIADIC_TEMPLATES     | ON      |
| ANAX_VIRTUAL_DTORS_IN_COMPONENT | ON      |
| ENTITYX_DT_TYPE                 | double  |
| ENTITYX_MAX_COMPONENTS          | 64      |

 - Test and Examples are not build
 - Linked Libraries are static builds





## Benchmark

Benchmarks:

 - creating Entities
 - Systems update


### Setup

#### 3 Components
 - PositionComponent
	- `float x,y` 
 - DirectionComponent
	- `float x,y` 
 - ComflabulationComponent
	- `float thingy`
	- `int dingy`
	- `bool mingy`
	- `std::string stringy`

#### 2 Systems
 - MovementSystem
```cpp
		void update(){
			position.x += direction.x * dt;
			position.y += direction.y * dt;
		}
```

 - ComflabSystem
```cpp
		void update(){
			comflab.thingy *= 1.000001f;
			comflab.mingy = !comflab.mingy;
			comflab.dingy++;
		}
```




### benchmark create Entities

Benchmark Code (1 iteration):
```cpp
auto entity = entitymanager.create();

entity.addComponent<PositionComponent>();
entity.addComponent<DirectionComponent>();
entity.addComponent<ComflabulationComponent>();

entity.destroy();
```

### benchmark update system

Run the "update system"-benchmark with different number of entities.
 - 25, 50, 100, 200, 400, 800
 - 1600, 3200, 5000
 - 10000, 30000, 100000, 500000
 - 1000000 (1M), 2000000 (2M)


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

I run the benchmarks with `/usr/bin/time` for more measurement.


### Environment

 - OS: Linux Ubuntu 16.04 LTS 64-Bit Version
 - CPU: Intel® Core™ i7-3770K CPU @ 3.50GHz × 4 
 - RAM: 8 GB



### Run Benchmark

```bash
$ /usr/bin/time ./build/ecs_benchmark --bench entityx.*
$ /usr/bin/time ./build/ecs_benchmark --bench anax.*
$ /usr/bin/time ./build/ecs_benchmark --bench artemis.*
```

#### Result

See [BenchmarkResultDetails]() for detail Details. 


##### Summery


###### create Entity

|                            | EntityX2  | EntityX | Anax | Artemis |
|----------------------------|----------:|--------:|-----:|--------:|
| Time per Operation (ns/op) | **11**    | 158     | 581  | 27560   |



###### update Systems

```bash
## ECS Benchmark
# xlabel 'Entities'
# ylabel 'Time per Operation (ns/op)'
                 
#  Entities   EntityX2    EntityX             Anax        Artemis    
         25        253       1355              407           1850
         50        512       2709              719           3739
        100       1013       5354             1351           7171
        200       2028      10705             2772          15105
        400       4032      21538             5515          30838
        800       8045      42644            12663          57808
       1600      16295      85357            28900         118610
       3200      32925     176464            65675         238977
       5000      52012     267848            98019         370044
      10000     103898     549676           207962         766931
      30000     312005    1716154          1404356        2637299
     100000    1138549    5555625          7378245     1771098554
     500000    6822237   28519338         41724988    43347850038
    1000000   13581160   59526020        114361612   178245581448
    2000000   27446855  126546487        304180312   751284287440
```







### Update Systems Benchmark 

![ECS Benchmark](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/result_summery.png)




## Links

 - https://github.com/blockchaindev/benchpress/blob/master/docs/getting_started.md
 - https://github.com/miguelmartin75/anax/wiki/Using-the-Library

Reference:

http://tilemapkit.com/2015/10/entity-component-systems-compared-benchmarked-entityx-anax-artemis/
https://github.com/LearnCocos2D/LearnCocos2D/tree/master/EntityComponentSystemsTest
