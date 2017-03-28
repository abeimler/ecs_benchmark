cmake_minimum_required(VERSION 2.6)

message("====================================")
message("Building Makefile for Artemis-Cpp")
message("====================================")
message("Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Binary Dir: ${CMAKE_CURRENT_BINARY_DIR}")

# =================================================================
# Project properties
# =================================================================
project(ArtemisCpp)

# Specify build output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Prevents cmake from following symbolic links using GLOB
cmake_policy( SET CMP0009 NEW)

# =================================================================
# Source Files (.cpp files)
# =================================================================
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# =================================================================
# Include directories (containing .h files)
# =================================================================
set(INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

# =================================================================
# Output Library
# =================================================================
include_directories(${INCLUDE_DIRECTORIES})

message("Directories included in the Header search:")
foreach(dir ${INCLUDE_DIRECTORIES})
    message("    ${dir}")
endforeach(dir)

add_library(ArtemisCpp STATIC ${SOURCE_FILES})

# =================================================================
# Install Target
# =================================================================
INSTALL(FILES ${HEADER_FILES}
        DESTINATION include/Artemis)

INSTALL(TARGETS ArtemisCpp
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)