cmake_minimum_required(VERSION 3.14)
project(ecs_benchmark VERSION 3.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
list(APPEND CMAKE_MODULE_PATH ${CONAN_LIB_DIRS_CATCH2}/cmake/Catch2)

include(useGoldLinker)

# If clang-format/clang-tidy is not in PATH,
# you should define CMAKE_PROGRAM_PATH to
# a list containing it

# Enable modern C++ (default)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################################
# Find thread
################################
find_package(Threads REQUIRED)

##################################
# Prepare variables
##################################
set(sources_to_format "")
set(targets_to_tidy "")

##################################
# add more dependencies
##################################
include(FetchContent)

FetchContent_Declare(
  benchpress
  GIT_REPOSITORY https://github.com/abeimler/benchpress
  GIT_TAG        1.2.2
)
FetchContent_GetProperties(benchpress)
if(NOT benchpress_POPULATED)
  FetchContent_Populate(benchpress)
  #add_subdirectory(${benchpress_SOURCE_DIR} ${benchpress_BINARY_DIR})
endif()

FetchContent_Declare(
  anax
  GIT_REPOSITORY https://github.com/miguelmartin75/anax
  GIT_TAG        v2.1.0
)
FetchContent_GetProperties(anax)
if(NOT anax_POPULATED)
  FetchContent_Populate(anax)

  set(INSTALL_HEADERS false)
  set(BUILD_SHARED_LIBS false)

  add_subdirectory(${anax_SOURCE_DIR} ${anax_BINARY_DIR})
endif()

FetchContent_Declare(
  ArtemisCpp
  GIT_REPOSITORY https://github.com/vinova/Artemis-Cpp
)
FetchContent_GetProperties(ArtemisCpp)
if(NOT ArtemisCpp_POPULATED)
  FetchContent_Populate(ArtemisCpp)
  add_subdirectory(${artemiscpp_SOURCE_DIR} ${artemiscpp_BINARY_DIR})
endif()

FetchContent_Declare(
  entityx
  GIT_REPOSITORY https://github.com/alecthomas/entityx
  GIT_TAG        1.1.2
)
FetchContent_GetProperties(entityx)
if(NOT entityx_POPULATED)
  FetchContent_Populate(entityx)

  set(ENTITYX_BUILD_SHARED false)
  set(ENTITYX_BUILD_TESTING false)
  set(ENTITYX_RUN_BENCHMARKS false)

  add_subdirectory(${entityx_SOURCE_DIR} ${entityx_BINARY_DIR})
endif()

FetchContent_Declare(
  entityx2
  GIT_REPOSITORY https://github.com/alecthomas/entityx
  GIT_TAG        origin/experimental/compile_time
)
FetchContent_GetProperties(entityx2)
if(NOT entityx2_POPULATED)
  FetchContent_Populate(entityx2)
endif()

FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt
  GIT_TAG        v3.2.0
)
FetchContent_GetProperties(entt)
if(NOT entt_POPULATED)
  FetchContent_Populate(entt)
endif()

FetchContent_Declare(
  enttlegacy
  GIT_REPOSITORY https://github.com/skypjack/entt
  GIT_TAG        v1.1.0
)
FetchContent_GetProperties(enttlegacy)
if(NOT enttlegacy_POPULATED)
  FetchContent_Populate(enttlegacy)
endif()

FetchContent_Declare(
  eventpp
  GIT_REPOSITORY https://github.com/abeimler/eventpp
)
FetchContent_GetProperties(eventpp)
if(NOT eventpp_POPULATED)
  FetchContent_Populate(eventpp)
endif()

FetchContent_Declare(
  ginseng
  GIT_REPOSITORY https://github.com/apples/ginseng
  GIT_TAG        v1.1
)
FetchContent_GetProperties(ginseng)
if(NOT ginseng_POPULATED)
  FetchContent_Populate(ginseng)
endif()




##################################
# Project
##################################

string(TOUPPER "${CMAKE_PROJECT_NAME}" CMAKE_PROJECT_NAME_UPPERCASE)
set(${CMAKE_PROJECT_NAME_UPPERCASE}_TESTS OFF CACHE BOOL "Enable ${CMAKE_PROJECT_NAME} Tests")
set(${CMAKE_PROJECT_NAME_UPPERCASE}_BENCHMARK OFF CACHE BOOL "Enable ${CMAKE_PROJECT_NAME} Benchmark")
configure_file (
    "${PROJECT_SOURCE_DIR}/include/Version.h.in"
    "${PROJECT_BINARY_DIR}/include/Version.h"
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)
add_subdirectory(app)

include(CTest)
enable_testing()
if (${CMAKE_PROJECT_NAME_UPPERCASE}_TESTS)
  add_subdirectory(test)
endif()
if (${CMAKE_PROJECT_NAME_UPPERCASE}_BENCHMARK)
  add_subdirectory(benchmark)
endif()


##################################
# Utilities
##################################

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}") # CMake 3.9+
endif()

# A target named "clangformat", use make clangformat to format all specified files
include(ClangFormat)
clangformat_setup(${sources_to_format})

# If this finds clang-tidy, it will automatically set CMAKE_CXX_CLANG_TIDY,
include(ClangTidy)
clangtidy_setup()
if (CLANG_TIDY_COMMAND)
    message(STATUS "Your clang-tidy path is: ${CMAKE_CXX_CLANG_TIDY}")
    set_target_properties(${targets_to_tidy} PROPERTIES
        CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}"
    )
endif()
