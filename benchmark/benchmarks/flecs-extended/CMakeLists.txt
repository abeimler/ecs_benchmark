set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-flecs-extended
        # NOTE: add new benchmarks here
        FlecsBenchmarkSuite.cpp FlecsBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-flecs-extended
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-flecs-extended PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-flecs-extended PRIVATE ${CMAKE_PROJECT_NAME}-benchmark-base)


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-flecs-extended PRIVATE ${CMAKE_PROJECT_NAME}-example-flecs)


