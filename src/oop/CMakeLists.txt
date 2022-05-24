set(INCLUDE_DIR "include") # must be relative paths
add_library(${CMAKE_PROJECT_NAME}-example-oop STATIC
        # NOTE: add source files here
        oop/systems/ComflabSystem.h
        oop/systems/ComflabSystem.cpp
        oop/systems/MoreComplexSystem.h
        oop/systems/MoreComplexSystem.cpp
        oop/systems/MovementSystem.h
        oop/systems/MovementSystem.cpp
        oop/entities/EntityFactory.h
        oop/entities/EntityFactory.cpp
        oop/entities/MovableObject.h
        oop/entities/MovableObject.cpp
        oop/entities/MovableWithDataObject.h
        oop/entities/MovableWithDataObject.cpp
        oop/OOPApplication.h
        oop/OOPApplication.cpp)
add_library(${CMAKE_PROJECT_NAME}::example::OOP ALIAS ${CMAKE_PROJECT_NAME}-example-oop)

target_include_directories(
        ${CMAKE_PROJECT_NAME}-example-oop
        PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${INCLUDE_DIR}>"
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/${INCLUDE_DIR}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${INCLUDE_DIR}>")
target_link_libraries(${CMAKE_PROJECT_NAME}-example-oop PUBLIC project_warnings project_options)
target_link_libraries(${CMAKE_PROJECT_NAME}-example-oop PUBLIC ${CMAKE_PROJECT_NAME}-base)
