set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended
        # NOTE: add new benchmarks here
        EnttBenchmarkSuite.cpp EnttBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended-stable
        # NOTE: add new benchmarks here
        EnttStableBenchmarkSuite.cpp EnttStableBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended-stable
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-stable PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-stable PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-stable PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended-runtime
        # NOTE: add new benchmarks here
        EnttRuntimeBenchmarkSuite.cpp EnttRuntimeBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended-runtime
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-runtime PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-runtime PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-runtime PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended-group
        # NOTE: add new benchmarks here
        EnttGroupBenchmarkSuite.cpp EnttGroupBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-group PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-group PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-group PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)




set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended-non-owning-group
        # NOTE: add new benchmarks here
        EnttNonOwningGroupBenchmarkSuite.cpp EnttNonOwningGroupBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended-non-owning-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-non-owning-group PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-non-owning-group PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-non-owning-group PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)




set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended-full-owning-group
        # NOTE: add new benchmarks here
        EnttFullOwningGroupBenchmarkSuite.cpp EnttFullOwningGroupBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended-full-owning-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-full-owning-group PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-full-owning-group PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-full-owning-group PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)




set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entt-extended-partial-owning-group
        # NOTE: add new benchmarks here
        EnttPartialOwningGroupBenchmarkSuite.cpp EnttPartialOwningGroupBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entt-extended-partial-owning-group
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-partial-owning-group PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-partial-owning-group PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entt-extended-partial-owning-group PRIVATE ${CMAKE_PROJECT_NAME}-example-entt)


