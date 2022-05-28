set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-entityx
        # NOTE: add new benchmarks here
        EntityXBenchmark.cpp EntityXBenchmark.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-entityx
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-entityx PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-entityx PRIVATE ${CMAKE_PROJECT_NAME}-benchmark-base)
target_compile_definitions(${CMAKE_PROJECT_NAME}-entityx PRIVATE "-DENTITYX_VERSION=${ENTITYX_VERSION}")


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-entityx PRIVATE ${CMAKE_PROJECT_NAME}-example-entityx)


