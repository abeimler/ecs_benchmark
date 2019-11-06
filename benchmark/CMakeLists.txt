set(${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS "")
set(${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE "")

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
# [[[end]]]

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.c??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND ${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
)
# [[[end]]]

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Benchmark Header Files" FILES ${${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Benchmark Source Files" FILES ${${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-benchmark ${${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE})
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark INTERFACE ${PROJECT_BINARY_DIR}/include)

## todo: add libs
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PRIVATE ${benchpress_SOURCE_DIR}/include)

target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark lib${CMAKE_PROJECT_NAME})
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(${CMAKE_PROJECT_NAME}-benchmark PUBLIC cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME}-benchmark PROPERTIES CXX_EXTENSIONS OFF)

set(sources_to_format "${sources_to_format}" "${${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE}}" "${${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS}}" PARENT_SCOPE)
set(targets_to_tidy "${targets_to_tidy}" "${CMAKE_PROJECT_NAME}-benchmark" PARENT_SCOPE)
