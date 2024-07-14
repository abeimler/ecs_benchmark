# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#
add_executable(ecs-benchmark-fuzz-tester)
target_sources(ecs-benchmark-fuzz-tester PRIVATE fuzz_tester.cpp)
target_include_directories(ecs-benchmark-fuzz-tester PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# @NOTE: add libs here
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ecs-benchmark-fuzz-tester PRIVATE Threads::Threads)

target_link_libraries(ecs-benchmark-fuzz-tester PRIVATE project_warnings project_options)
#target_link_options(ecs-benchmark-fuzz-tester PRIVATE -coverage -fsanitize=fuzzer,undefined,address)
#target_compile_options(ecs-benchmark-fuzz-tester PRIVATE -fsanitize=fuzzer,undefined,address)
# @FIXME: c++: error: unrecognized argument to '-fsanitize=' option: 'fuzzer'

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME ecs-benchmark-fuzz-tester-run COMMAND ecs-benchmark-fuzz-tester -max_total_time=${FUZZ_RUNTIME})
