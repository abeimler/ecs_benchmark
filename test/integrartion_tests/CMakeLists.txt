add_executable(ecs-benchmark-integration-tests)
target_sources(ecs-benchmark-integration-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp)
target_include_directories(ecs-benchmark-integration-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs-benchmark-integration-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ecs-benchmark-integration-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(ecs-benchmark-integration-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(ecs-benchmark-integration-tests PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark-integration-tests PUBLIC -DINTEGRATION_TESTING)

# @NOTE: add libs here
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ecs-benchmark-integration-tests PRIVATE ecs-benchmark::base)
target_link_system_libraries(ecs-benchmark-integration-tests PRIVATE Threads::Threads)
target_link_system_libraries(ecs-benchmark-integration-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to whatever you want, or
# use different for different binaries
catch_discover_tests(ecs-benchmark-integration-tests)
