file(GLOB hdrs "*.h")
file(GLOB srcs "*.cpp")

add_executable(fisheye ${hdrs} ${srcs})
#target_link_libraries(fisheye ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(fisheye OpenGL32.lib Glu32.lib libglew32.lib glfw3d.lib soil2-debug.lib zlib.lib)
install(TARGETS fisheye DESTINATION .)