set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-oop
        # NOTE: add new benchmarks here
        OOPBenchmarkSuite.cpp OOPBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-oop
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-oop PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-oop PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-oop PRIVATE ecs-benchmark-example-oop)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-oop-complex
        # NOTE: add new benchmarks here
        ComplexOOPBenchmarkSuite.cpp OOPBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-oop-complex
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-oop-complex PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-oop-complex PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-oop-complex PRIVATE ecs-benchmark-example-oop)
