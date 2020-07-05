# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems: 
 - [Anax](https://github.com/miguelmartin75/anax)
 - [Artemis](https://github.com/vinova/Artemis-Cpp)
 - [EntityX](https://github.com/alecthomas/entityx)
 - [EntityX (experimental/compile_time)](https://github.com/alecthomas/entityx/tree/experimental/compile_time)
 - [EnTT (legacy)](https://github.com/skypjack/entt/releases/tag/v1.1.0)
 - [EnTT](https://github.com/skypjack/entt)
 - [Ginseng](https://github.com/apples/ginseng)
 - [ECS](https://github.com/redxdev/ECS)

### TL;DR Results

![benchmark results systems update](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/updatelong.png "Benchmark Results: Systems update")  
_(lower is better)_

|                                    |  ECS     |  Anax    |  EnTT    |  Artemis  |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)  |  EnTT (use runtime-view)|
|------------------------------------|----------|----------|----------|-----------|-----------|-----------|---------------------------------------|--------------------|-----------------|-------------------------|
|Update  1M entities with 2 Systems  |  0.084s  |  0.118s  |  0.006s  |  96.160s  |  0.008s   |  0.034s   |  0.019s                               |  0.005s            |  0.007s         |  0.013s                 |
|Update  2M entities with 2 Systems  |  0.166s  |  0.299s  |  0.012s  |  N/A      |  0.016s   |  0.070s   |  0.039s                               |  0.011s            |  0.014s         |  0.028s                 |
|Update  5M entities with 2 Systems  |  0.435s  |  N/A     |  0.031s  |  N/A      |  0.041s   |  0.178s   |  0.097s                               |  0.028s            |  0.037s         |  0.071s                 |
|Update 10M entities with 2 Systems  |  0.863s  |  N/A     |  0.061s  |  N/A      |  0.081s   |  0.361s   |  0.195s                               |  0.059s            |  0.084s         |  0.153s                 |
|Update 20M entities with 2 Systems  |  1.695s  |  N/A     |  0.122s  |  N/A      |  0.166s   |  0.754s   |  0.389s                               |  0.126s            |  0.148s         |  0.297s                 |


## Candidates

### Anax by @miguelmartin75

> anax is an open source C++ entity system designed to be portable, lightweight and easy to use. It is aimed toward Game Development, however it would be possible to use it for other projects.

Version: 2.1.0 (Januar 2017)

### Artemis by @vinova

> A C++ port of Artemis Entity System Framework.
> The port was orignially written by Sidar Talei, in which he used several C++11 features such as deleted function, variadic templates, nullptr, etc… We wanted the framework to be portable, so we removed all C++11 feature usages.

Version: 1.x (October 2013)

### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity 'objects' themselves.

Version: 1.1.2 (Juli 2017)

### EntityX (experimental/compile_time) by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity 'objects' themselves. The Evolve your Hierarchy article provides a solid overview of EC systems and why you should use them.
> EntityX is an EC system that uses C++11 features to provide type-safe component management, event delivery, etc. It was built during the creation of a 2D space shooter.
> This version of EntityX is header-only and utilizes a bunch of template metaprogramming to provide compile-time component access. 

Version: compiler-time branch aka. Version 2.0.0 (?) (August 2017)

### EnTT (legacy) by @skypjack

> EnTT is a header-only, tiny and easy to use Entity-Component System in modern C++.
> ECS is an architectural pattern used mostly in game development.

Version: 1.1.0 (September 2017)

### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++, mainly known for its innovative entity-component-system (ECS) model.

Version: 3.2.0 (October 2019)

### Ginseng by @apples

> Ginseng is an entity-component-system (ECS) library designed for use in games.
> The main advantage over similar libraries is that the component types do not need to be listed or registered. Component types are detected dynamically.
> Any function-like object can be used as a system. The function's parameters are used to determine the required components.

Version: 1.1 (October 2018)

### ECS by @redxdev

> This is a simple C++ header-only type-safe entity component system library. It makes heavy use of C++11 constructs, so make sure you have an up to date compiler. It isn't meant to do absolutely everything, so please feel free to modify it when using. There's a VS2015 solution provided, but it should compile on any standard compiler with C++11 support (C++14 is more ideal, however, as it lets you use auto parameters in lambdas).
> Again, this is meant for quick prototyping or as a starting point for a more advanced ECS toolkit. It works and it works well, but it isn't optimized for speed or anything.

Version: 1.x (May 2019)




## Benchmark-Framework: [benchpress](https://github.com/abeimler/benchpress)

> Why benchpress?
> 
> The modern developer is faced with a rich variety of language alternatives to C++; however, C++ is still the choice of professionals facing demanding performance requirements. Despite this fact, there are few (if any) popular performance benchmarking frameworks.
> 
> Benchpress is inspired by Catch and by Golang's benchmark functionality.

It's simple, light and header-only.

Version: 1.2.2


I fork [benchpress](https://github.com/philipp-classen/benchpress) (add some utils and helper) to plot data for gnuplot.



## <a name="build"></a> Build

### CMake

I used CMake 3.15.4 for the build.
Minimum is 3.14.

 1. change directory to this Folder
 2. `mkdir ./build`
 3. `./deps.sh`
 4. `./configure.sh`
 4. `./build.sh`


#### Dependencies 

I used [Conan](https://conan.io/) and [CMake FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) for all dependencies.

_see [deps.sh](deps.sh) and [CMakeLists.txt](CMakeLists.txt) for more details_


##### Linked Libraries

- Anax
- Artemis
- EntityX

Other Frameworks are header-only.


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

_see [configure.sh](configure.sh) for more details_


## Benchmark Result Details

Date: 17. Nov 2019

### Environment

 - OS: 4.19.81-1-MANJARO x86_64 GNU/Linux
 - CPU: AMD Ryzen 5 1600 Six-Core Processor
 - RAM: 16G

### Results

#### Create, Destroying and Iterating over 10M entities

|                                                       |  ECS     |  EnTT    |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)  |  EnTT (use runtime-view)|
|-------------------------------------------------------|----------|----------|-----------|-----------|---------------------------------------|--------------------|-----------------|-------------------------|
|Creating 10M entities                                  |  0.537s  |  0.082s  |  0.103s   |  0.259s   |  0.145s                               |  N/A               |  0.058s         |  N/A                    |
|Destroying 10M entities                                |  0.223s  |  0.066s  |  1.186s   |  0.333s   |  0.100s                               |  N/A               |  0.080s         |  N/A                    |
|Iterating over 10M entities, unpacking one component   |  0.148s  |  0.023s  |  0.012s   |  0.062s   |  0.028s                               |  N/A               |  0.010s         |  0.000s                 |
|Iterating over 10M entities, unpacking two components  |  N/A     |  0.063s  |  0.030s   |  0.114s   |  0.033s                               |  0.018s            |  0.023s         |  0.000s                 |
|Creating 10M entities at once                          |  N/A     |  0.053s  |  N/A      |  N/A      |  0.071s                               |  N/A               |  N/A            |  N/A                    |
|Destroying 10M entities at once                        |  0.287s  |  N/A     |  N/A      |  N/A      |  0.064s                               |  N/A               |  N/A            |  N/A                    |

_I didn't benchmark Anax and Artemis, because it causes some `bad_alloc`-Errors._


#### Systems update

![benchmark results systems update 1](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/update.png "Benchmark Results: Systems update #1")
_(lower is faster)_

|                                    |  ECS     |  EnTT    |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)  |  EnTT (use runtime-view)|
|------------------------------------|----------|----------|-----------|-----------|---------------------------------------|--------------------|-----------------|-------------------------|
|Update  1M entities with 2 Systems  |  0.077s  |  0.006s  |  0.008s   |  0.036s   |  0.019s                               |  0.005s            |  0.007s         |  0.013s                 |
|Update  2M entities with 2 Systems  |  0.150s  |  0.012s  |  0.015s   |  0.070s   |  0.037s                               |  0.010s            |  0.014s         |  0.027s                 |
|Update  5M entities with 2 Systems  |  0.398s  |  0.029s  |  0.038s   |  0.179s   |  0.093s                               |  0.026s            |  0.037s         |  0.072s                 |
|Update 10M entities with 2 Systems  |  0.793s  |  0.059s  |  0.078s   |  0.352s   |  0.185s                               |  0.055s            |  0.076s         |  0.143s                 |
|Update 20M entities with 2 Systems  |  1.699s  |  0.117s  |  0.160s   |  0.743s   |  0.367s                               |  0.121s            |  0.153s         |  0.289s                 |

![benchmark results systems update 2](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/updatelong.png "Benchmark Results: Systems update #2")  
_(lower is faster)_

|                                    |  ECS     |  Anax    |  EnTT    |  Artemis  |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)  |  EnTT (use runtime-view)|
|------------------------------------|----------|----------|----------|-----------|-----------|-----------|---------------------------------------|--------------------|-----------------|-------------------------|
|Update  1M entities with 2 Systems  |  0.084s  |  0.118s  |  0.006s  |  96.160s  |  0.008s   |  0.034s   |  0.019s                               |  0.005s            |  0.007s         |  0.013s                 |
|Update  2M entities with 2 Systems  |  0.166s  |  0.299s  |  0.012s  |  N/A      |  0.016s   |  0.070s   |  0.039s                               |  0.011s            |  0.014s         |  0.028s                 |
|Update  5M entities with 2 Systems  |  0.435s  |  N/A     |  0.031s  |  N/A      |  0.041s   |  0.178s   |  0.097s                               |  0.028s            |  0.037s         |  0.071s                 |
|Update 10M entities with 2 Systems  |  0.863s  |  N/A     |  0.061s  |  N/A      |  0.081s   |  0.361s   |  0.195s                               |  0.059s            |  0.084s         |  0.153s                 |
|Update 20M entities with 2 Systems  |  1.695s  |  N/A     |  0.122s  |  N/A      |  0.166s   |  0.754s   |  0.389s                               |  0.126s            |  0.148s         |  0.297s                 |

![benchmark results systems update 3](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/updatemorecomplex.png "Benchmark Results: Systems update #3")  
_(lower is faster)_

|                                    |  ECS     |  EnTT    |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)  |  EnTT (use runtime-view)|
|------------------------------------|----------|----------|-----------|-----------|---------------------------------------|--------------------|-----------------|-------------------------|
|Update  1M entities with 2 Systems  |  0.076s  |  0.006s  |  0.008s   |  0.034s   |  0.020s                               |  0.005s            |  0.006s         |  0.013s                 |
|Update  2M entities with 2 Systems  |  0.151s  |  0.013s  |  0.017s   |  0.069s   |  0.039s                               |  0.011s            |  0.014s         |  0.027s                 |
|Update  5M entities with 2 Systems  |  0.404s  |  0.030s  |  0.039s   |  0.188s   |  0.101s                               |  0.028s            |  0.036s         |  0.072s                 |
|Update 10M entities with 2 Systems  |  0.787s  |  0.063s  |  0.080s   |  0.366s   |  0.194s                               |  0.059s            |  0.076s         |  0.155s                 |
|Update 20M entities with 2 Systems  |  1.527s  |  0.125s  |  0.156s   |  0.749s   |  0.390s                               |  0.130s            |  0.155s         |  0.286s                 |



#### Eventbus

![benchmark results eventbus](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/eventbus.png "Benchmark Results: Eventbus")

|                                              |  ECS     |  EntityX  |  EnTT (legacy)|
|----------------------------------------------|----------|-----------|---------------|
|publish EventA, EventB and EventC  20k times  |  0.000s  |  0.001s   |  0.002s       |
|publish EventA, EventB and EventC  50k times  |  0.001s  |  0.002s   |  0.004s       |
|publish EventA, EventB and EventC 100k times  |  0.001s  |  0.005s   |  0.008s       |
|publish EventA, EventB and EventC 200k times  |  0.002s  |  0.008s   |  0.016s       |
|publish EventA, EventB and EventC 500k times  |  0.006s  |  0.024s   |  0.039s       |

_Listen to EventA EventB and EventC_




## Make your own Results

### before run benchmark

After you implemente the Benchmarks you need to config the python script.  
_you need [pystache](https://github.com/defunkt/pystache) to run the python script: `pip install pystache`_


_scripts/run_benchmark/config.json_
```js
{
    "update": [
        "entityx1",
        "entityx2",
        "entt",
        "ginseng",
        "yourframeworkname"
    ],
    "updatelong": [
        "anax",
        "artemis",
        "entityx1",
        "entityx2",
        "entt",
        "ginseng",
        "yourframeworkname"
    ],
    "eventbus": [
        "entityx",
        "eventpp"
    ],
    "10Mentities": [
        "entityx1",
        "entityx2",
        "entt",
        "ginseng",
        "yourframeworkname"
    ],

    "info": {
        "yourframeworkname": {
            "name": "MyFramework",
            "author": "@me",
            "description": "This is a descroption.\nMy framework is awesome :)",
            "version": "1.1.0",
            "link": "https://github.com/abeimler/myframework",
            "framework": true,
            "linkedlib": false
        },
    }
}
```

Put you Framework information into `info` with this keys:
 - **name**: Displayname of you Framework (csv, README, ...)
 - **author**: Author 
 - **description**: description for Candidates-list in README
 - **version**: Version used in this benchmark
 - **link**: Link to your Framework (Website, github, ...)
 - **framework**: `true` when this a framework for benchmark
 - **linkedlib**: `true` when this framework need to be linked (only used README)


Depend on what you implemented, you must add your `yourframeworkname` to the list.

 * **updates**: just run benchmark for "Update Systems" without plot
 * **plotupdates**: run benchmark for "Update Systems" with plot
 * **updatelong**: run benchmark for "Update Systems" with plot (alternative)
 * **eventbus**: run benchmark for "Eventbus" with plot
 * **10Mentities**: run benchmark for "Creating, Destroying, ... 10M entities" with plot

_I use `updatelong` as alternative to include artemis from the "normal" benchmark, with artemis it takes a bit longer to benchmark_ 

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
    "simplebenchmark": false,
    "benchmark": true,
    "runbenchmarkupdatelong": false,
    "gencsvfiles": true,
    "plot": true,
    "genreadme": true
}
```

 * **simplebenchmark**: just run benchmarks for "Update Systems" without plot
 * **benchmark**: run benchmarks for "Update Systems" with plot (plot) and generate .csv-files (gencsvfiles)
 * **runbenchmarkupdatelong**: run benchmarks for "Update Systems" for 'updateslong'-frameworks (see config.js)
 * **gencsvfiles**: generate .csv-files (needed for plot and readme)
 * **plot**: generate (gnuplot) .plt-scripts and plot graphs from .csv-files
 * **genreadme**: generate README.md with new results (from .csv-files)


### run benchmark

 1. Build this Project, see [Build](#build)
 2. run `python3 ./scripts/run_benchmark` to print all kind of stuff - _Note: artemis is disabled, it takes to long, but you can uncomment it_
	2.1. OR just run the direct benchmark with plotdata,
		`./build/ecs_benchmark --bench ".*entityx1.*update.*" --bench ".*entityx2.*update.*" --bench ".*entt.*update.*" --plotdata > ./doc/data.dat`
		Now you got the `data.dat`
 	2.2. use `gnuplot` and the [gnuplot-script](scripts/update.plt) to print the plot, _or use this site [http://gnuplot.respawned.com/]()_
 3. see generated README for results or CSVs or Graphs




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

	if (i % 2 != 0) {
		entity.addComponent<ComflabulationComponent>();
	}
}
```

Benchmark Code (1 iteration):
```cpp
world.update(fakeDeltaTime);
```


### Examples

see other Benchmarks for Example...
Put your Framework-Code to benchmark into `src/frameworkname` and the benchpress-Runner into `app/frameworkname`

_src/entt/EnttBenchmark.h_
```cpp
class EnttBenchmark {
    public:

    struct PositionComponent {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct DirectionComponent {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct ComflabulationComponent {
        float thingy = 0.0;
        int dingy = 0;
        bool mingy = false;
        std::string stringy;
    };

    // setup EntityManager

    class System {
        public:
        // virtual dtor and the rule of 6
        System() = default;
        virtual ~System() = default;
        System(const System&) = default;
        System& operator=(const System&) = default;
        System(System&&) = default;
        System& operator=(System&&) = default;

        virtual void update(EntityManager& es, TimeDelta dt) = 0;
    };


    class MovementSystem : public System {
        public:
        MovementSystem() = default;

        void update(EntityManager& registry, TimeDelta dt) override {
            // iterate movement components and do stuff
        }
    };

    class ComflabSystem : public System {
        public:
        ComflabSystem() = default;

        void update(EntityManager& registry, TimeDelta dt) override {
            // iterate comflab components and do stuff
        }
    };


    class Application {
        public:
        Application() {
            // setup systems
        }

        void update(TimeDelta dt) {
            // update systems
        }

        EntityManager& getEntityManager() { return this->entities_; }
        const EntityManager& getEntityManager() const { return this->entities_; }

        private:
        EntityManager entities_;
        std::vector<std::unique_ptr<System>> systems_;
    };

    static constexpr TimeDelta fakeDeltaTime = 1.0 / 60;
};
```

_src/entt/EnttBenchmark.cpp_
```cpp
#include "EnttBenchmark.h"
```



_app/entt/enttBenchmarkRunner.cpp_
```cpp

// benchmark for create/destory 10M entities ...


inline void init_entities(EnttBenchmark::EntityManager& registry, size_t nentities){
    for (size_t i = 0; i < nentities; i++) {
        // create entiries
    }
}

inline void runEntitiesSystemsEnttBenchmark(benchpress::context* ctx, size_t nentities) {
    EnttBenchmark::Application app;
    auto& registry = app.getEntityManager();

    init_entities(registry, nentities);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EnttBenchmark::fakeDeltaTime);
    }
}



class BenchmarksEntt {
    public:
    static const std::vector<int> ENTITIES;

    static inline void makeBenchmarks(const std::string& name) {
        makeBenchmarks(name, ENTITIES);
    }

    static void makeBenchmarks(const std::string& name, const std::vector<int>& entities) {
        for(int nentities : entities) {
            std::string tag = fmt::format("[{}]", nentities);
            std::string benchmark_name = fmt::format("{:>12}{:<10}{:>12} entities component systems update", tag, name, nentities);
            
            BENCHMARK(benchmark_name, [nentities](benchpress::context* ctx) {
                runEntitiesSystemsEnttBenchmark(ctx, nentities);
            })
        }
    }

    BenchmarksEntt(const std::string& name){
        makeBenchmarks(name);
    }
};
const std::vector<int> BenchmarksEntt::ENTITIES = {
    10, 25, 50,
    100, 200, 400, 800,
    1600, 3200, 5000,
    10'000, 30'000,
    100'000, 500'000,
    1'000'000, 2'000'000, 5'000'000,
    10'000'000, 20'000'000
};

BenchmarksEntt enttbenchmarks("entt");

```


## Links

 - https://github.com/blockchaindev/benchpress/blob/master/docs/getting_started.md
 - https://github.com/miguelmartin75/anax/wiki/Using-the-Library


#### Reference:

 - https://github.com/LearnCocos2D/LearnCocos2D/tree/master/EntityComponentSystemsTest


##### This file is genrated via python and pystache, you can find the template in [scripts/run_benchmark/README.md.mustache](scripts/run_benchmark/README.md.mustache)
 - https://github.com/defunkt/pystache
 - https://github.com/mplewis/csvtomd
