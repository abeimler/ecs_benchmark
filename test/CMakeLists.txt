
set(${CMAKE_PROJECT_NAME}_TEST_HEADERS "")
set(${CMAKE_PROJECT_NAME}_TEST_SOURCE "")

# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_TEST_HEADERS ")
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
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_TEST_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND ${CMAKE_PROJECT_NAME}_TEST_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp 
)
# [[[end]]]

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Test Header Files" FILES ${${CMAKE_PROJECT_NAME}_TEST_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Test Source Files" FILES ${${CMAKE_PROJECT_NAME}_TEST_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-test ${${CMAKE_PROJECT_NAME}_TEST_SOURCE})
target_include_directories(${CMAKE_PROJECT_NAME}-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-test PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME}-test PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG} ${CONAN_INCLUDE_DIRS_CATCH2})
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${LIB${CMAKE_PROJECT_NAME}} CONAN_PKG::spdlog CONAN_PKG::Catch2)
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(${CMAKE_PROJECT_NAME}-test PUBLIC cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME}-test PROPERTIES CXX_EXTENSIONS OFF)


set(sources_to_format "${sources_to_format}" "${${CMAKE_PROJECT_NAME}_TEST_SOURCE}}" "${${CMAKE_PROJECT_NAME}_TEST_HEADERS}}" PARENT_SCOPE)
set(targets_to_tidy "${targets_to_tidy}" "${CMAKE_PROJECT_NAME}-test" PARENT_SCOPE)


include(Catch)
catch_discover_tests(${CMAKE_PROJECT_NAME}-test)