set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(
  ecs-benchmark-mustache-extended
  # NOTE: add new benchmarks here
  MustacheBenchmarkSuite.cpp MustacheBenchmarkSuite.h)
target_include_directories(
  ecs-benchmark-mustache-extended
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
          "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-mustache-extended PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-mustache-extended PRIVATE ecs-benchmark)
# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-mustache-extended PRIVATE ecs-benchmark-example-mustache)


set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(
        ecs-benchmark-mustache-extended-event
        # NOTE: add new benchmarks here
        MustacheEventBenchmarkSuite.cpp MustacheEventBenchmarkSuite.h)
target_include_directories(
        ecs-benchmark-mustache-extended-event
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-mustache-extended-event PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-mustache-extended-event PRIVATE ecs-benchmark)
# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-mustache-extended-event PRIVATE ecs-benchmark-example-mustache)