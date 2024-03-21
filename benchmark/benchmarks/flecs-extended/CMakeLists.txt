set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(
  ecs-benchmark-flecs-extended
  # NOTE: add new benchmarks here
  FlecsBenchmarkSuite.cpp FlecsBenchmarkSuite.h)
target_include_directories(
  ecs-benchmark-flecs-extended
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
          "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-flecs-extended PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-flecs-extended PRIVATE ecs-benchmark)
# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-flecs-extended PRIVATE ecs-benchmark-example-flecs)


set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(
        ecs-benchmark-flecs-extended-event
        # NOTE: add new benchmarks here
        FlecsEventBenchmarkSuite.cpp FlecsEventBenchmarkSuite.h)
target_include_directories(
        ecs-benchmark-flecs-extended-event
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-flecs-extended-event PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-flecs-extended-event PRIVATE ecs-benchmark)
# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-flecs-extended-event PRIVATE ecs-benchmark-example-flecs)


set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(
        ecs-benchmark-flecs-extended-event-emit
        # NOTE: add new benchmarks here
        FlecsEventEmitBenchmarkSuite.cpp FlecsEventEmitBenchmarkSuite.h)
target_include_directories(
        ecs-benchmark-flecs-extended-event-emit
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-flecs-extended-event-emit PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-flecs-extended-event-emit PRIVATE ecs-benchmark)
# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-flecs-extended-event-emit PRIVATE ecs-benchmark-example-flecs)