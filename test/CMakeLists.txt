find_package(Catch2 CONFIG REQUIRED)
include(Catch)

add_subdirectory(tests)

option(ENABLE_CONSTEXPR_TESTS "Enable constexpr Test Builds" OFF)
if(ENABLE_CONSTEXPR_TESTS)
  message(AUTHOR_WARNING "Building Tests. Be sure to check out test/constexpr_tests for persistence testing")
  add_subdirectory(constexpr_tests)
endif()

option(ENABLE_INTEGRATION_TESTS "Enable Integration Tests" OFF)
if(ENABLE_INTEGRATION_TESTS)
  message(AUTHOR_WARNING "Building Integration Tests. Be sure to check out test/integration_tests for integration testing")
  add_subdirectory(integrartion_tests)
endif()
