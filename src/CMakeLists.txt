file(GLOB hdrs "*.h")
file(GLOB srcs "*.cpp")

add_executable(cubemap ${hdrs} ${srcs})
#target_link_libraries(cubemap ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(cubemap OpenGL32.lib Glu32.lib libglew32.lib glfw3d.lib soil2-debug.lib)
install(TARGETS cubemap DESTINATION .)