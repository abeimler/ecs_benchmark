find_package(benchmark REQUIRED)

add_subdirectory(benchmarks)

# NOTE: add sub project for benchmaarks here
add_subdirectory(benchmarks/entt)
add_subdirectory(benchmarks/entt-more)
add_subdirectory(benchmarks/entityx)