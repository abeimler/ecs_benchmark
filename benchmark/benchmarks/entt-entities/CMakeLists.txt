set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-entities
        # NOTE: add new benchmarks here
        EnttEntityBenchmarkSuite.cpp EnttEntityBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-entities
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-entities PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-entities PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-entities PRIVATE ecs-benchmark-example-entt)


