# Entity-Component-Systems Benchmark

Simple Benchmark of common Entity-Component-Systems: 
 - [Anax](https://github.com/miguelmartin75/anax)
 - [Artemis](https://github.com/vinova/Artemis-Cpp)
 - [EntityX](https://github.com/alecthomas/entityx)
 - [EntityX (experimental/compile_time)](https://github.com/alecthomas/entityx/tree/experimental/compile_time)
 - [EnTT (legacy)](https://github.com/skypjack/entt)
 - [EnTT](https://github.com/skypjack/entt)
 - [Ginseng](https://github.com/apples/ginseng)

### TL;DR Results

![benchmark results systems update](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/updatelong.png "Benchmark Results: Systems update")  
_(lower is better)_

|                                    |  Anax    |  EnTT    |  Artemis  |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)|
|------------------------------------|----------|----------|-----------|-----------|-----------|---------------------------------------|--------------------|---------------|
|Update  1M entities with 2 Systems  |  0.130s  |  0.006s  |  94.635s  |  0.007s   |  0.041s   |  0.019s                               |  0.005s            |  0.007s       |
|Update  2M entities with 2 Systems  |  0.290s  |  0.011s  |  N/A      |  0.015s   |  0.085s   |  0.039s                               |  0.011s            |  0.014s       |
|Update  5M entities with 2 Systems  |  N/A     |  0.030s  |  N/A      |  0.039s   |  0.239s   |  0.101s                               |  0.028s            |  0.039s       |
|Update 10M entities with 2 Systems  |  N/A     |  0.061s  |  N/A      |  0.084s   |  0.481s   |  0.221s                               |  0.061s            |  0.091s       |
|Update 20M entities with 2 Systems  |  N/A     |  0.130s  |  N/A      |  0.174s   |  1.383s   |  0.449s                               |  0.136s            |  0.160s       |


## Candidates

### Anax by @miguelmartin75

> anax is an open source C++ entity system designed to be portable, lightweight and easy to use. 

Version: 2.1.0 (Januar 2017)

### Artemis by @vinova

> A C++ port of Artemis Entity System Framework.

Version: 1.x (October 2013)

### EntityX by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity 'objects' themselves.

Version: 1.1.2 (Juli 2017)

### EntityX (experimental/compile_time) by @alecthomas

> Entity Component Systems (ECS) are a form of decomposition that completely decouples entity logic and data from the entity 'objects' themselves.

Version: compiler-time branch aka. Version 2.0.0 (?) (August 2017)

### EnTT (legacy) by @skypjack

> EnTT is a header-only, tiny and easy to use entity-component system in modern C++.

Version: 1.1.0 (September 2017)

### EnTT by @skypjack

> EnTT is a header-only, tiny and easy to use library for game programming and much more written in modern C++, mainly known for its innovative entity-component-system (ECS) model.

Version: 3.2.0 (October 2019)

### Ginseng by @apples

> Ginseng is an entity-component-system (ECS) library designed for use in games.

Version: 1.1 (October 2018)




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

Date: 04. Nov 2019

### Environment

 - OS: 4.19.80-1-MANJARO x86_64 GNU/Linux
 - CPU: AMD Ryzen 5 1600 Six-Core Processor
 - RAM: 16G

### Results

#### Create, Destroying and Iterating over 10M entities

|                                                       |  EnTT    |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)|
|-------------------------------------------------------|----------|-----------|-----------|---------------------------------------|--------------------|---------------|
|Creating 10M entities                                  |  0.085s  |  0.109s   |  0.279s   |  0.160s                               |  N/A               |  0.060s       |
|Destroying 10M entities                                |  0.070s  |  1.715s   |  0.426s   |  0.144s                               |  N/A               |  0.089s       |
|Iterating over 10M entities, unpacking one component   |  0.022s  |  0.012s   |  0.061s   |  0.008s                               |  N/A               |  0.010s       |
|Iterating over 10M entities, unpacking two components  |  0.064s  |  0.032s   |  0.117s   |  N/A                                  |  0.018s            |  0.022s       |
|Creating 10M entities at once                          |  0.055s  |  N/A      |  N/A      |  0.069s                               |  N/A               |  N/A          |

_I didn't benchmark Anax and Artemis, because it causes some `bad_alloc`-Errors._


#### Systems update

![benchmark results systems update 1](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/update.png "Benchmark Results: Systems update #1")
_(lower is faster)_

|                                    |  EnTT    |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)|
|------------------------------------|----------|-----------|-----------|---------------------------------------|--------------------|---------------|
|Update  1M entities with 2 Systems  |  0.006s  |  0.008s   |  0.043s   |  0.020s                               |  0.005s            |  0.007s       |
|Update  2M entities with 2 Systems  |  0.012s  |  0.016s   |  0.086s   |  0.039s                               |  0.011s            |  0.014s       |
|Update  5M entities with 2 Systems  |  0.030s  |  0.040s   |  0.247s   |  0.104s                               |  0.028s            |  0.037s       |
|Update 10M entities with 2 Systems  |  0.061s  |  0.084s   |  0.480s   |  0.215s                               |  0.060s            |  0.089s       |
|Update 20M entities with 2 Systems  |  0.130s  |  0.180s   |  1.409s   |  0.439s                               |  0.134s            |  0.185s       |

![benchmark results systems update 2](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/updatelong.png "Benchmark Results: Systems update #2")  
_(lower is faster)_

|                                    |  Anax    |  EnTT    |  Artemis  |  Ginseng  |  EntityX  |  EntityX (experimental/compile_time)  |  EnTT (use group)  |  EnTT (legacy)|
|------------------------------------|----------|----------|-----------|-----------|-----------|---------------------------------------|--------------------|---------------|
|Update  1M entities with 2 Systems  |  0.130s  |  0.006s  |  94.635s  |  0.007s   |  0.041s   |  0.019s                               |  0.005s            |  0.007s       |
|Update  2M entities with 2 Systems  |  0.290s  |  0.011s  |  N/A      |  0.015s   |  0.085s   |  0.039s                               |  0.011s            |  0.014s       |
|Update  5M entities with 2 Systems  |  N/A     |  0.030s  |  N/A      |  0.039s   |  0.239s   |  0.101s                               |  0.028s            |  0.039s       |
|Update 10M entities with 2 Systems  |  N/A     |  0.061s  |  N/A      |  0.084s   |  0.481s   |  0.221s                               |  0.061s            |  0.091s       |
|Update 20M entities with 2 Systems  |  N/A     |  0.130s  |  N/A      |  0.174s   |  1.383s   |  0.449s                               |  0.136s            |  0.160s       |




#### Eventbus

![benchmark results eventbus](https://raw.githubusercontent.com/abeimler/ecs_benchmark/develop/doc/eventbus.png "Benchmark Results: Eventbus")

|                                      |  EntityX  |  EnTT (legacy)|
|--------------------------------------|-----------|---------------|
|publish EventA and EventB  20k times  |  0.001s   |  0.002s       |
|publish EventA and EventB  50k times  |  0.002s   |  0.004s       |
|publish EventA and EventB 100k times  |  0.004s   |  0.008s       |
|publish EventA and EventB 200k times  |  0.008s   |  0.017s       |
|publish EventA and EventB 500k times  |  0.020s   |  0.042s       |

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

 - [https://github.com/blockchaindev/benchpress/blob/master/docs/getting_started.md]()
 - [https://github.com/miguelmartin75/anax/wiki/Using-the-Library]()


#### Reference:

 - [http://tilemapkit.com/2015/10/entity-component-systems-compared-benchmarked-entityx-anax-artemis/]()
 - [https://github.com/LearnCocos2D/LearnCocos2D/tree/master/EntityComponentSystemsTest]()


##### This file is genrated via python and pystache, you can find the template in [scripts/run_benchmark/README.md.mustache](scripts/run_benchmark/README.md.mustache)
 - https://github.com/defunkt/pystache
 - https://github.com/mplewis/csvtomd