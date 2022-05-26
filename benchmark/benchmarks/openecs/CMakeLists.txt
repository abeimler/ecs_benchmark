set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-openecs
        # NOTE: add new benchmarks here
        OpenECSBenchmark.cpp OpenECSBenchmark.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-openecs
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-openecs PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-openecs PRIVATE ${CMAKE_PROJECT_NAME}-benchmark-base)


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-openecs PRIVATE ${CMAKE_PROJECT_NAME}-example-openecs)


