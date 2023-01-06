set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-oop
        # NOTE: add new benchmarks here
        OOPBenchmarkSuite.cpp OOPBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-oop
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-oop PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-oop PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-oop PRIVATE ${CMAKE_PROJECT_NAME}-example-oop)



set(INCLUDE_DIR "include") # must be relative paths
# NOTE: rename project in "${CMAKE_PROJECT_NAME}-myecs"
add_executable(${CMAKE_PROJECT_NAME}-oop-complex
        # NOTE: add new benchmarks here
        ComplexOOPBenchmarkSuite.cpp OOPBenchmarkSuite.h
        )
target_include_directories(${CMAKE_PROJECT_NAME}-oop-complex
        PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-oop-complex PRIVATE project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-oop-complex PRIVATE ${CMAKE_PROJECT_NAME})


# @NOTE: add libs for example here
target_link_libraries(${CMAKE_PROJECT_NAME}-oop-complex PRIVATE ${CMAKE_PROJECT_NAME}-example-oop)
