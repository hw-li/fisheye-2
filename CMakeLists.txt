cmake_minimum_required(VERSION 2.8)

project(cubemap)

#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/include")

link_directories("${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_PROGRAM_PATH "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/lib")

add_subdirectory(src)
