# more 3rd party dependencies

CPMAddPackage(
        NAME googletest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG release-1.11.0
        VERSION 1.11.0
        OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

CPMAddPackage(
        NAME benchmark
        GITHUB_REPOSITORY google/benchmark
        VERSION 1.6.1
        OPTIONS "BENCHMARK_ENABLE_TESTING OFF"
)
if(benchmark_ADDED)
    # enable c++11 to avoid compilation errors
    set_target_properties(benchmark PROPERTIES CXX_STANDARD 11)
endif()


# FIXME: see src/openecs/
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/openecs)