add_subdirectory(base)

# NOTE: add ecs example here
option(ENABLE_BENCHMARK_ENTT "Enable EnTT Benchmarks" ON)
if(ENABLE_BENCHMARK_ENTT)
  add_subdirectory(entt)
endif()

option(ENABLE_BENCHMARK_ENTITYX "Enable EntityX Benchmarks" ON)
if(ENABLE_BENCHMARK_ENTITYX)
  add_subdirectory(entityx)
endif()

option(ENABLE_BENCHMARK_GINSENG "Enable Ginseng Benchmarks" ON)
if(ENABLE_BENCHMARK_GINSENG)
  add_subdirectory(ginseng)
endif()

option(ENABLE_BENCHMARK_MUSTACHE "Enable mustache Benchmarks" ON)
if(ENABLE_BENCHMARK_MUSTACHE)
  add_subdirectory(mustache)
endif()

option(ENABLE_BENCHMARK_OPENECS "Enable OpenECS Benchmarks" ON)
if(ENABLE_BENCHMARK_OPENECS)
  add_subdirectory(openecs)
endif()

option(ENABLE_BENCHMARK_FLECS "Enable flecs Benchmarks" ON)
if(ENABLE_BENCHMARK_FLECS)
  add_subdirectory(flecs)
endif()

option(ENABLE_BENCHMARK_PICO_ECS "Enable pico_ecs Benchmarks" ON)
if(ENABLE_BENCHMARK_PICO_ECS)
  add_subdirectory(pico_ecs)
endif()

option(ENABLE_BENCHMARK_OOP "Enable OOP Benchmarks" ON)
if(ENABLE_BENCHMARK_OOP)
  add_subdirectory(oop)
endif()
