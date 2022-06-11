find_package(benchmark REQUIRED)

add_subdirectory(benchmarks)

# NOTE: add sub project for benchmarks here
if (ENABLE_BENCHMARK_ENTT)
add_subdirectory(benchmarks/entt)
add_subdirectory(benchmarks/entt-more)
endif()

if (ENABLE_BENCHMARK_ENTITYX)
add_subdirectory(benchmarks/entityx)
add_subdirectory(benchmarks/entityx-more)
endif()

if (ENABLE_BENCHMARK_GINSENG)
add_subdirectory(benchmarks/ginseng)
add_subdirectory(benchmarks/ginseng-more)
endif()

if (ENABLE_BENCHMARK_MUSTACHE)
add_subdirectory(benchmarks/mustache)
add_subdirectory(benchmarks/mustache-more)
endif()

if (ENABLE_BENCHMARK_OPENECS)
add_subdirectory(benchmarks/openecs)
add_subdirectory(benchmarks/openecs-more)
endif()

if (ENABLE_BENCHMARK_FLECS)
add_subdirectory(benchmarks/flecs)
add_subdirectory(benchmarks/flecs-more)
endif()

if (ENABLE_BENCHMARK_ENTITYPLUS)
    add_subdirectory(benchmarks/entityplus)
    add_subdirectory(benchmarks/entityplus-more)
endif()

if (ENABLE_BENCHMARK_OOP)
add_subdirectory(benchmarks/oop)
endif()