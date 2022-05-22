set(INCLUDE_DIR "include") # must be relative paths
add_library(${CMAKE_PROJECT_NAME}-benchmark-base STATIC
        ECSBenchmark.cpp ECSBenchmark.h
        )
target_include_directories(
        ${CMAKE_PROJECT_NAME}-benchmark-base
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark-base PUBLIC project_warnings project_options)
target_compile_definitions(${CMAKE_PROJECT_NAME}-benchmark-base PUBLIC -DBENCHMARKING)

find_package(fmt CONFIG REQUIRED)
target_link_system_libraries(${CMAKE_PROJECT_NAME}-benchmark-base PUBLIC benchmark::benchmark)
target_link_system_libraries(${CMAKE_PROJECT_NAME}-benchmark-base PUBLIC benchmark::benchmark_main)
target_link_system_libraries(${CMAKE_PROJECT_NAME}-benchmark-base PUBLIC fmt::fmt-header-only)

