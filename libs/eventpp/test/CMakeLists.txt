#
# Tests configuration
#

set(EVENTPP_SRC_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_SRC_DIR})

# List of available targets

set(TARGET_EVENTPP eventpp)

# Test TARGET_EVENTPP_SRC_DIR

set(
    TARGET_EVENTPP_SOURCES
    test.cpp
)

add_executable(
    ${TARGET_EVENTPP}
    ${TARGET_EVENTPP_SOURCES}
)

target_include_directories(
    ${TARGET_EVENTPP}
    PRIVATE ${EVENTPP_SRC_DIR}
    PRIVATE ${GOOGLETEST_INCLUDE_DIRS}
)

target_link_libraries(
    ${TARGET_EVENTPP}
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    PRIVATE ${GOOGLETEST_LIBRARIES}
)

add_test(
    NAME ${TARGET_EVENTPP}
    COMMAND ${TARGET_EVENTPP}
)
