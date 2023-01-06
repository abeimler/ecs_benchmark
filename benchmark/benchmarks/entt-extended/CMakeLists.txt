set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended
        # NOTE: add new benchmarks here
        EnttBenchmarkSuite.cpp EnttBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended PRIVATE ecs-benchmark-example-entt)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended-stable
        # NOTE: add new benchmarks here
        EnttStableBenchmarkSuite.cpp EnttStableBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended-stable
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended-stable PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended-stable PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended-stable PRIVATE ecs-benchmark-example-entt)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended-runtime
        # NOTE: add new benchmarks here
        EnttRuntimeBenchmarkSuite.cpp EnttRuntimeBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended-runtime
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended-runtime PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended-runtime PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended-runtime PRIVATE ecs-benchmark-example-entt)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended-group
        # NOTE: add new benchmarks here
        EnttGroupBenchmarkSuite.cpp EnttGroupBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended-group PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended-group PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended-group PRIVATE ecs-benchmark-example-entt)




set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended-non-owning-group
        # NOTE: add new benchmarks here
        EnttNonOwningGroupBenchmarkSuite.cpp EnttNonOwningGroupBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended-non-owning-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended-non-owning-group PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended-non-owning-group PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended-non-owning-group PRIVATE ecs-benchmark-example-entt)




set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended-full-owning-group
        # NOTE: add new benchmarks here
        EnttFullOwningGroupBenchmarkSuite.cpp EnttFullOwningGroupBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended-full-owning-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended-full-owning-group PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended-full-owning-group PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended-full-owning-group PRIVATE ecs-benchmark-example-entt)




set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "ecs-benchmark-myecs"
add_executable(ecs-benchmark-entt-extended-partial-owning-group
        # NOTE: add new benchmarks here
        EnttPartialOwningGroupBenchmarkSuite.cpp EnttPartialOwningGroupBenchmarkSuite.h
        )
target_include_directories(ecs-benchmark-entt-extended-partial-owning-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(ecs-benchmark-entt-extended-partial-owning-group PRIVATE project_warnings project_options)
target_link_libraries(ecs-benchmark-entt-extended-partial-owning-group PRIVATE ecs-benchmark)


# @NOTE: add libs for example here
target_link_libraries(ecs-benchmark-entt-extended-partial-owning-group PRIVATE ecs-benchmark-example-entt)


