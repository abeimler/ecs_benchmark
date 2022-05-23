find_package(benchmark REQUIRED)

add_subdirectory(benchmarks)

# NOTE: add sub project for benchmarks here
add_subdirectory(benchmarks/entt)
add_subdirectory(benchmarks/entt-more)
add_subdirectory(benchmarks/entityx)
add_subdirectory(benchmarks/entityx-more)
add_subdirectory(benchmarks/ginseng)
add_subdirectory(benchmarks/ginseng-more)