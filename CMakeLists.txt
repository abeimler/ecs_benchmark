cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (ecs_benchmark VERSION 0.1.0 LANGUAGES CXX)



include(CheckCXXSourceCompiles)
find_package (Threads)

###
## Setup Compiler
###

#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    

## best practice by Jason Turner
## More Flags: https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

if (CMAKE_COMPILER_IS_GNUCXX)
    set(warnings "-Wall -Wextra -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(warnings "${warnings} -Weverything")
    endif()
    set(warnings "${warnings} -pedantic")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /W44640 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

find_package (Threads)

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

add_subdirectory(${LIB_PATH}/benchpress)



###
## Application build
###
add_executable(${PROJECT_NAME} ${SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME} c++abi)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr
						                        cxx_lambdas)


target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/entityx1)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/entityx2)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/anax/include)

target_link_libraries (${PROJECT_NAME} PRIVATE entityx)
target_link_libraries (${PROJECT_NAME} PRIVATE anax)


target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_PATH}/benchpress/src)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_PATH})

#target_compile_options(${PROJECT_NAME} PRIVATE -fexceptions)
#target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)

target_link_libraries (${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(${PROJECT_NAME} PRIVATE -pthread)
