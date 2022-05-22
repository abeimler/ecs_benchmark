add_executable(${CMAKE_PROJECT_NAME}-constexpr-tests)
target_sources(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE project_warnings project_options)
target_compile_definitions(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE -DCONSTEXPR_TESTING)

# @NOTE: add libs here
target_link_libraries(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${CMAKE_PROJECT_NAME}::base)
target_link_system_library(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE Catch2::Catch2)
target_link_system_library(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE Catch2::Catch2WithMain)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to whatever you want, or
# use different for different binaries
catch_discover_tests(${CMAKE_PROJECT_NAME}-constexpr-tests)

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when things go wrong
# with the constexpr testing
add_executable(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests)
target_sources(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_SOURCE}
                                                                     ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE project_warnings project_options)
target_compile_definitions(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE -DRELAXED_CONSTEXPR_TESTING)
target_compile_definitions(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

# @NOTE: add libs here

catch_discover_tests(
  ${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests
  TEST_PREFIX
  "relaxed_constexpr."
  REPORTER
  xml
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "relaxed_constexpr."
  OUTPUT_SUFFIX
  .xml)

if(ENABLE_COVERAGE)
  setup_target_for_coverage_gcovr_html(
    NAME
    ${CMAKE_PROJECT_NAME}-coverage-constexpr-test
    EXECUTABLE
    ${CMAKE_PROJECT_NAME}-constexpr-tests
    EXCLUDE
    "${PROJECT_SOURCE_DIR}/benchmark"
    "${PROJECT_SOURCE_DIR}/src/app/desktop"
    "${PROJECT_SOURCE_DIR}/src/app/raspberrypi"
    "${PROJECT_SOURCE_DIR}/src/core"
    "${PROJECT_SOURCE_DIR}/src/persistence"
    "${PROJECT_SOURCE_DIR}/test"
    "${PROJECT_SOURCE_DIR}/test/tests"
    "${PROJECT_SOURCE_DIR}/thirdparty"
    "${CMAKE_BINARY_DIR}/_deps")

  setup_target_for_coverage_gcovr_html(
    NAME
    ${CMAKE_PROJECT_NAME}-coverage-relaxed-constexpr-test
    EXECUTABLE
    ${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests
    EXCLUDE
    "${PROJECT_SOURCE_DIR}/benchmark"
    "${PROJECT_SOURCE_DIR}/src/app/engine"
    "${PROJECT_SOURCE_DIR}/test"
    "${PROJECT_SOURCE_DIR}/test/constexpr_tests"
    "${PROJECT_SOURCE_DIR}/test/integrartion_tests"
    "${PROJECT_SOURCE_DIR}/test/tests"
    "${PROJECT_SOURCE_DIR}/thirdparty"
    "${CMAKE_BINARY_DIR}/_deps")
endif()
