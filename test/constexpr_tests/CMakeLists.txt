add_executable(ecs-benchmark-constexpr-tests)
target_sources(ecs-benchmark-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_include_directories(ecs-benchmark-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs-benchmark-constexpr-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ecs-benchmark-constexpr-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_link_libraries(ecs-benchmark-constexpr-tests PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark-constexpr-tests PRIVATE -DCONSTEXPR_TESTING)

# @NOTE: add libs here
target_link_libraries(ecs-benchmark-constexpr-tests PRIVATE ecs-benchmark::base)
target_link_system_libraries(ecs-benchmark-constexpr-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to whatever you want, or
# use different for different binaries
catch_discover_tests(ecs-benchmark-constexpr-tests)



# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when things go wrong
# with the constexpr testing
add_executable(ecs-benchmark-relaxed-constexpr-tests)
target_sources(ecs-benchmark-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp)
target_include_directories(ecs-benchmark-relaxed-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs-benchmark-relaxed-constexpr-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ecs-benchmark-relaxed-constexpr-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(ecs-benchmark-relaxed-constexpr-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(ecs-benchmark-relaxed-constexpr-tests PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark-relaxed-constexpr-tests PRIVATE -DRELAXED_CONSTEXPR_TESTING)
target_compile_definitions(ecs-benchmark-relaxed-constexpr-tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

# @NOTE: add libs here
target_link_libraries(ecs-benchmark-relaxed-constexpr-tests PRIVATE ecs-benchmark::base)
target_link_system_libraries(ecs-benchmark-relaxed-constexpr-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to whatever you want, or
# use different for different binaries
catch_discover_tests(ecs-benchmark-relaxed-constexpr-tests)
