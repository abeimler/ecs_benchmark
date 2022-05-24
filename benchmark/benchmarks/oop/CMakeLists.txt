set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-oop
        # NOTE: add new benchmarks here
        OOPBenchmark.cpp OOPBenchmark.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-oop
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-oop PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-oop PRIVATE ${CMAKE_PROJECT_NAME}-benchmark-base)


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-oop PRIVATE ${CMAKE_PROJECT_NAME}-example-oop)


set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-oop-more
        # NOTE: add new benchmarks here
        MoreOOPBenchmark.cpp OOPBenchmark.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-oop-more
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-oop-more PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-oop-more PRIVATE ${CMAKE_PROJECT_NAME}-benchmark-base)


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-oop-more PRIVATE ${CMAKE_PROJECT_NAME}-example-oop)
