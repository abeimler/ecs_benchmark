add_executable(
  ecs-benchmark-tests
  ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/entt_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/entityx_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/gaia_ecs_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/application/entt_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/application/entityx_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/application/ginseng_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/application/mustache_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/application/gaia_ecs_test.cpp)
target_include_directories(ecs-benchmark-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs-benchmark-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ecs-benchmark-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(ecs-benchmark-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(ecs-benchmark-tests PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark-tests PRIVATE TESTING)

# split into more tests ... error: duplicate symbol: _deps/flecs-build/libflecs_static.a(entity.c.o): src/pico_ecs/libecs-benchmark-example-pico-ecs.a(pico_ecs.cpp.o): ecs_new
add_executable(
        ecs-benchmark-tests-flecs
        ${CMAKE_CURRENT_SOURCE_DIR}/application/flecs_test.cpp)
target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(ecs-benchmark-tests-flecs PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark-tests-flecs PRIVATE TESTING)

add_executable(
        ecs-benchmark-tests-pico-ecs
        ${CMAKE_CURRENT_SOURCE_DIR}/application/pico_ecs_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/pico_ecs_test.cpp)
target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(ecs-benchmark-tests-pico-ecs PRIVATE project_warnings project_options)
target_compile_definitions(ecs-benchmark-tests-pico-ecs PRIVATE TESTING)

# @NOTE: add libs here
target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark::base)
target_link_system_libraries(ecs-benchmark-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_link_libraries(ecs-benchmark-tests-flecs PRIVATE ecs-benchmark::base)
target_link_system_libraries(ecs-benchmark-tests-flecs PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
target_link_libraries(ecs-benchmark-tests-pico-ecs PRIVATE ecs-benchmark::base)
target_link_system_libraries(ecs-benchmark-tests-pico-ecs PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-entt)
target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-entityx)
target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-ginseng)
target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-mustache)
target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-gaia-ecs)
target_link_libraries(ecs-benchmark-tests-flecs PRIVATE ecs-benchmark-example-flecs)
target_link_libraries(ecs-benchmark-tests-pico-ecs PRIVATE ecs-benchmark-example-pico-ecs)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to whatever you want, or
# use different for different binaries
catch_discover_tests(ecs-benchmark-tests)
catch_discover_tests(ecs-benchmark-tests-flecs)
catch_discover_tests(ecs-benchmark-tests-pico-ecs)
