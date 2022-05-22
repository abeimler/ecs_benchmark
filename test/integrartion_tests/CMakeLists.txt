add_executable(${CMAKE_PROJECT_NAME}-integration-tests)
target_sources(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE project_warnings project_options)
target_compile_definitions(${CMAKE_PROJECT_NAME}-integration-tests PUBLIC -DINTEGRATION_TESTING)

# @NOTE: add libs here
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE ${CMAKE_PROJECT_NAME}::base)
target_link_system_library(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE Threads::Threads)
target_link_system_library(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE Catch2::Catch2)
target_link_system_library(${CMAKE_PROJECT_NAME}-integration-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to whatever you want, or
# use different for different binaries
catch_discover_tests(${CMAKE_PROJECT_NAME}-integration-tests

if(ENABLE_COVERAGE)
  setup_target_for_coverage_gcovr_html(
    NAME
    ${CMAKE_PROJECT_NAME}-coverage-integration-test
    EXECUTABLE
    ${CMAKE_PROJECT_NAME}-integration-test
    EXCLUDE
    "${PROJECT_SOURCE_DIR}/benchmark"
    "${PROJECT_SOURCE_DIR}/test"
    "${PROJECT_SOURCE_DIR}/test/constexpr_tests"
    "${PROJECT_SOURCE_DIR}/test/integrartion_tests"
    "${PROJECT_SOURCE_DIR}/test/tests"
    "${PROJECT_SOURCE_DIR}/thirdparty"
    "${CMAKE_BINARY_DIR}/_deps")
endif()
