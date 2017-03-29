cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (ecs_benchmark VERSION 1.2.1 LANGUAGES CXX)


###
## Setup Compiler
###

include(CheckCXXSourceCompiles)

## best practice by Jason Turner
## More Flags: https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
## cmake code from https://github.com/ChaiScript/ChaiScript/blob/develop/CMakeLists.txt

if(CMAKE_COMPILER_IS_GNUCC)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

  if(GCC_VERSION VERSION_LESS 4.9)
    set(CPP11_FLAG "-std=c++1y")
  else()
    set(CPP11_FLAG "-std=c++14")
  endif()
else()
  set(CPP11_FLAG "-std=c++14")
endif()

if(MSVC)
  add_definitions(/W4 /w14545 /w34242 /w34254 /w34287 /w44263 /w44265 /w44296 /w44311 /w44826 /we4289 /w14546 /w14547 /w14549 /w14555 /w14619 /w14905 /w14906 /w14928)

  if (MSVC_VERSION STREQUAL "1800")
    # VS2013 doesn't have magic statics
    add_definitions(/w44640)
  else()
    # enum warnings are too noisy on MSVC2013
    add_definitions(/w34062)
  endif()

  add_definitions(/bigobj)
  # Note on MSVC compiler flags.
  # The code base selective disables warnings as necessary when the compiler is complaining too much
  # about something that is perfectly valid, or there is simply no technical way around it
  # This particular warning, C4503 is in regards to the decorated names that MSVC generates internally.
  # The error did not come up until the move to C++11, but the compiler doesn't give enough information
  # to determine where the error is coming from, and the internet provides no real information for
  # how to workaround or fix the error. So I'm disabling it globally.
  add_definitions(/wd4503)
else()
  add_definitions(-Wall -Wextra -Wno-error -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -Wno-old-style-cast  -pedantic ${CPP11_FLAG})

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Weverything -Wno-c++98-compat-pedantic  -Wno-c++98-compat -Wno-documentation -Wno-switch-enum -Wno-weak-vtables -Wno-missing-prototypes -Wno-padded -Wno-missing-noreturn -Wno-exit-time-destructors -Wno-documentation-unknown-command)
  else()
    add_definitions(-Wnoexcept)
  endif()

  if(APPLE)
    add_definitions(-Wno-sign-compare)
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  option(USE_LIBCXX "Use clang's libcxx" TRUE)

  if(USE_LIBCXX)
    add_definitions(-stdlib=libc++)
    set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG} -stdlib=libc++")
  else()
    set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG}")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC)
  set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG}")
endif()

# limitations in MinGW require us to make an optimized build
# for the sake of object sizes or something
if(MINGW OR CYGWIN)
  add_definitions(-O3)
endif()

find_package (Threads)
if(CMAKE_COMPILER_IS_GNUCC)
    execute_process(COMMAND ${CMAKE_C_COMPILER} --version OUTPUT_VARIABLE GCC_FULL_VERSION)
    if(GCC_FULL_VERSION MATCHES "4.8.1.*ubuntu")
    set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--no-as-needed -pthread")
    else()
    set(LINKER_FLAGS "${LINKER_FLAGS} -pthread")
    endif()
else()
    set(LINKER_FLAGS "${LINKER_FLAGS} -pthread")
endif()

add_definitions(-pthread)

##
# Testing Compiler
##

check_cxx_source_compiles(
"
#include <cstdint>
#include <ctime>

#include <random>

int main() {

    std::random_device rd {};
    auto value = rd();

    return 0;
}
"
HAS_CXX11_RANDOM_DEVICE
)

check_cxx_source_compiles(
"
#include <cstdint>
#include <ctime>

#include <random>

int main() {

    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<unsigned int> dis;
    auto value = dis(generator);

    return 0;
}
"
HAS_CXX11_DEFAULT_RANDOM_ENGINE
)

if(NOT HAS_CXX11_RANDOM_DEVICE)
    add_definitions(-DHAS_NO_CXX11_RANDOM_DEVICE)
endif()

if(NOT HAS_CXX11_DEFAULT_RANDOM_ENGINE)
    add_definitions(-DHAS_NO_CXX11_DEFAULT_RANDOM_DEVICE)
endif()













###
## Source/Header Files
###
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC ${SRC_PATH}/*.cpp ${SRC_PATH}/*.cxx ${SRC_PATH}/*.cc)
file(GLOB_RECURSE HEADERS ${INCLUDE_PATH}/*.h ${INCLUDE_PATH}/*.hpp ${INCLUDE_PATH}/*.hxx)



###
## 3rd libs
###
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(ENTITYX_BUILD_SHARED 0)
add_subdirectory(${LIB_PATH}/entityx1)
add_subdirectory(${LIB_PATH}/entityx2)

add_subdirectory(${LIB_PATH}/anax)
add_subdirectory(${LIB_PATH}/Artemis-Cpp)

add_subdirectory(${LIB_PATH}/benchpress)

add_subdirectory(${LIB_PATH}/eventpp)
add_subdirectory(${LIB_PATH}/entt)


###
## Application build
###
add_executable(${PROJECT_NAME} ${SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr
						                        cxx_lambdas)

# use SYSTEM to get rid of warnings in 3rd librarys
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/entityx1)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/entityx2)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/anax/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/Artemis-Cpp/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/benchpress/src)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/eventpp/src)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${LIB_PATH}/entt/src)


target_link_libraries (${PROJECT_NAME} PRIVATE entityx)
target_link_libraries (${PROJECT_NAME} PRIVATE anax)
target_link_libraries (${PROJECT_NAME} PRIVATE ArtemisCpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_PATH})

#target_compile_options(${PROJECT_NAME} PRIVATE -fexceptions)
#target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)



###
## More Settings
###

SET(USE_MORECOMPLEX_SYSTEM OFF CACHE BOOL "use the 4. MoreComplex-System")
if(USE_MORECOMPLEX_SYSTEM)
target_compile_options(${PROJECT_NAME} PRIVATE -DUSE_MORECOMPLEX_SYSTEM)
endif()
