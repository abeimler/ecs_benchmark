set(INCLUDE_DIR "include") # must be relative paths
add_library(ecs-benchmark STATIC basic.cpp basic.h ECSBenchmark.h ExtendedECSBenchmark.h EntityBenchmark.h)
target_include_directories(
  ecs-benchmark
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
         "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark PUBLIC -DBENCHMARKING)

# find_package(fmt CONFIG REQUIRED)
target_link_system_libraries(ecs-benchmark PUBLIC benchmark::benchmark)
target_link_system_libraries(ecs-benchmark PUBLIC benchmark::benchmark_main)
# target_link_system_libraries(ecs-benchmark PUBLIC fmt::fmt-header-only)
