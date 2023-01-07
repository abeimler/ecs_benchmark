cmake_minimum_required(VERSION 3.20...3.24)

# Not ideal to use this global variable, but necessary to make sure that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

# strongly encouraged to enable this globally to avoid conflicts between -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for
# example when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS ON)


# Add project_options
# https://github.com/aminya/project_options
# Change the version to update the package (watch the releases of the repository for future updates)
include(cmake/CPM.cmake)
CPMAddPackage(
        NAME              project_options
        GITHUB_REPOSITORY aminya/project_options
        VERSION           0.26.3
        #GIT_TAG           main
        DOWNLOAD_ONLY
)
if(project_options_ADDED)
  include(${project_options_SOURCE_DIR}/Index.cmake)
endif()

# Define the features of the project
include(CMakeDependentOption)
option(ENABLE_TESTING "Enable the tests" ${PROJECT_IS_TOP_LEVEL})
option(ENABLE_BENCHMARKS "Enable Benchmark" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)
get_property(BUILDING_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(BUILDING_MULTI_CONFIG)
  if(NOT CMAKE_BUILD_TYPE)
    # Make sure that all supported configuration types have their associated conan packages available. You can reduce this list to only the
    # configuration types you use, but only if one is not forced-set on the command line for VS
    message(TRACE "Setting up multi-config build types")
    set(CMAKE_CONFIGURATION_TYPES
            Debug Release RelWithDebInfo MinSizeRel
            CACHE STRING "Enabled build types" FORCE)
  else()
    message(TRACE "User chose a specific build type, so we are using that")
    set(CMAKE_CONFIGURATION_TYPES
            ${CMAKE_BUILD_TYPE}
            CACHE STRING "Enabled build types" FORCE)
  endif()
endif()

run_vcpkg()

# Set the project name and language
project(ecs-benchmark
        VERSION 4.6.0
        DESCRIPTION ""
        HOMEPAGE_URL "https://github.com/abeimler/ecs_benchmark"
        LANGUAGES CXX C)
include(cmake/PreventInSourceBuilds.cmake)

# This is a list of headers to pre-compile, here are some common ones
set(PCH_HEADERS
        <vector>
        <utility>
        <string>
        <string_view>)

set(ENABLE_CLANG_TIDY OFF)
set(ENABLE_CPPCHECK OFF)
set(ENABLE_SANITIZER_ADDRESS OFF)
set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR OFF)
set(ENABLE_COVERAGE OFF)
set(ENABLE_INCLUDE_WHAT_YOU_USE OFF)
if(ENABLE_CHECKING)
  set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
  set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
  set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
endif()
if(ENABLE_CHECKING_INCLUDE_WHAT_YOU_USE)
  set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
endif()
if(FEATURE_TESTS)
  if(NOT DEFINED OPT_ENABLE_COVERAGE)
    set(ENABLE_COVERAGE "ENABLE_COVERAGE")
  endif()

  if(NOT DISABLE_SANITIZER)
    if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
      set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
      set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "ENABLE_SANITIZER_UNDEFINED_BEHAVIOR")
    else()
      # or it is MSVC and has run vcvarsall
      string(FIND "$ENV{PATH}" "$ENV{VSINSTALLDIR}" index_of_vs_install_dir)
      if(MSVC AND "${index_of_vs_install_dir}" STREQUAL "-1")
        set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
      endif()
    endif()
  endif()
endif()

# Initialize project_options variable related to this project
# This overwrites `project_options` and sets `project_warnings`
# uncomment to enable the options. Some of them accept one or more inputs:
project_options(
        ENABLE_CACHE
        ${ENABLE_CPPCHECK}
        ${ENABLE_CLANG_TIDY}
        ${ENABLE_INCLUDE_WHAT_YOU_USE}
        ENABLE_VS_ANALYSIS
        # ENABLE_BUILD_WITH_TIME_TRACE
        ENABLE_INTERPROCEDURAL_OPTIMIZATION
        ENABLE_NATIVE_OPTIMIZATION
        # ENABLE_DOXYGEN
        ${ENABLE_COVERAGE}
        ${ENABLE_SANITIZER_ADDRESS}
        # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
        # ENABLE_SANITIZER_LEAK
        # ENABLE_SANITIZER_THREAD
        # ENABLE_SANITIZER_MEMORY
        # ENABLE_PCH
        # PCH_HEADERS
        # ${PCH_HEADERS}
        # WARNINGS_AS_ERRORS
        # ENABLE_USER_LINKER
        # ENABLE_UNITY
        CPPCHECK_OPTIONS
        --enable=style,performance,warning,portability
        --inline-suppr
        # We cannot act on a bug/missing feature of cppcheck
        --suppress=cppcheckError
        --suppress=internalAstError
        # if a file does not have an internalAstError, we get an unmatchedSuppression error
        --suppress=unmatchedSuppression
        --suppress=passedByValue
        --suppress=syntaxError
        --suppress=*:${CMAKE_BINARY_DIR}/_deps/*
        --inconclusive
)
include(cmake/MoreProjectOptions.cmake)

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info
include(cmake/CPM.cmake)
# PackageProject.cmake will be used to make our target installable
cpmaddpackage("gh:TheLartians/PackageProject.cmake@1.9.0")
cpmaddpackage(
        NAME
        Format.cmake
        VERSION
        1.7.3
        GITHUB_REPOSITORY
        TheLartians/Format.cmake
        OPTIONS
        # set to yes skip cmake formatting
        "FORMAT_SKIP_CMAKE NO"
        # path to exclude (optional, supports regular expressions)
        "CMAKE_FORMAT_EXCLUDE libs|resources")

add_subdirectory(libs)

# ##########################################################################################################################################
# Project
# ##########################################################################################################################################

## add configure files
configure_file (
        "${PROJECT_SOURCE_DIR}/include/Version.h.in"
        "${PROJECT_BINARY_DIR}/include/Version.h"
        @ONLY
)

add_subdirectory(src)

if(ENABLE_TESTS)
  # This variable is set by project() in CMake 3.21+
  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}" PROJECT_IS_TOP_LEVEL)
  if(PROJECT_IS_TOP_LEVEL)
    # Consider the CTest module, which creates targets and options! Only needed if you want to enable submissions to a CDash server.
    include(CTest)
  endif()
  enable_testing()
  add_subdirectory(test)
endif()

if(ENABLE_FUZZ_TESTS)
  add_subdirectory(fuzz_test)
endif()

if(ENABLE_BENCHMARKS)
  message(AUTHOR_WARNING "Building Benchmarks.")
  add_subdirectory(benchmark)
endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment so that it behaves well with MSVC's debugger, and we
# can run the target from visual studio
if(MSVC)
  get_all_targets(all_targets)
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()