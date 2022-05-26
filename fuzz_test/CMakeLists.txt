# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.normpath(os.path.relpath(src, path)).replace("\\","/"))
#       cog.outl(")")
# ]]]
# [[[end]]]
# cmake-format: on

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.c??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           if "catch_main.cpp" in os.path.relpath(src, path): continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.normpath(os.path.relpath(src, path)).replace("\\","/"))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/fuzz_tester.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Test Header Files"
  FILES ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Test Source Files"
  FILES ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE})

# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#
add_executable(${CMAKE_PROJECT_NAME}-fuzz-tester)
target_sources(${CMAKE_PROJECT_NAME}-fuzz-tester PRIVATE ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE}
                                                         ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-fuzz-tester PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# @NOTE: add libs here
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Bitsery CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}-fuzz-tester ${CMAKE_PROJECT_NAME}::core ${CMAKE_PROJECT_NAME}::bitsery
                      ${CMAKE_PROJECT_NAME}::json)
target_link_libraries(${CMAKE_PROJECT_NAME}-fuzz-tester Bitsery::bitsery nlohmann_json nlohmann_json::nlohmann_json spdlog::spdlog
                      spdlog::spdlog_header_only)
target_link_libraries(${CMAKE_PROJECT_NAME}-fuzz-tester Threads::Threads)

target_link_options(${CMAKE_PROJECT_NAME}-fuzz-tester PRIVATE project_options project_warnings -coverage
                    -fsanitize=fuzzer,undefined,address)
target_compile_options(${CMAKE_PROJECT_NAME}-fuzz-tester PRIVATE -fsanitize=fuzzer,undefined,address)

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME ${CMAKE_PROJECT_NAME}-fuzz-tester-run COMMAND ${CMAKE_PROJECT_NAME}-fuzz-tester -max_total_time=${FUZZ_RUNTIME})
