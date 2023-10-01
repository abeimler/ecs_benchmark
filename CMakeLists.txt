cmake_minimum_required(VERSION 3.21...3.24)

# Not ideal to use this global variable, but necessary to make sure that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

# strongly encouraged to enable this globally to avoid conflicts between -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for
# example when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS ON)

# Add project_options https://github.com/aminya/project_options Change the version to update the package (watch the releases of the
# repository for future updates)
include(cmake/CPM.cmake)
cpmaddpackage(
  NAME
  project_options
  GITHUB_REPOSITORY
  aminya/project_options
  VERSION
  0.32.1
  # GIT_TAG           main
  DOWNLOAD_ONLY)
if(project_options_ADDED)
  include(${project_options_SOURCE_DIR}/Index.cmake)
endif()

option(ENABLE_CROSS_COMPILING "Detect cross compiler and setup toolchain" OFF)
if(ENABLE_CROSS_COMPILING)
  enable_cross_compiler()
endif()
run_vcpkg()

# Set the project name and language
project(
  ecs-benchmark
  VERSION 4.7.3
  DESCRIPTION "Benchmarks of common ECS (Entity-Component-System)-Frameworks in C++ (or C)"
  HOMEPAGE_URL "https://github.com/abeimler/ecs_benchmark"
  LANGUAGES CXX C)
string(TOUPPER "${CMAKE_PROJECT_NAME}" CMAKE_PROJECT_NAME_UPPERCASE)
string(TOLOWER "${CMAKE_PROJECT_NAME}" CMAKE_PROJECT_NAME_LOWERCASE)
include(cmake/PreventInSourceBuilds.cmake)

# User options
include(cmake/CMakeOptions.cmake)
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
include(cmake/ProjectOptions.cmake)

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info
include(cmake/CPM.cmake)
# PackageProject.cmake will be used to make our target installable
cpmaddpackage("gh:TheLartians/PackageProject.cmake@1.11.0")
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

# add configure files
configure_file("${PROJECT_SOURCE_DIR}/include/Version.h.in" "${PROJECT_BINARY_DIR}/include/Version.h" @ONLY)

if(ENABLE_TESTING)
  # This variable is set by project() in CMake 3.21+
  string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}" PROJECT_IS_TOP_LEVEL)
  if(PROJECT_IS_TOP_LEVEL)
    # Consider the CTest module, which creates targets and options! Only needed if you want to enable submissions to a CDash server.
    include(CTest)
  endif()
  enable_testing()
  message(AUTHOR_WARNING "Building Tests. Be sure to check out test/constexpr_tests.cpp for constexpr testing")
  add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  message(AUTHOR_WARNING "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  if(NOT OPT_ENABLE_ADDRESS_SANITIZER AND NOT OPT_ENABLE_THREAD_SANITIZER)
    message(WARNING "You need asan or tsan enabled for meaningful fuzz testing")
  endif()
  add_subdirectory(fuzz_test)
endif()

if(ENABLE_BENCHMARKS)
  message(AUTHOR_WARNING "Building Benchmarks.")
  add_subdirectory(benchmark)
endif()

add_subdirectory(src)

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment so that it behaves well with MSVC's debugger, and we
# can run the target from visual studio
if(MSVC)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()
