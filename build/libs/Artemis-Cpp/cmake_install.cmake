# Install script for directory: /home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Artemis" TYPE FILE FILES
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/ImmutableBag.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/Artemis.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/EntitySystem.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/DelayedEntitySystem.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/World.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/EntityManager.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/SystemManager.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/ComponentMapper.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/DelayedEntityProcessingSystem.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/BitSize.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/TypeInfoComparator.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/GroupManager.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/SystemBitManager.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/EntityProcessingSystem.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/ComponentType.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/Component.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/ComponentTypeManager.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/TagManager.h"
    "/home/hirc/Schreibtisch/ecs_benchmark/libs/Artemis-Cpp/include/Artemis/Entity.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/hirc/Schreibtisch/ecs_benchmark/build/lib/libArtemisCpp.a")
endif()

