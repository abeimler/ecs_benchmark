set(INCLUDE_DIR "include") # must be relative paths

# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(
  ecs-benchmark-gaia-ecs-extended
  # NOTE: there can only be ONE suite (split into more execs)
  GaiaEcsBenchmarkSuite.cpp GaiaEcsBenchmarkSuite.h)
target_include_directories(
  ecs-benchmark-gaia-ecs-extended
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
          "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-gaia-ecs-extended PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-gaia-ecs-extended PRIVATE ecs-benchmark)

# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-gaia-ecs-extended PRIVATE ecs-benchmark-example-gaia-ecs)

add_executable(
  ecs-benchmark-gaia-ecs-extended-soa
  # NOTE: there can only be ONE suite (split into more execs)
  GaiaEcsSoABenchmarkSuite.cpp GaiaEcsSoABenchmarkSuite.h)
target_include_directories(
  ecs-benchmark-gaia-ecs-extended-soa
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
          "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-gaia-ecs-extended-soa PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-gaia-ecs-extended-soa PRIVATE ecs-benchmark)

# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-gaia-ecs-extended-soa PRIVATE ecs-benchmark-example-gaia-ecs)
