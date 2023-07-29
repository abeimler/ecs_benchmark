
# This is a list of headers to pre-compile, here are some common ones
set(PCH_HEADERS <fmt/format.h>
        <spdlog/spdlog.h>
        <vector> <string> <algorithm> <iostream> <utility>)

set(ENABLE_CLANG_TIDY OFF)
set(ENABLE_CPPCHECK OFF)
set(ENABLE_SANITIZER_ADDRESS OFF)
set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR OFF)
set(ENABLE_COVERAGE OFF)
set(ENABLE_INCLUDE_WHAT_YOU_USE OFF)
set(ENABLE_BUILD_WITH_TIME_TRACE OFF)
set(ENABLE_GCC_ANALYZER OFF)
set(PROJECT_OPTIONS_LINKER OFF)
set(PROJECT_OPTIONS_LINKER_LINKER OFF)

if(ENABLE_STATIC_ANALYZER)
    set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
    set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
    set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
    set(ENABLE_GCC_ANALYZER "ENABLE_GCC_ANALYZER")
endif()
if(ENABLE_STATIC_ANALYZER_INCLUDE_WHAT_YOU_USE)
    set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
endif()
if(ENABLE_TESTING)
    if(NOT DISABLE_COVERAGE)
        if(NOT DEFINED OPT_ENABLE_COVERAGE)
            set(ENABLE_COVERAGE "ENABLE_COVERAGE")
        endif()
    endif()

    if(NOT DISABLE_SANITIZER)
        if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
            if (SUPPORTS_ASAN)
                set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
            endif()
            if (SUPPORTS_UBSAN)
                set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "ENABLE_SANITIZER_UNDEFINED_BEHAVIOR")
            endif()
        else()
            # or it is MSVC and has run vcvarsall
            string(FIND "$ENV{PATH}" "$ENV{VSINSTALLDIR}" index_of_vs_install_dir)
            if(MSVC AND "${index_of_vs_install_dir}" STREQUAL "-1")
                set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
            endif()
        endif()
    endif()
endif()
if(ENABLE_TIME_TRACE)
    set(ENABLE_BUILD_WITH_TIME_TRACE "ENABLE_BUILD_WITH_TIME_TRACE")
endif()

if(OPT_ENABLE_HARDENING)
    if(NOT SUPPORTS_UBSAN
            OR OPT_ENABLE_SANITIZER_UNDEFINED
            OR OPT_ENABLE_SANITIZER_ADDRESS
            OR OPT_ENABLE_SANITIZER_THREAD
            OR OPT_ENABLE_SANITIZER_LEAK)
        set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
        set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${OPT_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${OPT_ENABLE_SANITIZER_UNDEFINED}")

    set(ENABLE_CONTROL_FLOW_PROTECTION "ENABLE_CONTROL_FLOW_PROTECTION")
    set(ENABLE_STACK_PROTECTION "ENABLE_STACK_PROTECTION")
    set(ENABLE_OVERFLOW_PROTECTION "ENABLE_OVERFLOW_PROTECTION")
    set(ENABLE_ELF_PROTECTION "ENABLE_ELF_PROTECTION")
    #set(ENABLE_RUNTIME_SYMBOLS_RESOLUTION "ENABLE_RUNTIME_SYMBOLS_RESOLUTION")
endif()

if(OPT_ENABLE_IPO)
    set(ENABLE_IPO "ENABLE_INTERPROCEDURAL_OPTIMIZATION ENABLE_NATIVE_OPTIMIZATION")
endif()
if(OPT_WARNINGS_AS_ERRORS)
    set(WARNINGS_AS_ERRORS "WARNINGS_AS_ERRORS")
endif()
if(OPT_ENABLE_SANITIZER_ADDRESS)
    set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
endif()
if(OPT_ENABLE_SANITIZER_LEAK)
    set(ENABLE_SANITIZER_LEAK "ENABLE_SANITIZER_LEAK")
endif()
if(OPT_ENABLE_SANITIZER_UNDEFINED)
    set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "ENABLE_SANITIZER_UNDEFINED_BEHAVIOR")
endif()
if(OPT_ENABLE_SANITIZER_THREAD)
    set(ENABLE_SANITIZER_THREAD "ENABLE_SANITIZER_THREAD")
endif()
if(OPT_ENABLE_SANITIZER_MEMORY)
    set(ENABLE_SANITIZER_MEMORY "ENABLE_SANITIZER_MEMORY")
endif()
if(OPT_ENABLE_UNITY_BUILD)
    set(ENABLE_UNITY "ENABLE_UNITY")
endif()
if(OPT_ENABLE_CLANG_TIDY)
    set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
endif()
if(OPT_ENABLE_CPPCHECK)
    set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
endif()
if(OPT_ENABLE_PCH)
    set(ENABLE_PCH "ENABLE_PCH")
endif()
if(OPT_ENABLE_CACHE)
    set(ENABLE_CACHE "ENABLE_CACHE")
endif()

if(DISABLE_COVERAGE)
    set(ENABLE_COVERAGE OFF)
endif()
if(DISABLE_SANITIZER)
    set(ENABLE_SANITIZER_ADDRESS OFF)
    set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR OFF)
    set(ENABLE_SANITIZER_THREAD OFF)
    set(ENABLE_SANITIZER_MEMORY OFF)
endif()
if(OPT_USE_LLD_LINKER)
    set(PROJECT_OPTIONS_LINKER "LINKER")
    set(PROJECT_OPTIONS_LINKER_LINKER "lld")
endif()
if(OPT_USE_CUSTOM_LINKER)
    set(PROJECT_OPTIONS_LINKER "LINKER")
    set(PROJECT_OPTIONS_LINKER_LINKER "${OPT_USE_CUSTOM_LINKER}")
endif()

# defaulted_project_options sets recommended defaults and provides user and developer modes and full GUI support for choosing options at
# configure time for more flexibility, look into project_options() macro Initialize project_options variable related to this project This
# overwrites `project_options` and sets `project_warnings` uncomment the options to enable them:
project_options(
        ${ENABLE_CACHE}
        ${ENABLE_CPPCHECK}
        ${ENABLE_CLANG_TIDY}
        ${ENABLE_INCLUDE_WHAT_YOU_USE}
        ENABLE_VS_ANALYSIS
        ${ENABLE_IPO}
        ${ENABLE_COVERAGE}
        ${ENABLE_SANITIZER_ADDRESS}
        ${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR}
        ${ENABLE_SANITIZER_THREAD}
        ${ENABLE_SANITIZER_MEMORY}
        ${ENABLE_CONTROL_FLOW_PROTECTION}
        ${ENABLE_STACK_PROTECTION}
        ${ENABLE_OVERFLOW_PROTECTION}
        ${ENABLE_ELF_PROTECTION}
        ${ENABLE_RUNTIME_SYMBOLS_RESOLUTION}
        ${ENABLE_PCH}
        PCH_HEADERS ${PCH_HEADERS}
        ${WARNINGS_AS_ERRORS}
        ${ENABLE_BUILD_WITH_TIME_TRACE}
        ${ENABLE_UNITY}
        ${PROJECT_OPTIONS_LINKER} ${PROJECT_OPTIONS_LINKER_LINKER}
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
        --suppress=*:${CMAKE_SOURCE_DIR}/libs/*
        --inconclusive)
include(cmake/MoreProjectOptions.cmake)