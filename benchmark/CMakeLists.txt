find_package(benchmark REQUIRED)

add_subdirectory(benchmarks)

# NOTE: add sub project for benchmarks here
if(ENABLE_BENCHMARK_ENTT)
  add_subdirectory(benchmarks/entt-entities)
  add_subdirectory(benchmarks/entt)
  add_subdirectory(benchmarks/entt-extended)
endif()

if(ENABLE_BENCHMARK_ENTITYX)
  add_subdirectory(benchmarks/entityx-entities)
  add_subdirectory(benchmarks/entityx)
  add_subdirectory(benchmarks/entityx-extended)
endif()

if(ENABLE_BENCHMARK_GINSENG)
  add_subdirectory(benchmarks/ginseng-entities)
  add_subdirectory(benchmarks/ginseng)
  add_subdirectory(benchmarks/ginseng-extended)
endif()

if(ENABLE_BENCHMARK_MUSTACHE)
  add_subdirectory(benchmarks/mustache-entities)
  add_subdirectory(benchmarks/mustache)
  add_subdirectory(benchmarks/mustache-extended)
endif()

if(ENABLE_BENCHMARK_OPENECS)
  add_subdirectory(benchmarks/openecs-entities)
  add_subdirectory(benchmarks/openecs)
  add_subdirectory(benchmarks/openecs-extended)
endif()

if(ENABLE_BENCHMARK_FLECS)
  add_subdirectory(benchmarks/flecs-entities)
  add_subdirectory(benchmarks/flecs)
  add_subdirectory(benchmarks/flecs-extended)
endif()

if(ENABLE_BENCHMARK_PICO_ECS)
  add_subdirectory(benchmarks/pico-ecs-entities)
  add_subdirectory(benchmarks/pico-ecs)
  add_subdirectory(benchmarks/pico-ecs-extended)
endif()

if(ENABLE_BENCHMARK_GAIA_ECS)
  add_subdirectory(benchmarks/gaia-ecs-entities)
  add_subdirectory(benchmarks/gaia-ecs)
  add_subdirectory(benchmarks/gaia-ecs-extended)
endif()

if(ENABLE_BENCHMARK_OOP)
  add_subdirectory(benchmarks/oop)
endif()
