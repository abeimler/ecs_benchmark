set(${CMAKE_PROJECT_NAME}_HEADERS "")
set(${CMAKE_PROJECT_NAME}_SOURCE "")

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND ${CMAKE_PROJECT_NAME}_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseBenchmark.h 
)
# [[[end]]]

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.c??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND ${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/BaseBenchmark.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ginseng/ginsengBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ecs/ecsBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/entt/enttBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/entt/enttGroupBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/entt/enttRuntimeBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/anax/anaxBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/artemis/artemisBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/entityx/entityxEventBusBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/entityx/entityxBenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/entityx2/entityx2BenchmarkRunner.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/enttlegacy/enttlegacyBenchmarkRunner.cpp 
)
# [[[end]]]

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${${CMAKE_PROJECT_NAME}_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${${CMAKE_PROJECT_NAME}_SOURCE})

add_executable(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_SOURCE})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE ${PROJECT_BINARY_DIR}/include)

## todo: add libs
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${benchpress_SOURCE_DIR}/src)

target_link_libraries(${CMAKE_PROJECT_NAME} lib${CMAKE_PROJECT_NAME})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

set(sources_to_format "${sources_to_format}" "${${CMAKE_PROJECT_NAME}_SOURCE}}" "${${CMAKE_PROJECT_NAME}_HEADERS}}" PARENT_SCOPE)
set(targets_to_tidy "${targets_to_tidy}" "${CMAKE_PROJECT_NAME}" PARENT_SCOPE)
