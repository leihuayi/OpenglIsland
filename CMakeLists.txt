cmake_minimum_required(VERSION 3.6)
project(Terrain)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(SOIL)
include_directories(. include src ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SOIL_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/interactionManager.cpp src/terrain.cpp src/camera.hpp src/camera.cpp)
add_executable(Terrain ${SOURCE_FILES})

target_link_libraries(Terrain ${GLEW_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SOIL_LIBRARY})