set(LIB${CMAKE_PROJECT_NAME}_HEADERS "")
set(LIB${CMAKE_PROJECT_NAME}_SOURCE "")

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND LIB${CMAKE_PROJECT_NAME}_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND LIB${CMAKE_PROJECT_NAME}_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/anax/Config.hpp 
)
# [[[end]]]

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.c??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND LIB${CMAKE_PROJECT_NAME}_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND LIB${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/base.cpp 
)
# [[[end]]]

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Lib Header Files" FILES ${LIB${CMAKE_PROJECT_NAME}_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Lib Source Files" FILES ${LIB${CMAKE_PROJECT_NAME}_SOURCE})

add_library(lib${CMAKE_PROJECT_NAME} STATIC ${LIB${CMAKE_PROJECT_NAME}_SOURCE})
target_include_directories(lib${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(lib${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lib${CMAKE_PROJECT_NAME} INTERFACE ${PROJECT_BINARY_DIR}/include)

## todo: add libs
target_include_directories(lib${CMAKE_PROJECT_NAME} PRIVATE ${anax_SOURCE_DIR}/include)

target_link_libraries(lib${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(lib${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(lib${CMAKE_PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

set(sources_to_format "${sources_to_format}" "${LIB${CMAKE_PROJECT_NAME}_SOURCE}}" "${LIB${CMAKE_PROJECT_NAME}_HEADERS}}" PARENT_SCOPE)
set(targets_to_tidy "${targets_to_tidy}" "${LIB${CMAKE_PROJECT_NAME}}" PARENT_SCOPE)
